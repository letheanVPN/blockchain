# C:/Users/snide/CLionProjects/snider/blockchain/cmake/package_boost.cmake
#
# Packages the pre-built Boost library.
# Cross-platform replacement for the shell logic in the 'package-boost' make target.
#
# Usage:
#   cmake -D BOOST_VERSION=<ver> -D BOOST_SDK_DIR=<path> -D PLATFORM_ID=<id> -P cmake/package_boost.cmake

if(NOT DEFINED BOOST_VERSION OR "${BOOST_VERSION}" STREQUAL "")
    message(FATAL_ERROR "Error: Project not configured. Run 'make configure' first to generate packaging variables.")
endif()

if(NOT IS_DIRECTORY "${BOOST_SDK_DIR}")
    message(FATAL_ERROR "Error: Boost SDK directory not found at ${BOOST_SDK_DIR}.\nHint: Run 'make build_sdk' to build it first.")
endif()

get_filename_component(BOOST_SDK_PARENT_DIR "${BOOST_SDK_DIR}" DIRECTORY)
get_filename_component(BOOST_SDK_NAME "${BOOST_SDK_DIR}" NAME)

set(PACKAGE_NAME "boost-${BOOST_VERSION}-${PLATFORM_ID}.tar.gz")

message(STATUS "--- Packaging Boost SDK ---")
message(STATUS "Creating package: ${PACKAGE_NAME}")

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar "czf" "${PACKAGE_NAME}" "${BOOST_SDK_NAME}"
    WORKING_DIRECTORY "${BOOST_SDK_PARENT_DIR}"
    RESULT_VARIABLE TAR_RESULT
)

if(NOT TAR_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to create package.")
else()
    message(STATUS "Package created successfully: ${PACKAGE_NAME}")
endif()