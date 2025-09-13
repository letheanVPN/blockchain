# This script is executed by the TEST_COMMAND of the boost_external project.
# It verifies that the newly installed Boost is usable.

message(STATUS "--- Starting Boost installation verification ---")
message(STATUS "[VerifyBoost.cmake] CMAKE_OSX_ARCHITECTURES is set to: ${CMAKE_OSX_ARCHITECTURES}")

message(STATUS "")
message(STATUS "Verification script inputs:")
message(STATUS "  - TEST_BOOST_INSTALL_PREFIX: ${TEST_BOOST_INSTALL_PREFIX}")
message(STATUS "  - TEST_BOOST_WORK_DIR:     ${TEST_BOOST_WORK_DIR}")
message(STATUS "  - TEST_BOOST_LIBS_STRING:  ${TEST_BOOST_LIBS_STRING}")
message(STATUS "  - TEST_BOOST_VERSION:      ${TEST_BOOST_VERSION}")
if(DEFINED TEST_ICU_ROOT)
    message(STATUS "  - TEST_ICU_ROOT:           ${TEST_ICU_ROOT}")
endif()

message(STATUS "Forwarded build configuration:")
if(TEST_CMAKE_GENERATOR)
    message(STATUS "  - CMAKE_GENERATOR:           ${TEST_CMAKE_GENERATOR}")
endif()
if(CMAKE_BUILD_TYPE)
    message(STATUS "  - CMAKE_BUILD_TYPE:          ${CMAKE_BUILD_TYPE}")
endif()
if(CMAKE_TOOLCHAIN_FILE AND EXISTS "${CMAKE_TOOLCHAIN_FILE}")
    message(STATUS "  - CMAKE_TOOLCHAIN_FILE:      ${CMAKE_TOOLCHAIN_FILE}")
endif()
if(APPLE)
    if(DEFINED CMAKE_OSX_ARCHITECTURES)
        message(STATUS "  - CMAKE_OSX_ARCHITECTURES:   ${CMAKE_OSX_ARCHITECTURES}")
    endif()
    if(DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
        message(STATUS "  - CMAKE_OSX_DEPLOYMENT_TARGET: ${CMAKE_OSX_DEPLOYMENT_TARGET}")
    endif()
    if(DEFINED CMAKE_OSX_SYSROOT AND EXISTS "${CMAKE_OSX_SYSROOT}")
        message(STATUS "  - CMAKE_OSX_SYSROOT:         ${CMAKE_OSX_SYSROOT}")
    endif()
endif()
message(STATUS "") # Add a blank line for readability

set(TEST_PROJECT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/test_boost_project")
set(TEST_PROJECT_BINARY_DIR "${TEST_BOOST_WORK_DIR}/verification_build")

# Clean up previous test build artifacts
if(EXISTS "${TEST_PROJECT_BINARY_DIR}")
    file(REMOVE_RECURSE "${TEST_PROJECT_BINARY_DIR}")
endif()
file(MAKE_DIRECTORY "${TEST_PROJECT_BINARY_DIR}")

# The root of our SDK is the parent directory of the Boost installation.
# By setting this as the prefix path, find_package can naturally discover
# both Boost and its dependencies (like ICU) in their respective subdirectories.
get_filename_component(SDK_ROOT "${TEST_BOOST_INSTALL_PREFIX}" DIRECTORY)

# Prepare CMake arguments for the test project
set(TEST_CMAKE_ARGS
    -S ${TEST_PROJECT_SOURCE_DIR}
    -B ${TEST_PROJECT_BINARY_DIR}
    -DBoost_ROOT=${TEST_BOOST_INSTALL_PREFIX}
    # Set CMAKE_PREFIX_PATH to the root of the SDK. This is a robust way to
    # ensure the test project finds both Boost and its dependencies.
    -DCMAKE_PREFIX_PATH=${SDK_ROOT}
    # Also set CMAKE_FIND_ROOT_PATH to ensure the toolchain respects this as the root for searches.
    -DCMAKE_FIND_ROOT_PATH=${SDK_ROOT}
    # Force find_package to search ONLY in the root path. This is the most robust way to prevent
    # it from finding other versions of Boost installed on the system (e.g., via Homebrew),
    # especially for nested find_package calls within Boost's own config scripts.
    -DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ONLY
    # For maximum isolation, explicitly clear the system prefix path for the test project.
    # This prevents find_package from finding system libraries (like a wrong version of ICU from Homebrew).
    -DCMAKE_SYSTEM_PREFIX_PATH=
    -DBoost_NO_SYSTEM_PATHS=ON # Ensure we use only the just-built Boost
    # Explicitly disable any compiler launchers like ccache for this verification step.
    # Launchers can interfere with the configuration checks of sub-projects.
    -DCMAKE_CXX_COMPILER_LAUNCHER=
    -DTEST_BOOST_VERSION=${TEST_BOOST_VERSION}
    -DTEST_COMPONENTS_STRING=${TEST_BOOST_LIBS_STRING} # Pass the safe string directly
)

# Forward necessary variables from the main build
if(TEST_CMAKE_GENERATOR)
    # The generator name can sometimes be passed with extra quotes from the parent
    # build process. We strip them here to ensure it's passed cleanly.
    string(REPLACE "\"" "" TEST_CMAKE_GENERATOR_CLEAN "${TEST_CMAKE_GENERATOR}")
    list(APPEND TEST_CMAKE_ARGS -G "${TEST_CMAKE_GENERATOR_CLEAN}")
endif()
if(CMAKE_BUILD_TYPE)
    list(APPEND TEST_CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
endif()
if(CMAKE_TOOLCHAIN_FILE)
    list(APPEND TEST_CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
endif()
if(APPLE)
    if(DEFINED CMAKE_OSX_ARCHITECTURES)
        list(APPEND TEST_CMAKE_ARGS -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES})
    endif()
    if(DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
        list(APPEND TEST_CMAKE_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET})
    endif()
    if(DEFINED CMAKE_OSX_SYSROOT)
        list(APPEND TEST_CMAKE_ARGS -DCMAKE_OSX_SYSROOT=${CMAKE_OSX_SYSROOT})
    endif()
endif()

if(DEFINED TEST_ICU_ROOT)
    list(APPEND TEST_CMAKE_ARGS -DICU_ROOT=${TEST_ICU_ROOT})
endif()

message(STATUS "")
message(STATUS "Arguments passed to test project configuration:")
foreach(ARG ${TEST_CMAKE_ARGS})
    message(STATUS "  ${ARG}")
endforeach()
message(STATUS "")

# Configure the test project
message(STATUS "Configuring verification project...")
execute_process(
    COMMAND ${CMAKE_COMMAND} ${TEST_CMAKE_ARGS}
    WORKING_DIRECTORY ${TEST_PROJECT_BINARY_DIR}
    RESULT_VARIABLE configure_result
    OUTPUT_VARIABLE configure_output
    ERROR_VARIABLE configure_output
)

if(NOT configure_result EQUAL 0)
    message(FATAL_ERROR "Failed to configure Boost verification project.\n"
                        "This indicates a problem with the Boost installation (e.g., missing headers or CMake config files).\n"
                        "Output:\n${configure_output}")
endif()

# Build the test project
message(STATUS "Building verification project...")

# Get number of cores for parallel builds using the robust ProcessorCount module.
include(ProcessorCount)
ProcessorCount(JOBS)
if(JOBS GREATER 0)
    set(PARALLEL_ARGS --parallel ${JOBS})
else()
    set(PARALLEL_ARGS "") # No parallel flag if detection fails.
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} --build . ${PARALLEL_ARGS}
    WORKING_DIRECTORY ${TEST_PROJECT_BINARY_DIR}
    RESULT_VARIABLE build_result
    OUTPUT_VARIABLE build_output
    ERROR_VARIABLE build_output
)

if(NOT build_result EQUAL 0)
    message(FATAL_ERROR "Failed to build Boost verification project.\n"
                        "This indicates a problem with the compiled Boost libraries (e.g., linking errors).\n"
                        "Output:\n${build_output}")
endif()

# Run the test executable
message(STATUS "Running verification executable...")
execute_process(
    COMMAND ./run_test
    WORKING_DIRECTORY ${TEST_PROJECT_BINARY_DIR}
    RESULT_VARIABLE run_result
    OUTPUT_VARIABLE run_output
    ERROR_VARIABLE run_output
)

if(NOT run_result EQUAL 0)
    message(FATAL_ERROR "Boost verification executable failed to run.\n"
                        "This may indicate a runtime issue or a problem with a dependency like ICU for boost::locale.\n"
                        "Output:\n${run_output}")
endif()

message(STATUS "--- Boost installation verification successful ---")
message(STATUS "Test executable output:\n${run_output}")