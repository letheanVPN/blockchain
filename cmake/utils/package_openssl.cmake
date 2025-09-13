# This script packages the built OpenSSL SDK into a .tar.gz archive.

if(NOT DEFINED OPENSSL_VERSION)
    message(FATAL_ERROR "OPENSSL_VERSION must be defined.")
endif()

if(NOT DEFINED OPENSSL_SDK_DIR)
    message(FATAL_ERROR "OPENSSL_SDK_DIR must be defined.")
endif()

if(NOT DEFINED PLATFORM_ID)
    message(FATAL_ERROR "PLATFORM_ID must be defined.")
endif()

set(ARCHIVE_NAME "openssl-${OPENSSL_VERSION}-${PLATFORM_ID}.tar.gz")
set(ARCHIVE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}")

if(NOT EXISTS "${OPENSSL_SDK_DIR}/include/openssl/ssl.h")
    message(FATAL_ERROR "OpenSSL SDK not found at ${OPENSSL_SDK_DIR}. Run 'make build_sdk' first.")
endif()

message(STATUS "Packaging OpenSSL SDK from: ${OPENSSL_SDK_DIR}")
message(STATUS "Creating archive: ${ARCHIVE_OUTPUT_PATH}")

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar "czf" "${ARCHIVE_OUTPUT_PATH}" "."
    WORKING_DIRECTORY ${OPENSSL_SDK_DIR}
    RESULT_VARIABLE TAR_RESULT
)

if(NOT TAR_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to create OpenSSL archive.")
else()
    message(STATUS "Successfully created ${ARCHIVE_NAME}")
endif()
