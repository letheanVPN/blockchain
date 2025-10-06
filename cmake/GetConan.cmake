# cmake/GetConan.cmake

# This module downloads and installs Conan if it's not found.

# Set the Conan version
set(CONAN_VERSION 2.21.0)

# Set the download URLs
set(CONAN_URL_MACOS_ARM "https://github.com/conan-io/conan/releases/download/${CONAN_VERSION}/conan-${CONAN_VERSION}-macos-arm64.tgz")
set(CONAN_URL_MACOS_INTEL "https://github.com/conan-io/conan/releases/download/${CONAN_VERSION}/conan-${CONAN_VERSION}-macos-x86_64.tgz")
set(CONAN_URL_WINDOWS_X86_64 "https://github.com/conan-io/conan/releases/download/${CONAN_VERSION}/conan-${CONAN_VERSION}-windows-x86_64.zip")
set(CONAN_URL_WINDOWS_ARM64 "https://github.com/conan-io/conan/releases/download/${CONAN_VERSION}/conan-${CONAN_VERSION}-windows-arm64.zip")
set(CONAN_URL_LINUX_X86_64 "https://github.com/conan-io/conan/releases/download/${CONAN_VERSION}/conan-${CONAN_VERSION}-linux-x86_64.tgz")
set(CONAN_URL_LINUX_AARCH64 "https://github.com/conan-io/conan/releases/download/${CONAN_VERSION}/conan-${CONAN_VERSION}-linux-aarch64.tgz")
set(CONAN_INSTALL_DIR "${CMAKE_SOURCE_DIR}/build")
# Set the installation directory
if(NOT CMAKE_BINARY_DIR)
  set(CMAKE_BINARY_DIR "${CONAN_INSTALL_DIR}")
endif()

set(CONAN_EXECUTABLE "${CONAN_INSTALL_DIR}/bin/conan")

# Check if Conan is already installed
if(NOT EXISTS "${CONAN_EXECUTABLE}")
  message(STATUS "Conan not found. Downloading and installing...")

  file(MAKE_DIRECTORY "${CONAN_INSTALL_DIR}")

  # Detect the operating system and architecture
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
      set(CONAN_URL ${CONAN_URL_MACOS_ARM})
      set(CONAN_ARCHIVE_TYPE "tgz")
    else()
      set(CONAN_URL ${CONAN_URL_MACOS_INTEL})
      set(CONAN_ARCHIVE_TYPE "tgz")
    endif()
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "ARM64")
      set(CONAN_URL ${CONAN_URL_WINDOWS_ARM64})
      set(CONAN_ARCHIVE_TYPE "zip")
    else()
      set(CONAN_URL ${CONAN_URL_WINDOWS_X86_64})
      set(CONAN_ARCHIVE_TYPE "zip")
    endif()
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
      set(CONAN_URL ${CONAN_URL_LINUX_AARCH64})
      set(CONAN_ARCHIVE_TYPE "tgz")
    else()
      set(CONAN_URL ${CONAN_URL_LINUX_X86_64})
      set(CONAN_ARCHIVE_TYPE "tgz")
    endif()
  else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_HOST_SYSTEM_NAME}")
  endif()

  # Download and extract Conan
  set(CONAN_ARCHIVE "${CMAKE_BINARY_DIR}/conan.${CONAN_ARCHIVE_TYPE}")

  message(STATUS "Downloading ${CONAN_URL} to ${CONAN_ARCHIVE}")
  file(DOWNLOAD "${CONAN_URL}" "${CONAN_ARCHIVE}" SHOW_PROGRESS)

  message(STATUS "Extracting ${CONAN_ARCHIVE} to ${CONAN_INSTALL_DIR}")
  if(CONAN_ARCHIVE_TYPE STREQUAL "tgz")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xzf "${CONAN_ARCHIVE}"
      WORKING_DIRECTORY "${CONAN_INSTALL_DIR}"
      RESULT_VARIABLE result
    )
  elseif(CONAN_ARCHIVE_TYPE STREQUAL "zip")
    # Cmake -E tar can handle zip files
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xf "${CONAN_ARCHIVE}"
      WORKING_DIRECTORY "${CONAN_INSTALL_DIR}"
      RESULT_VARIABLE result
    )
  endif()

  if(NOT result EQUAL 0)
    message(FATAL_ERROR "Failed to extract Conan archive.")
  endif()

  # Clean up the archive
  file(REMOVE "${CONAN_ARCHIVE}")

  message(STATUS "Conan installed successfully in ${CONAN_INSTALL_DIR}/conan")
else()
  message(STATUS "Conan already installed in ${CONAN_INSTALL_DIR}/conan")
endif()
