cmake_minimum_required(VERSION 3.26.3)
project(BoostVerificationTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# By setting the minimum required version to match the main project, we ensure
# that all modern CMake policies are enabled by default. This creates a
# consistent environment and avoids subtle issues with find_package behavior.

# TEST_COMPONENTS_STRING is a pipe-separated string like "system|filesystem|..."
# passed from VerifyBoost.cmake. We convert it to a proper CMake list here.
string(REPLACE "|" ";" REQUIRED_COMPONENTS "${TEST_COMPONENTS_STRING}")

# Use CONFIG mode to ensure we use the BoostConfig.cmake provided by the Boost
# installation, bypassing the deprecated FindBoost.cmake module.
# Adding the EXACT version makes the request more specific and robust.
find_package(Boost ${TEST_BOOST_VERSION} EXACT CONFIG REQUIRED COMPONENTS ${REQUIRED_COMPONENTS})

# Find ICU libraries
find_package(ICU REQUIRED COMPONENTS data i18n uc)

add_executable(run_test main.cpp)

# Link against all the found Boost libraries
# Using the modern imported targets (e.g., Boost::system) is the preferred
# way to link against Boost components, as it automatically handles all
# necessary include directories and dependencies.
foreach(COMPONENT ${REQUIRED_COMPONENTS})
    target_link_libraries(run_test PRIVATE Boost::${COMPONENT})
endforeach()

# Also link against the headers target if it exists
# This is good practice for header-only parts of Boost.
if(TARGET Boost::headers)
    target_link_libraries(run_test PRIVATE Boost::headers)
endif()

# Link against ICU libraries in the correct order: i18n -> uc -> data
target_link_libraries(run_test PRIVATE ICU::i18n ICU::uc ICU::data)

# Add preprocessor definitions for optional components
if("locale" IN_LIST REQUIRED_COMPONENTS)
    target_compile_definitions(run_test PRIVATE TEST_LOCALE)
endif()

if("log" IN_LIST REQUIRED_COMPONENTS)
    target_compile_definitions(run_test PRIVATE TEST_LOG)
endif()
