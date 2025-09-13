include_guard(GLOBAL) # Prevent multiple inclusions

include(ExternalProject)
include(libs/BoostUrls)

# --- Configuration ---
# These variables can be set by the parent scope to override defaults.
if(NOT DEFINED BOOST_VERSION)
    set(BOOST_VERSION "1.85.0" CACHE STRING "The version of Boost to download and build")
endif()

# The parent scope is expected to set BOOST_LIBS_TO_BUILD.
if(NOT BOOST_LIBS_TO_BUILD)
    message(FATAL_ERROR "BOOST_LIBS_TO_BUILD must be set before including Boost.cmake. This is typically set in the main CMakeLists.txt.")
endif()

# --- Pre-compiled Cache Configuration ---
option(FORCE_BUILD_BOOST "Force building Boost from source, ignoring pre-compiled caches." OFF)
option(REQUIRE_PRECOMPILED_BOOST "Fail the build if a pre-compiled Boost cache cannot be downloaded and used." OFF)

# --- Platform and SDK Path Calculation ---
# PLATFORM_ID is now determined in the main sdk.cmake file.
set(BOOST_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build/sdk/${PLATFORM_ID}/boost)
set(BOOST_WORK_DIR ${DEP_WORK_ROOT}/boost)

# --- Makefile Integration ---
set(MAKEFILE_VARS_CONTENT "
BOOST_VERSION_FOR_PACKAGING := ${BOOST_VERSION}\n
DEP_PLATFORM_ID_FOR_PACKAGING := ${PLATFORM_ID}\n
BOOST_SDK_DIR_FOR_PACKAGING := ${BOOST_INSTALL_PREFIX}\n
")
file(WRITE "${CMAKE_BINARY_DIR}/packaging.vars" "${MAKEFILE_VARS_CONTENT}")

# --- Define Boost variables for the parent scope ---
set(Boost_INCLUDE_DIRS ${BOOST_INSTALL_PREFIX}/include)
set(Boost_LIBRARY_DIRS ${BOOST_INSTALL_PREFIX}/lib)
set(Boost_VERSION ${BOOST_VERSION})

file(MAKE_DIRECTORY "${BOOST_INSTALL_PREFIX}/include" "${BOOST_INSTALL_PREFIX}/lib")

# --- Create Boost Targets ---
# Replicate the structure from the official Boost-provided CMake files
# to ensure consistency between USE_SYSTEM_DEPS=ON and USE_SYSTEM_DEPS=OFF.

# 1. Create the header-only and compatibility targets.
if(NOT TARGET Boost::headers)
    add_library(Boost::headers INTERFACE IMPORTED GLOBAL)
    set_target_properties(Boost::headers PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${BOOST_INSTALL_PREFIX}/include"
    )
endif()

if(NOT TARGET Boost::boost)
    add_library(Boost::boost INTERFACE IMPORTED GLOBAL)
    set_property(TARGET Boost::boost APPEND PROPERTY INTERFACE_LINK_LIBRARIES Boost::headers)
endif()

if(NOT TARGET Boost::diagnostic_definitions)
    add_library(Boost::diagnostic_definitions INTERFACE IMPORTED GLOBAL)
    if(WIN32)
        set_property(TARGET Boost::diagnostic_definitions PROPERTY INTERFACE_COMPILE_DEFINITIONS "BOOST_LIB_DIAGNOSTIC")
    endif()
endif()

if(NOT TARGET Boost::disable_autolinking)
    add_library(Boost::disable_autolinking INTERFACE IMPORTED GLOBAL)
    if(WIN32)
        set_property(TARGET Boost::disable_autolinking PROPERTY INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB")
    endif()
endif()

if(NOT TARGET Boost::dynamic_linking)
    add_library(Boost::dynamic_linking INTERFACE IMPORTED GLOBAL)
    if(WIN32)
        set_property(TARGET Boost::dynamic_linking PROPERTY INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_DYN_LINK")
    endif()
endif()

# 2. Create targets for each compiled library component.
if(MSVC AND SDK_LIB_TYPE STREQUAL "STATIC")
    set(_boost_lib_prefix "lib")
elseif (WIN32 AND SDK_LIB_TYPE STREQUAL "SHARED")
    set(_boost_lib_prefix "")
else()
    set(_boost_lib_prefix "lib")
endif ()

set(_boost_libs "")
list(APPEND _boost_libs Boost::headers)

foreach(COMPONENT ${BOOST_LIBS_TO_BUILD})
    set(TARGET_NAME "Boost::${COMPONENT}")
    if(NOT TARGET ${TARGET_NAME})
        add_library(${TARGET_NAME} ${SDK_LIB_TYPE} IMPORTED GLOBAL)
        set_target_properties(${TARGET_NAME} PROPERTIES
            IMPORTED_LOCATION "${BOOST_INSTALL_PREFIX}/lib/${_boost_lib_prefix}boost_${COMPONENT}${SDK_LIB_SUFFIX}"
            INTERFACE_INCLUDE_DIRECTORIES "${BOOST_INSTALL_PREFIX}/include"
        )
    endif()
    list(APPEND _boost_libs ${TARGET_NAME})
endforeach()

set(Boost_LIBRARIES "${_boost_libs}")

# --- Check for existing valid installation ---
if(NOT FORCE_BUILD_BOOST)
    if(EXISTS "${BOOST_INSTALL_PREFIX}/include/boost/version.hpp")
        set(_boost_sdk_is_complete TRUE)
        foreach(COMPONENT ${BOOST_LIBS_TO_BUILD})
            set(_lib_to_find "${_boost_lib_prefix}boost_${COMPONENT}${SDK_LIB_SUFFIX}")
            find_library(_component_lib_found
                NAMES ${_lib_to_find}
                HINTS "${BOOST_INSTALL_PREFIX}/lib"
                NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH
            )
            if(NOT _component_lib_found)
                message(STATUS "Existing Boost SDK is missing required component: ${COMPONENT} (${_lib_to_find})")
                set(_boost_sdk_is_complete FALSE)
                break()
            endif()
            unset(_component_lib_found CACHE)
        endforeach()

        if(_boost_sdk_is_complete)
            message(STATUS "Found complete pre-installed Boost in SDK: ${BOOST_INSTALL_PREFIX}")
            set(Boost_FOUND TRUE)
            return() # Success!
        endif()
    endif()

    # --- Download from pre-compiled cache ---
    if(PRECOMPILED_CACHE_URL)
        if(REQUIRE_PRECOMPILED_BOOST)
            sdk_download_and_extract_cache(BOOST ${BOOST_VERSION} ${BOOST_INSTALL_PREFIX} REQUIRE_PRECOMPILED)
        else()
            sdk_download_and_extract_cache(BOOST ${BOOST_VERSION} ${BOOST_INSTALL_PREFIX})
        endif()

        if(CACHE_DOWNLOAD_SUCCESS)
            set(Boost_FOUND TRUE)
            return() # Success!
        endif()
    endif()
endif()

# --- Build from Source (if not found in cache) ---

# Boost may have other dependencies (e.g. ICU, OpenSSL). We define them here.
set(BOOST_EXTRA_DEPS OpenSSL::SSL OpenSSL::Crypto)
#set(ICU_ROOT "")

# --- ICU Dependency Build (if locale is requested) ---
list(FIND BOOST_LIBS_TO_BUILD "locale" LOCALE_INDEX)
if(NOT LOCALE_INDEX EQUAL -1)
    message(STATUS "Boost 'locale' component requested, preparing to build ICU dependency.")
    set(ICU_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build/sdk/${PLATFORM_ID}/icu)
    set(ICU_ROOT ${ICU_INSTALL_PREFIX})

    include(ProcessorCount)
    ProcessorCount(_NPROC)
    if(_NPROC EQUAL 0)
        set(_NPROC 1)
    endif()

    if(MSVC)
        # For MSVC, we must build using the Visual Studio solution.
        # The configure script is for Unix-like environments and fails with MSVC.
        ExternalProject_Add(icu_external
            URL                 ${ICU_URL}
            URL_HASH            SHA256=${ICU_SHA256}
            DOWNLOAD_DIR        ${SDK_CACHE_DIR}
            INSTALL_DIR         ${ICU_INSTALL_PREFIX}
            PREFIX              ${DEP_WORK_ROOT}/icu
            EXCLUDE_FROM_ALL    1

            # No configure step, we build the solution directly.
            CONFIGURE_COMMAND   ""
            BUILD_COMMAND       ${CMAKE_MSBUILD_COMMAND} <SOURCE_DIR>/source/allinone/allinone.sln /p:Configuration=Release /p:Platform=x64
            # Manually install the headers and libraries.
            INSTALL_COMMAND     cmd /c "copy <SOURCE_DIR>\\readme.html ${ICU_INSTALL_PREFIX}\\install_stamp.txt && xcopy <SOURCE_DIR>\\include ${ICU_INSTALL_PREFIX}\\include /s /e /y /i && xcopy <SOURCE_DIR>\\lib64 ${ICU_INSTALL_PREFIX}\\lib /s /e /y /i"
            BUILD_BYPRODUCTS    <SOURCE_DIR>/lib64/sicuuc.lib
                                <SOURCE_DIR>/lib64/sicuin.lib
                                <SOURCE_DIR>/lib64/sicudt.lib
        )

        # Define imported targets for MSVC static build
        if(NOT TARGET ICU::data)
            add_library(ICU::data STATIC IMPORTED GLOBAL)
            set_target_properties(ICU::data PROPERTIES
                IMPORTED_LOCATION "${ICU_INSTALL_PREFIX}/lib/sicudt.lib"
            )
            add_dependencies(ICU::data icu_external)
        endif()
        if(NOT TARGET ICU::uc)
            add_library(ICU::uc STATIC IMPORTED GLOBAL)
            set_target_properties(ICU::uc PROPERTIES
                IMPORTED_LOCATION "${ICU_INSTALL_PREFIX}/lib/sicuuc.lib"
            )
            add_dependencies(ICU::uc icu_external)
        endif()
        if(NOT TARGET ICU::i18n)
            add_library(ICU::i18n STATIC IMPORTED GLOBAL)
            set_target_properties(ICU::i18n PROPERTIES
                IMPORTED_LOCATION "${ICU_INSTALL_PREFIX}/lib/sicuin.lib"
            )
            add_dependencies(ICU::i18n icu_external)
        endif()

    else()
        # Existing logic for non-MSVC (Linux, macOS)
        set(ICU_C_FLAGS "${CMAKE_C_FLAGS}")
        set(ICU_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        set(ICU_LD_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
        if(APPLE AND CMAKE_OSX_SYSROOT)
            message(STATUS "ICU Build: Using sysroot ${CMAKE_OSX_SYSROOT}")
            set(ICU_C_FLAGS "${ICU_C_FLAGS} -isysroot ${CMAKE_OSX_SYSROOT}")
            set(ICU_CXX_FLAGS "${ICU_CXX_FLAGS} -isysroot ${CMAKE_OSX_SYSROOT}")
            set(ICU_LD_FLAGS "${ICU_LD_FLAGS} -isysroot ${CMAKE_OSX_SYSROOT}")
        elseif(UNIX AND NOT APPLE)
            # For static linking on Linux, PIC is required.
            message(STATUS "ICU Build: Adding -fPIC for Linux static build.")
            set(ICU_C_FLAGS "${ICU_C_FLAGS} -fPIC")
            set(ICU_CXX_FLAGS "${ICU_CXX_FLAGS} -fPIC")
        endif()
        set(ICU_CONFIGURE_ENV "CC=${CMAKE_C_COMPILER}" "CXX=${CMAKE_CXX_COMPILER}" "CFLAGS=${ICU_C_FLAGS}" "CXXFLAGS=${ICU_CXX_FLAGS}" "LDFLAGS=${ICU_LD_FLAGS}")

        set(ICU_CONFIGURE_OPTIONS "")
        list(APPEND ICU_CONFIGURE_OPTIONS --with-data-packaging=archive)
        if(APPLE)
            if(CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
                list(APPEND ICU_CONFIGURE_OPTIONS --host=aarch64-apple-darwin)
            elseif(CMAKE_OSX_ARCHITECTURES MATCHES "x86_64")
                list(APPEND ICU_CONFIGURE_OPTIONS --host=x86_64-apple-darwin)
            endif()
        elseif(UNIX AND NOT APPLE)
            if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
                list(APPEND ICU_CONFIGURE_OPTIONS --host=aarch64-linux-gnu)
            endif()
        endif()

        ExternalProject_Add(icu_external
            URL                 ${ICU_URL}
            URL_HASH            SHA256=${ICU_SHA256}
            DOWNLOAD_DIR        ${SDK_CACHE_DIR}
            INSTALL_DIR         ${ICU_INSTALL_PREFIX}
            PREFIX              ${DEP_WORK_ROOT}/icu
            EXCLUDE_FROM_ALL    1

            CONFIGURE_COMMAND   ${CMAKE_COMMAND} -E env ${ICU_CONFIGURE_ENV}
                                sh <SOURCE_DIR>/${ICU_CONFIGURE_PATH}
                                --prefix=<INSTALL_DIR> --disable-shared --enable-static --disable-tests --disable-samples
                                ${ICU_CONFIGURE_OPTIONS}
            BUILD_COMMAND       ${CMAKE_MAKE_PROGRAM} -j${_NPROC}
            INSTALL_COMMAND     ${CMAKE_MAKE_PROGRAM} install
        )

        if(NOT TARGET ICU::data)
            add_library(ICU::data STATIC IMPORTED GLOBAL)
            set_target_properties(ICU::data PROPERTIES
                IMPORTED_LOCATION "${ICU_INSTALL_PREFIX}/lib/libicudata.a"
            )
            add_dependencies(ICU::data icu_external)
        endif()
        if(NOT TARGET ICU::uc)
            add_library(ICU::uc STATIC IMPORTED GLOBAL)
            set_target_properties(ICU::uc PROPERTIES
                IMPORTED_LOCATION "${ICU_INSTALL_PREFIX}/lib/libicuuc.a"
            )
            add_dependencies(ICU::uc icu_external)
        endif()
        if(NOT TARGET ICU::i18n)
            add_library(ICU::i18n STATIC IMPORTED GLOBAL)
            set_target_properties(ICU::i18n PROPERTIES
                IMPORTED_LOCATION "${ICU_INSTALL_PREFIX}/lib/libicui18n.a"
            )
            add_dependencies(ICU::i18n icu_external)
        endif()
    endif()

    list(APPEND BOOST_EXTRA_DEPS icu_external)
endif()

message(STATUS "Building Boost ${BOOST_VERSION} from source...")
string(REPLACE "." "_" BOOST_VERSION_SUFFIX ${BOOST_VERSION})

set(BOOST_BUILD_SYSTEM ${BOOST_VERSION_${BOOST_VERSION_SUFFIX}_BUILD_SYSTEM})
set(BOOST_SHA256 ${BOOST_VERSION_${BOOST_VERSION_SUFFIX}_SHA256})
set(BOOST_URL ${BOOST_VERSION_${BOOST_VERSION_SUFFIX}_URLS})

if(NOT BOOST_BUILD_SYSTEM)
    message(FATAL_ERROR "Boost version ${BOOST_VERSION} is not defined in the database in cmake/libs/BoostUrls.cmake. Please add it.")
endif()

if(NOT BOOST_URL)
    message(FATAL_ERROR "Source URLs for Boost version ${BOOST_VERSION} are not defined in the database in cmake/libs/BoostUrls.cmake. Please add them.")
endif()

set(_needs_7z FALSE)
foreach(url ${BOOST_URL})
    if(url MATCHES "\\.7z$")
        set(_needs_7z TRUE)
        break()
    endif()
endforeach()

if(_needs_7z)
    if(NOT DEFINED CMAKE_SEVEN_ZIP_COMMAND)
        find_program(CMAKE_SEVEN_ZIP_COMMAND NAMES 7z 7za DOC "Path to 7-Zip executable")
    endif()

    if(NOT CMAKE_SEVEN_ZIP_COMMAND)
        message(FATAL_ERROR "Boost v${BOOST_VERSION} is distributed as a .7z archive, but the 7z executable was not found in your PATH. Please install 7-Zip and ensure it is available in your system's PATH.")
    else()
        message(STATUS "Found 7-Zip executable for .7z extraction: ${CMAKE_SEVEN_ZIP_COMMAND}")
    endif()
endif()

if(BOOST_BUILD_SYSTEM STREQUAL "cmake")
    message(STATUS "Boost v${BOOST_VERSION}: Using CMake build system.")
    include(${CMAKE_CURRENT_LIST_DIR}/BoostCmake.cmake)
elseif(BOOST_BUILD_SYSTEM STREQUAL "b2")
    message(STATUS "Boost v${BOOST_VERSION}: Using b2 build system.")
    include(${CMAKE_CURRENT_LIST_DIR}/BoostB2.cmake)
else()
    message(FATAL_ERROR "Unknown build system '${BOOST_BUILD_SYSTEM}' defined for Boost v${BOOST_VERSION} in cmake/BoostUrls.cmake.")
endif()

if(NOT TARGET boost_external)
    message(FATAL_ERROR "Boost build script failed to create 'boost_external' target. This should not happen.")
endif()

if(NOT TARGET Zano::boost_libs)
    add_library(zano_boost_libs INTERFACE)
    add_library(Zano::boost_libs ALIAS zano_boost_libs)
endif()
target_link_libraries(zano_boost_libs INTERFACE ${Boost_LIBRARIES})

if(TARGET OpenSSL::SSL)
    target_link_libraries(zano_boost_libs INTERFACE OpenSSL::SSL)
endif()

if(TARGET ICU::i18n)
    get_target_property(icu_include_dir ICU::i18n INTERFACE_INCLUDE_DIRECTORIES)
    if(icu_include_dir)
        target_include_directories(zano_boost_libs INTERFACE ${icu_include_dir})
    endif()
    target_link_libraries(zano_boost_libs INTERFACE ICU::i18n ICU::uc ICU::data)
    if(NOT APPLE) # Linux needs 'dl' for ICU
        target_link_libraries(zano_boost_libs INTERFACE dl)
    else() # Apple needs 'iconv' for Boost.Locale
        target_link_libraries(zano_boost_libs INTERFACE iconv)
    endif()
endif()

add_dependencies(zano_boost_libs boost_external)
add_dependencies(build_sdk boost_external)

set(Boost_FOUND TRUE)
