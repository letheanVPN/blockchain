# C:/Users/snide/CLionProjects/snider/blockchain/cmake/utils/run_tests.cmake
#
# Reads the last build directory from build/.last_build_dir and runs the 'test' target.
# Cross-platform replacement for the shell logic in the 'test' make target.

set(LAST_BUILD_FILE "build/.last_build_dir")

if(NOT EXISTS "${LAST_BUILD_FILE}")
    message(FATAL_ERROR "Error: No build has been run. Use 'make release' or 'make debug' first.")
endif()

file(READ "${LAST_BUILD_FILE}" LAST_BUILD_DIR)
string(STRIP "${LAST_BUILD_DIR}" LAST_BUILD_DIR)

if(NOT IS_DIRECTORY "${LAST_BUILD_DIR}")
    message(FATAL_ERROR "Error: Last build directory '${LAST_BUILD_DIR}' not found.")
endif()

message(STATUS "--- Running tests in ${LAST_BUILD_DIR} ---")
execute_process(
    COMMAND ${CMAKE_COMMAND} --build ${LAST_BUILD_DIR} --target test
    RESULT_VARIABLE TEST_RESULT
)

if(NOT TEST_RESULT EQUAL 0)
    message(FATAL_ERROR "Tests failed.")
endif()