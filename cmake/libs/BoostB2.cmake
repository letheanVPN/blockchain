# This script handles downloading and building a specific version of Boost using b2.
# It is intended to be included from the main CMakeLists.txt.

include(ExternalProject)

# --- Boost Build (b2) Arguments ---
math(EXPR CMAKE_SIZEOF_VOID_P_BITS "${CMAKE_SIZEOF_VOID_P} * 8")

foreach(COMPONENT ${BOOST_LIBS_TO_BUILD})
    list(APPEND B2_ARGS "--with-${COMPONENT}")
endforeach()

list(APPEND B2_ARGS
    "link=static"
    "runtime-link=static"
    "threading=multi"
    "address-model=${CMAKE_SIZEOF_VOID_P_BITS}"
    "--layout=system" # Install libs with simple names (e.g. libboost_program_options.a)
)

# If ICU is required, add the necessary flags for b2.
if(ICU_ROOT)
    list(APPEND B2_ARGS "-sICU_PATH=${ICU_ROOT}")
endif()

# If OpenSSL was built, provide its paths to the b2 build.
if(TARGET OpenSSL::SSL)
    list(APPEND B2_ARGS "-sOPENSSL_INCLUDE=${OPENSSL_INSTALL_PREFIX}/include")
    list(APPEND B2_ARGS "-sOPENSSL_LIBPATH=${OPENSSL_INSTALL_PREFIX}/lib")
endif()

# Forward the C++ standard.
if(CMAKE_CXX_STANDARD)
    list(APPEND B2_ARGS "cxxstd=${CMAKE_CXX_STANDARD}")
endif()

# --- Platform-specific flags ---
set(B2_EXTRA_CXX_FLAGS "")
set(B2_EXTRA_LINK_FLAGS "")

if(APPLE)
    # Architecture
    if(CMAKE_OSX_ARCHITECTURES)
        if("${CMAKE_OSX_ARCHITECTURES}" STREQUAL "arm64")
            list(APPEND B2_ARGS "architecture=arm")
        elseif("${CMAKE_OSX_ARCHITECTURES}" STREQUAL "x86_64")
            list(APPEND B2_ARGS "architecture=x86")
        else()
            message(WARNING "Unsupported CMAKE_OSX_ARCHITECTURES for b2: ${CMAKE_OSX_ARCHITECTURES}. Letting b2 autodetect.")
        endif()
    endif()

    # Deployment target and sysroot
    if(CMAKE_OSX_DEPLOYMENT_TARGET)
        set(B2_EXTRA_CXX_FLAGS "${B2_EXTRA_CXX_FLAGS} -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET}")
        set(B2_EXTRA_LINK_FLAGS "${B2_EXTRA_LINK_FLAGS} -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET}")
    endif()
    if(CMAKE_OSX_SYSROOT)
        set(B2_EXTRA_CXX_FLAGS "${B2_EXTRA_CXX_FLAGS} -isysroot ${CMAKE_OSX_SYSROOT}")
        set(B2_EXTRA_LINK_FLAGS "${B2_EXTRA_LINK_FLAGS} -isysroot ${CMAKE_OSX_SYSROOT}")
    endif()

    # ICU for boost_locale
    find_package(ICU QUIET)
    if(ICU_FOUND)
        message(STATUS "Found ICU for Boost.b2 build. Adding include path to compiler flags: ${ICU_INCLUDE_DIRS}")
        foreach(DIR ${ICU_INCLUDE_DIRS})
            set(B2_EXTRA_CXX_FLAGS "${B2_EXTRA_CXX_FLAGS} -I${DIR}")
        endforeach()
    else()
        message(WARNING "ICU not found. Building boost_locale without ICU backend via b2.")
#        list(APPEND B2_ARGS "--without-icu")
    endif()
endif()

# Append extra flags to B2_ARGS, quoting them for b2.
string(STRIP "${B2_EXTRA_CXX_FLAGS}" B2_EXTRA_CXX_FLAGS_STRIPPED)
if(B2_EXTRA_CXX_FLAGS_STRIPPED)
    # Conditionally quote the flags. If they contain spaces (common on macOS),
    # they must be quoted. If not (common on Linux), omitting the quotes is safer
    # and avoids platform-specific shell escaping issues.
    if(B2_EXTRA_CXX_FLAGS_STRIPPED MATCHES " ")
        list(APPEND B2_ARGS "cxxflags=\"${B2_EXTRA_CXX_FLAGS_STRIPPED}\"")
    else()
        list(APPEND B2_ARGS "cxxflags=${B2_EXTRA_CXX_FLAGS_STRIPPED}")
    endif()
endif()
string(STRIP "${B2_EXTRA_LINK_FLAGS}" B2_EXTRA_LINK_FLAGS_STRIPPED)
if(B2_EXTRA_LINK_FLAGS_STRIPPED)
    if(B2_EXTRA_LINK_FLAGS_STRIPPED MATCHES " ")
        list(APPEND B2_ARGS "linkflags=\"${B2_EXTRA_LINK_FLAGS_STRIPPED}\"")
    else()
        list(APPEND B2_ARGS "linkflags=${B2_EXTRA_LINK_FLAGS_STRIPPED}")
    endif()
endif()

# --- Toolset and Compiler Configuration ---
# Always create a user-config.jam to explicitly point b2 to the correct compiler.
if(MSVC)
    set(BOOST_TOOLSET "msvc")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(BOOST_TOOLSET "gcc")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(BOOST_TOOLSET "clang")
else()
    message(FATAL_ERROR "Unsupported compiler for Boost.b2 build: ${CMAKE_CXX_COMPILER_ID}.")
endif()

file(MAKE_DIRECTORY ${BOOST_WORK_DIR})
set(BOOST_USER_CONFIG_JAM_PATH ${BOOST_WORK_DIR}/user-config.jam)
set(BOOST_USER_CONFIG_JAM_CONTENT "using ${BOOST_TOOLSET} : : \"${CMAKE_CXX_COMPILER}\" ;")
file(WRITE ${BOOST_USER_CONFIG_JAM_PATH} "${BOOST_USER_CONFIG_JAM_CONTENT}")

list(APPEND B2_ARGS "toolset=${BOOST_TOOLSET}")
set(B2_USER_CONFIG_ARG "--user-config=${BOOST_USER_CONFIG_JAM_PATH}")

# --- Platform-specific commands ---
if(WIN32)
    set(_BOOTSTRAP_CMD bootstrap.bat)
    set(_B2_CMD b2.exe)
    # For static linking on Windows, prevent auto-linking by MSVC
    add_compile_definitions(BOOST_ALL_NO_LIB)
else()
    set(_BOOTSTRAP_CMD ./bootstrap.sh)
    set(_B2_CMD ./b2)
endif()

# Determine the number of parallel jobs using the robust ProcessorCount module.
include(ProcessorCount)
ProcessorCount(B2_JOBS)
if(B2_JOBS EQUAL 0)
    set(B2_JOBS 1) # Fallback to 1 core if detection fails.
endif()

# --- Filesystem Permissions Workaround for WSL/Unix ---
# On filesystems that don't properly handle Unix execute permissions (like WSL
# mounting a Windows drive), scripts extracted from the tarball won't be
# executable. We use the UPDATE_COMMAND to explicitly run `chmod +x` on the
# necessary scripts after extraction and before configuration.
set(_UPDATE_COMMAND "")
if(UNIX AND NOT APPLE)
    find_program(CHMOD_EXECUTABLE chmod)
    if(CHMOD_EXECUTABLE)
        set(_UPDATE_COMMAND ${CHMOD_EXECUTABLE} +x <SOURCE_DIR>/bootstrap.sh && ${CHMOD_EXECUTABLE} +x <SOURCE_DIR>/tools/build/src/engine/build.sh)
    endif()
endif()

# --- External Project Definition ---
ExternalProject_Add(
    boost_external
    PREFIX ${BOOST_WORK_DIR}
    DOWNLOAD_DIR ${SDK_CACHE_DIR}
    URL ${BOOST_URL}
    URL_HASH SHA256=${BOOST_SHA256}
    INSTALL_DIR ${BOOST_INSTALL_PREFIX}
    DEPENDS ${BOOST_EXTRA_DEPS}
    BUILD_IN_SOURCE 1 # This is the key fix: Boost's b2 is an in-source build system.
    UPDATE_COMMAND ${_UPDATE_COMMAND}
    EXCLUDE_FROM_ALL 1

    # Bootstrap step (runs in <PREFIX>/src/boost_external)
    # Explicitly tell bootstrap which compiler toolset and executable to use. This is more robust
    # than relying on auto-detection, which can fail with compiler wrappers like ccache.
    # The bootstrap.sh script respects the CXX environment variable, not a --with-cxx flag.
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E env
        "CC=${CMAKE_C_COMPILER}" "CXX=${CMAKE_CXX_COMPILER}"
        ${_BOOTSTRAP_CMD} --with-toolset=${BOOST_TOOLSET}

    # Build and install step (runs in <PREFIX>/src/boost_external)
    BUILD_COMMAND ${_B2_CMD}
        install
        --prefix=<INSTALL_DIR>
        variant=$<IF:$<CONFIG:Debug>,debug,release>
        --build-dir=${BOOST_WORK_DIR}/build
        ${B2_ARGS}
        ${B2_USER_CONFIG_ARG}
        -j # Pass as a separate argument to avoid shell escaping issues.
        ${B2_JOBS}

    # No separate install command needed as b2 install does it
    INSTALL_COMMAND ""

    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
)