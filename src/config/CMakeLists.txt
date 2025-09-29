# This file is responsible for generating currency_config.h
# and providing it to other targets.
add_library(config INTERFACE)

include(${CMAKE_CURRENT_SOURCE_DIR}/default.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/check-config.cmake)

# This generates the header file from the template.
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/currency_config.h.in"
    "${CMAKE_BINARY_DIR}/src/config/currency_config.h"
)

# This tells any target linking against 'config' where to find headers.
target_include_directories(config INTERFACE
    # For targets within this build tree, add the directory containing the *generated* header.
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
    # Also add the main 'src' directory for other headers.
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)



file(WRITE "${CMAKE_BINARY_DIR}/src/config/currency_config_dummy.cpp" "")
add_library(currency_config OBJECT
        "${CMAKE_BINARY_DIR}/src/config/currency_config.h"
        "${CMAKE_BINARY_DIR}/src/config/currency_config_dummy.cpp"
)
add_dependencies(currency_config config)
