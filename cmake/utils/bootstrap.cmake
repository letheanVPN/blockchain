# cmake/bootstrap.cmake
#
# Determines which CMake executable to use for the build.
# 1. If the system's CMake is sufficient, it will be used.
# 2. If not, a pinned version will be downloaded and used.
#
# This script generates a makefile fragment (`build/cmake.mk`) that the main
# Makefile includes, defining the `CMAKE` variable.
#
# Required -D variables:
#   - CMAKE_WANTED_VERSION: The minimum required version of CMake.
#   - BUILD_ROOT: The root directory for all build artifacts.

if(NOT DEFINED CMAKE_WANTED_VERSION OR NOT DEFINED BUILD_ROOT)
    message(FATAL_ERROR "CMAKE_WANTED_VERSION and BUILD_ROOT must be defined.")
endif()
if(NOT DEFINED CMAKE_MK_FILE_OUT OR NOT DEFINED NPROC_MK_FILE_OUT)
    message(FATAL_ERROR "This script should be called from the Makefile which defines CMAKE_MK_FILE_OUT and NPROC_MK_FILE_OUT.")
endif()

set(TOOLS_DIR "${BUILD_ROOT}/sdk/tools")
set(CMAKE_COMMAND_TO_USE "")


# --- Set Default Generator if not defined ---

# --- Logic ---

# 1. Check system CMake
if(CMAKE_COMMAND AND CMAKE_VERSION VERSION_GREATER_EQUAL CMAKE_WANTED_VERSION)
    message(STATUS "System CMake (${CMAKE_VERSION}) is sufficient. Using it from system PATH.")
    set(CMAKE_COMMAND_TO_USE "${CMAKE_COMMAND}")
else()
    # System CMake is insufficient or not found. Use local bootstrapped version.
    if(CMAKE_COMMAND)
        message(WARNING "System CMake version ${CMAKE_VERSION} is too old. Required >= ${CMAKE_WANTED_VERSION}.")
    else()
        message(STATUS "No suitable system CMake found.")
    endif()

    set(LOCAL_CMAKE_INSTALL_DIR "${TOOLS_DIR}/cmake-${CMAKE_WANTED_VERSION}")
    if(WIN32)
        set(LOCAL_CMAKE_EXE "${LOCAL_CMAKE_INSTALL_DIR}/bin/cmake.exe")
    else()
        set(LOCAL_CMAKE_EXE "${LOCAL_CMAKE_INSTALL_DIR}/bin/cmake")
    endif()

    set(CMAKE_COMMAND_TO_USE "${LOCAL_CMAKE_EXE}")

    # 2. If local version already exists, we're done with this branch.
    if(EXISTS "${LOCAL_CMAKE_EXE}")
        message(STATUS "Found local CMake v${CMAKE_WANTED_VERSION}. Using it.")
    else()
        # 3. Download and unpack
        message(STATUS "Bootstrapping CMake v${CMAKE_WANTED_VERSION}...")

        # --- Platform Detection ---
        if(WIN32)
            set(OS_NAME "windows")
            set(ARCH_NAME "x86_64")
            set(ARCHIVE_EXT "zip")
        elseif(APPLE)
            set(OS_NAME "macos")
            set(ARCH_NAME "universal")
            set(ARCHIVE_EXT "tar.gz")
        elseif(UNIX)
            set(OS_NAME "linux")
            execute_process(COMMAND uname -m OUTPUT_VARIABLE ARCH_NAME OUTPUT_STRIP_TRAILING_WHITESPACE)
            set(ARCHIVE_EXT "tar.gz")
        else()
            message(FATAL_ERROR "Unsupported operating system for CMake bootstrapping.")
        endif()

        # --- Construct Paths and URL ---
        set(CMAKE_PLATFORM "${OS_NAME}-${ARCH_NAME}")
        set(CMAKE_URL "https://github.com/Kitware/CMake/releases/download/v${CMAKE_WANTED_VERSION}/cmake-${CMAKE_WANTED_VERSION}-${CMAKE_PLATFORM}.${ARCHIVE_EXT}")
        set(CMAKE_ARCHIVE_PATH "${TOOLS_DIR}/cmake_bootstrap.${ARCHIVE_EXT}")
        set(CMAKE_UNPACK_DIR_TMP "${TOOLS_DIR}/cmake-${CMAKE_WANTED_VERSION}-${CMAKE_PLATFORM}")

        file(MAKE_DIRECTORY "${TOOLS_DIR}")

        # --- Download ---
        message(STATUS "Downloading CMake v${CMAKE_WANTED_VERSION} for ${CMAKE_PLATFORM}...")
        message(STATUS "URL: ${CMAKE_URL}")
        file(DOWNLOAD "${CMAKE_URL}" "${CMAKE_ARCHIVE_PATH}" SHOW_PROGRESS STATUS download_status LOG log)
        if(NOT download_status EQUAL 0)
            message(FATAL_ERROR "Failed to download CMake from ${CMAKE_URL}.\n"
                                "Please check your internet connection or firewall settings.\n"
                                "You can also try downloading it manually and unpacking it to '${LOCAL_CMAKE_INSTALL_DIR}'.\n"
                                "Download log: ${log}")
        endif()

        # --- Unpack ---
        message(STATUS "Unpacking CMake...")
        get_filename_component(ARCHIVE_FILENAME "${CMAKE_ARCHIVE_PATH}" NAME)
        execute_process(
            COMMAND "${CMAKE_COMMAND}" -E tar "xf" "${ARCHIVE_FILENAME}"
            WORKING_DIRECTORY "${TOOLS_DIR}"
            RESULT_VARIABLE unpack_result
            ERROR_VARIABLE unpack_error
        )
        if(NOT unpack_result EQUAL 0)
            message(FATAL_ERROR "Failed to unpack CMake archive '${CMAKE_ARCHIVE_PATH}'.\n"
                                "Error: ${unpack_error}")
        endif()

        # --- Finalize and Clean Up ---
        file(RENAME "${CMAKE_UNPACK_DIR_TMP}" "${LOCAL_CMAKE_INSTALL_DIR}")
        file(REMOVE "${CMAKE_ARCHIVE_PATH}")
        message(STATUS "CMake bootstrap complete. Local CMake is ready.")
    endif()
endif()

# --- Output ---
# Write the makefile fragment that the main Makefile will include. The path is
# always kept with forward slashes, as this is more portable across different
# `make` implementations, especially on Windows.
set(CMAKE_COMMAND_TO_USE_NATIVE "${CMAKE_COMMAND_TO_USE}") # Default to the long path

if(WIN32)
    # On Windows, GnuWin32/make can struggle with paths containing spaces.
    # We attempt to get the 8.3 "short path" to avoid this issue.
    execute_process(
        COMMAND cmd /c "for %A in (\"${CMAKE_COMMAND_TO_USE}\") do @echo %~sA"
        OUTPUT_VARIABLE CMAKE_SHORT_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    # Use the short path only if it was found and doesn't contain spaces.
    if(CMAKE_SHORT_PATH AND NOT CMAKE_SHORT_PATH MATCHES " ")
        message(STATUS "Using short path for Windows compatibility: ${CMAKE_SHORT_PATH}")
        set(CMAKE_COMMAND_TO_USE_NATIVE "${CMAKE_SHORT_PATH}")
    endif()
endif()

# Convert to forward slashes for better portability in the Makefile
file(TO_CMAKE_PATH "${CMAKE_COMMAND_TO_USE_NATIVE}" CMAKE_COMMAND_TO_USE_NATIVE)

file(WRITE "${CMAKE_MK_FILE_OUT}" "CMAKE := \"${CMAKE_COMMAND_TO_USE_NATIVE}\"\n")
message(STATUS "Build will use CMake at: ${CMAKE_COMMAND_TO_USE_NATIVE}")

# --- Determine Processor Count ---
include(ProcessorCount)
ProcessorCount(CORE_COUNT)

file(WRITE "${NPROC_MK_FILE_OUT}" "NPROC := ${CORE_COUNT}\n")
message(STATUS "Parallel builds will use up to ${CORE_COUNT} cores.")