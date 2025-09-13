include_guard(GLOBAL)


# --- SDK Build Options ---
option(USE_SYSTEM_DEPS "Use system-provided dependencies (Boost, OpenSSL, etc.)" OFF)
option(USE_SDK_CACHE "Use pre-compiled dependency cache if available" ON)
option(REQUIRE_PRECOMPILED "Fail the build if pre-compiled dependencies are not available" OFF)

# This option is kept from the original file
option(BUILD_SHARED_LIBS "Build dependencies as shared libraries" OFF)

# Create a single target that represents all SDK dependencies.
# This allows other targets to depend on the entire SDK being ready.
if(NOT TARGET build_sdk)
    add_custom_target(build_sdk)
endif()

# If using system dependencies, find them and return.
if(USE_SYSTEM_DEPS)
    cmake_policy(SET CMP0144 OLD)
    message(STATUS "[sdk.cmake] USE_SYSTEM_DEPS is ON. Finding system dependencies.")

    # --- Find OpenSSL ---
    find_package(OpenSSL REQUIRED)
    message(STATUS "Found OpenSSL: ${OPENSSL_VERSION}")

    # --- Find Boost ---
    set(ZANO_BOOST_COMPONENTS "filesystem;thread;timer;date_time;chrono;regex;serialization;atomic;program_options")
    # The linker errors show that boost::locale is required, so we must include it on Windows.
    if(NOT CMAKE_SYSTEM_NAME STREQUAL "Android" OR CAKEWALLET)
      list(APPEND ZANO_BOOST_COMPONENTS locale)
    endif()
    if(NOT (CMAKE_SYSTEM_NAME STREQUAL "Android"))
      list(APPEND ZANO_BOOST_COMPONENTS log log_setup)
    endif()

    if(STATIC)
        set(Boost_USE_STATIC_LIBS ON)
        set(Boost_USE_STATIC_RUNTIME ON)
    endif()
    if(POLICY CMP0167)
        cmake_policy(SET CMP0167 OLD)
    endif()
    find_package(Boost 1.86.0 REQUIRED COMPONENTS ${ZANO_BOOST_COMPONENTS})
    if(Boost_FOUND)
        message(STATUS "Found Boost: ${Boost_VERSION}")
    endif()

    return()
endif()

# --- From this point, we are building the SDK ourselves ---
message(STATUS "[sdk.cmake] USE_SYSTEM_DEPS is OFF. Building SDK from source or cache.")

#
# Downloads and extracts a pre-compiled dependency from a cache.
#
function(sdk_download_and_extract_cache DEP_NAME DEP_VERSION INSTALL_PREFIX)
    set(options REQUIRE_PRECOMPILED)
    cmake_parse_arguments(ARG "${options}" "" "" ${ARGN})

    string(TOLOWER "${DEP_NAME}" _dep_name_lower)
    set(CACHE_FILENAME "${_dep_name_lower}-${DEP_VERSION}-${PLATFORM_ID}.tar.gz")
    set(CACHE_URL "${PRECOMPILED_CACHE_URL}/${CACHE_FILENAME}")

    string(REPLACE "." "_" VERSION_SUFFIX ${DEP_VERSION})
    string(REPLACE "-" "_" PLATFORM_ID_SUFFIX ${PLATFORM_ID})
    set(EXPECTED_CACHE_HASH ${${DEP_NAME}_VERSION_${VERSION_SUFFIX}_CACHE_SHA256_${PLATFORM_ID_SUFFIX}})

    if(NOT EXPECTED_CACHE_HASH)
        if(ARG_REQUIRE_PRECOMPILED)
            message(FATAL_ERROR "Required pre-compiled ${DEP_NAME}, but no cache hash is defined for ${DEP_NAME} ${DEP_VERSION} on platform ${PLATFORM_ID}.")
        else()
            message(STATUS "Skipping pre-compiled cache for ${DEP_NAME} ${DEP_VERSION} on ${PLATFORM_ID}: no hash defined.")
            set(CACHE_DOWNLOAD_SUCCESS FALSE PARENT_SCOPE)
            return()
        endif()
    endif()

    file(MAKE_DIRECTORY ${SDK_CACHE_DIR})
    set(CACHE_FILE "${SDK_CACHE_DIR}/${CACHE_FILENAME}")

    message(STATUS "Attempting to download pre-compiled ${DEP_NAME} for ${PLATFORM_ID} from ${CACHE_URL}")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E download "${CACHE_URL}" "${CACHE_FILE}"
        RESULT_VARIABLE DOWNLOAD_RESULT
        OUTPUT_QUIET
        ERROR_VARIABLE DOWNLOAD_ERROR_MSG
    )

    if(DOWNLOAD_RESULT EQUAL 0)
        file(SHA256 ${CACHE_FILE} ACTUAL_CACHE_HASH)
        if(NOT ACTUAL_CACHE_HASH STREQUAL EXPECTED_CACHE_HASH)
            set(DOWNLOAD_RESULT 1)
            set(DOWNLOAD_ERROR_MSG "Hash mismatch for ${CACHE_FILE}. Expected ${EXPECTED_CACHE_HASH}, got ${ACTUAL_CACHE_HASH}.")
            file(REMOVE ${CACHE_FILE})
        endif()
    endif()

    if(DOWNLOAD_RESULT EQUAL 0)
        message(STATUS "Extracting ${CACHE_FILE}...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${CACHE_FILE}
            WORKING_DIRECTORY ${INSTALL_PREFIX}/..
            RESULT_VARIABLE EXTRACT_RESULT
        )
        if(EXTRACT_RESULT EQUAL 0)
            message(STATUS "Successfully downloaded and extracted pre-compiled ${DEP_NAME}.")
            set(CACHE_DOWNLOAD_SUCCESS TRUE PARENT_SCOPE)
            return()
        else()
            if(ARG_REQUIRE_PRECOMPILED)
                message(FATAL_ERROR "Failed to extract required pre-compiled ${DEP_NAME} archive: ${CACHE_FILE}. Error code: ${EXTRACT_RESULT}")
            else()
                message(WARNING "Failed to extract pre-compiled ${DEP_NAME} archive: ${CACHE_FILE}. Error code: ${EXTRACT_RESULT}. Falling back to source build.")
            endif()
        endif()
    else()
        if(ARG_REQUIRE_PRECOMPILED)
            message(FATAL_ERROR "Could not download required pre-compiled ${DEP_NAME}: ${DOWNLOAD_ERROR_MSG}")
        else()
            message(STATUS "Could not download pre-compiled ${DEP_NAME}: ${DOWNLOAD_ERROR_MSG}. Falling back to source build.")
        endif()
    endif()

    set(CACHE_DOWNLOAD_SUCCESS FALSE PARENT_SCOPE)
endfunction()

# --- Global SDK Configuration ---
set(PRECOMPILED_CACHE_URL "https://github.com/letheanVPN/blockchain/releases/download/prebuilt-deps" CACHE STRING "Base URL for pre-compiled dependency packages")
set(SDK_CACHE_DIR ${CMAKE_SOURCE_DIR}/build/sdk/_cache)
set(DEP_WORK_ROOT ${CMAKE_SOURCE_DIR}/build/_work)

# --- Platform and SDK Path Calculation ---
if(NOT PLATFORM_ID)
    string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" _COMPILER_ID)
    if(_COMPILER_ID STREQUAL "gnu")
        set(_COMPILER_ID "gcc")
    endif()

    if(MSVC)
        set(_COMPILER_VERSION "${MSVC_VERSION}")
    elseif (APPLE)
        set(_COMPILER_VERSION "${CMAKE_OSX_DEPLOYMENT_TARGET}")
    else()
        string(REGEX MATCH "^[0-9]+" _COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
    endif()

    if(APPLE)
        if(CMAKE_OSX_ARCHITECTURES)
            set(_PLATFORM_ARCH "${CMAKE_OSX_ARCHITECTURES}")
        else()
            string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" _PLATFORM_ARCH)
        endif()
    else()
        if(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
            set(_PLATFORM_ARCH "x64")
        else()
            string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" _PLATFORM_ARCH)
        endif()
    endif()

    if(BUILD_SHARED_LIBS)
        set(_LINK_TYPE "shared")
    else()
        set(_LINK_TYPE "static")
    endif()

    set(PLATFORM_ID "${_COMPILER_ID}-${_COMPILER_VERSION}-${_PLATFORM_ARCH}-${_LINK_TYPE}")
endif()

message(STATUS "[sdk.cmake] Determined Platform ID: ${PLATFORM_ID}")

# --- Global Library Suffix and Type ---
if(BUILD_SHARED_LIBS)
    set(SDK_LIB_TYPE SHARED)
    if(WIN32)
        set(SDK_LIB_SUFFIX ".lib")
    else()
        if(APPLE)
            set(SDK_LIB_SUFFIX ".dylib")
        else()
            set(SDK_LIB_SUFFIX ".so")
        endif()
    endif()
else() # static
    set(SDK_LIB_TYPE STATIC)
    if(MSVC)
        set(SDK_LIB_SUFFIX ".lib")
    else()
        set(SDK_LIB_SUFFIX ".a")
    endif()
endif()

# --- OpenSSL Dependency ---
include(libs/OpenSSL)

# --- Boost Dependency ---
set(ZANO_BOOST_COMPONENTS "filesystem;thread;timer;date_time;chrono;regex;serialization;atomic;program_options")
if((NOT CMAKE_SYSTEM_NAME STREQUAL "Android" OR CAKEWALLET) AND NOT WIN32)
  list(APPEND ZANO_BOOST_COMPONENTS locale)
endif()
if(NOT (CMAKE_SYSTEM_NAME STREQUAL "Android"))
  list(APPEND ZANO_BOOST_COMPONENTS log log_setup)
endif()

set(BOOST_LIBS_TO_BUILD "system;${ZANO_BOOST_COMPONENTS}")
set(BOOST_VERSION "1.86.0" CACHE STRING "The version of Boost to download and build")
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()
include(libs/Boost)

message(STATUS "Using Boost: ${Boost_VERSION} from ${Boost_LIBRARY_DIRS}")
include_directories(${Boost_INCLUDE_DIRS})

# --- Cache Cleaning Target ---
add_custom_target(clean_sdk_cache
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${SDK_CACHE_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${DEP_WORK_ROOT}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/build/sdk
    COMMENT "Cleaning all dependency caches and installed SDKs. Re-run CMake and your build after this."
)
