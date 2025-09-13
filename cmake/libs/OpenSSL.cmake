include_guard(GLOBAL)

include(ExternalProject)
include(libs/OpenSSLUrls)

# --- Configuration ---
if(NOT DEFINED OPENSSL_VERSION)
    set(OPENSSL_VERSION "3.3.0" CACHE STRING "The version of OpenSSL to download and build")
endif()

option(OPENSSL_USE_SYSTEM "Use system-installed OpenSSL" OFF)

if(OPENSSL_USE_SYSTEM)
    message(STATUS "Attempting to use system-installed OpenSSL...")
    find_package(OpenSSL REQUIRED)
    message(STATUS "Found system-installed OpenSSL: ${OpenSSL_VERSION}")
    # find_package(OpenSSL) creates the OpenSSL::SSL and OpenSSL::Crypto targets we need.
    set(OpenSSL_FOUND TRUE)
    return()
endif()

# --- Pre-compiled Cache Configuration ---
option(FORCE_BUILD_OPENSSL "Force building OpenSSL from source, ignoring pre-compiled caches." OFF)
option(REQUIRE_PRECOMPILED_OPENSSL "Fail the build if a pre-compiled OpenSSL cache cannot be downloaded and used." OFF)

# --- Platform and SDK Path Calculation ---
# PLATFORM_ID is now determined in the main sdk.cmake file.
set(OPENSSL_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build/sdk/${PLATFORM_ID}/openssl)
set(OPENSSL_WORK_DIR ${DEP_WORK_ROOT}/openssl)

# --- Makefile Integration ---
set(MAKEFILE_VARS_CONTENT "
OPENSSL_VERSION_FOR_PACKAGING := ${OPENSSL_VERSION}\n\nDEP_PLATFORM_ID_FOR_PACKAGING := ${PLATFORM_ID}\n\nOPENSSL_SDK_DIR_FOR_PACKAGING := ${OPENSSL_INSTALL_PREFIX}\n\n")
file(WRITE "${CMAKE_BINARY_DIR}/openssl_packaging.vars" "${MAKEFILE_VARS_CONTENT}")

# --- Define OpenSSL variables ---
set(OpenSSL_INCLUDE_DIRS ${OPENSSL_INSTALL_PREFIX}/include)
file(MAKE_DIRECTORY "${OpenSSL_INCLUDE_DIRS}") # Ensure directory exists for imported targets

# Set the base names for the OpenSSL libraries.
set(_openssl_crypto_lib_name "libcrypto")
set(_openssl_ssl_lib_name "libssl")

if(NOT TARGET OpenSSL::Crypto)
    add_library(OpenSSL::Crypto ${SDK_LIB_TYPE} IMPORTED GLOBAL)
    set_target_properties(OpenSSL::Crypto PROPERTIES
        IMPORTED_LOCATION "${OPENSSL_INSTALL_PREFIX}/lib/${_openssl_crypto_lib_name}${SDK_LIB_SUFFIX}"
        INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL_INCLUDE_DIRS}"
    )
endif()

if(NOT TARGET OpenSSL::SSL)
    add_library(OpenSSL::SSL ${SDK_LIB_TYPE} IMPORTED GLOBAL)
    set_target_properties(OpenSSL::SSL PROPERTIES
        IMPORTED_LOCATION "${OPENSSL_INSTALL_PREFIX}/lib/${_openssl_ssl_lib_name}${SDK_LIB_SUFFIX}"
        INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL_INCLUDE_DIRS}"
    )
    # SSL depends on Crypto
    set_property(TARGET OpenSSL::SSL APPEND PROPERTY INTERFACE_LINK_LIBRARIES OpenSSL::Crypto)
endif()

set(OpenSSL_LIBRARIES OpenSSL::SSL OpenSSL::Crypto)

# --- Check for existing valid installation ---
if(NOT FORCE_BUILD_OPENSSL)
    if(EXISTS "${OPENSSL_INSTALL_PREFIX}/include/openssl/ssl.h" AND EXISTS "${OPENSSL_INSTALL_PREFIX}/lib/${_openssl_ssl_lib_name}${SDK_LIB_SUFFIX}" AND EXISTS "${OPENSSL_INSTALL_PREFIX}/lib/${_openssl_crypto_lib_name}${SDK_LIB_SUFFIX}")
        message(STATUS "Found complete pre-installed OpenSSL in SDK: ${OPENSSL_INSTALL_PREFIX}")
        set(OpenSSL_FOUND TRUE)
        return()
    endif()

    # --- Download from pre-compiled cache ---
    if(PRECOMPILED_CACHE_URL)
        if(REQUIRE_PRECOMPILED_OPENSSL)
            sdk_download_and_extract_cache(OPENSSL ${OPENSSL_VERSION} ${OPENSSL_INSTALL_PREFIX} REQUIRE_PRECOMPILED)
        else()
            sdk_download_and_extract_cache(OPENSSL ${OPENSSL_VERSION} ${OPENSSL_INSTALL_PREFIX})
        endif()

        if(CACHE_DOWNLOAD_SUCCESS)
            set(OpenSSL_FOUND TRUE)
            return() # Success!
        endif()
    endif()
endif()

# --- Build from Source ---
message(STATUS "Building OpenSSL ${OPENSSL_VERSION} from source...")

string(REPLACE "." "_" OPENSSL_VERSION_SUFFIX ${OPENSSL_VERSION})
set(OPENSSL_SHA256 ${OPENSSL_VERSION_${OPENSSL_VERSION_SUFFIX}_SHA256})
set(OPENSSL_URL ${OPENSSL_VERSION_${OPENSSL_VERSION_SUFFIX}_URLS})

if(NOT OPENSSL_URL)
    message(FATAL_ERROR "Source URLs for OpenSSL version ${OPENSSL_VERSION} are not defined in cmake/OpenSSLUrls.cmake.")
endif()

# --- Configure command for different platforms ---
set(OPENSSL_EXTRA_CONFIGURE_FLAGS "")
if(WIN32)
    set(OPENSSL_CONFIGURE_TARGET "VC-WIN64A")
    if(DEFINED ENV{PERL_EXECUTABLE})
        set(PERL_EXECUTABLE "$ENV{PERL_EXECUTABLE}")
        message(STATUS "OpenSSL Build: Using PERL_EXECUTABLE from environment: ${PERL_EXECUTABLE}")
    else()
        find_program(PERL_EXECUTABLE perl REQUIRED)
    endif()
    set(CONFIGURE_COMMAND ${PERL_EXECUTABLE} <SOURCE_DIR>/Configure)
    # On Windows, the environment for ExternalProject_Add can be sparse.
    # We need to ensure the Perl interpreter can find modules.
    # The OpenSSL source includes some modules, and we add this path to PERL5LIB
    # to help resolve dependencies like Locale::Maketext::Simple.
    set(CONFIGURE_COMMAND ${CMAKE_COMMAND} -E env "PERL5LIB=<SOURCE_DIR>/util/perl" ${CONFIGURE_COMMAND})
elseif(APPLE)
    if(CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
        set(OPENSSL_CONFIGURE_TARGET "darwin64-arm64-cc")
    else()
        set(OPENSSL_CONFIGURE_TARGET "darwin64-x86_64-cc")
    endif()
    set(CONFIGURE_COMMAND perl <SOURCE_DIR>/Configure)
else() # Linux
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(OPENSSL_CONFIGURE_TARGET "linux-aarch64")
    else()
        set(OPENSSL_CONFIGURE_TARGET "linux-x86_64")
    endif()
    set(CONFIGURE_COMMAND <SOURCE_DIR>/config)
    # On 64-bit Linux, the default libdir is often 'lib64', but our project expects 'lib'.
    # Explicitly set the libdir to ensure consistency.
    list(APPEND OPENSSL_EXTRA_CONFIGURE_FLAGS --libdir=<INSTALL_DIR>/lib)
endif()

include(ProcessorCount)
ProcessorCount(NPROC)
if(NPROC EQUAL 0)
    set(NPROC 1)
endif()

if(BUILD_SHARED_LIBS)
    set(_OPENSSL_BUILD_TYPE "shared")
else()
    set(_OPENSSL_BUILD_TYPE "no-shared")
endif()

if(WIN32)
    set(_jobs_flag "-m:")
else()
    set(_jobs_flag "-j")
endif()

# For non-Windows platforms, we need to pass compiler/linker flags via env vars.
if(NOT WIN32)
    set(OPENSSL_C_FLAGS "${CMAKE_C_FLAGS}")
    set(OPENSSL_LD_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
    if(APPLE AND CMAKE_OSX_SYSROOT)
        message(STATUS "OpenSSL Build: Using sysroot ${CMAKE_OSX_SYSROOT}")
        set(OPENSSL_C_FLAGS "${OPENSSL_C_FLAGS} -isysroot ${CMAKE_OSX_SYSROOT}")
        set(OPENSSL_LD_FLAGS "${OPENSSL_LD_FLAGS} -isysroot ${CMAKE_OSX_SYSROOT}")
    endif()
    set(CONFIGURE_COMMAND ${CMAKE_COMMAND} -E env "CC=${CMAKE_C_COMPILER}" "CFLAGS=${OPENSSL_C_FLAGS}" "LDFLAGS=${OPENSSL_LD_FLAGS}" ${CONFIGURE_COMMAND})
endif()

ExternalProject_Add(openssl_external
    URL                 ${OPENSSL_URL}
    URL_HASH            SHA256=${OPENSSL_SHA256}
    DOWNLOAD_DIR        ${SDK_CACHE_DIR}
    INSTALL_DIR         ${OPENSSL_INSTALL_PREFIX}
    PREFIX              ${OPENSSL_WORK_DIR}
    EXCLUDE_FROM_ALL    1

    CONFIGURE_COMMAND   ${CONFIGURE_COMMAND}
                        ${_OPENSSL_BUILD_TYPE}
                        no-tests
                        --prefix=<INSTALL_DIR>
                        --openssldir=<INSTALL_DIR>
                        ${OPENSSL_CONFIGURE_TARGET}
                        ${OPENSSL_EXTRA_CONFIGURE_FLAGS}

    BUILD_COMMAND       ${CMAKE_MAKE_PROGRAM} ${_jobs_flag}${NPROC}
    INSTALL_COMMAND     ${CMAKE_MAKE_PROGRAM} install_sw # install_sw installs libs and headers only
)

add_dependencies(OpenSSL::Crypto openssl_external)
add_dependencies(OpenSSL::SSL openssl_external)

# Add to the main SDK build target
add_dependencies(build_sdk openssl_external)

set(OpenSSL_FOUND TRUE)
