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

#add_custom_target(gen_config_header
#        DEPENDS "${CMAKE_BINARY_DIR}/src/config/currency_config.h"
#)

file(WRITE "${CMAKE_BINARY_DIR}/src/config/currency_config_dummy.cpp" "")

add_library(currency_config OBJECT
        "${CMAKE_BINARY_DIR}/src/config/currency_config.h"
        "${CMAKE_BINARY_DIR}/src/config/currency_config_dummy.cpp"
)
add_dependencies(currency_config config)

set(GENERATE_PREMINE_WALLET OFF CACHE BOOL "Generate premine wallet")
set(PREMINE_WALLET_PASSWORD "" CACHE STRING "Premine wallet password")

if (GENERATE_PREMINE_WALLET AND GENERATE_FRESH_GENESIS)
    message(FATAL_ERROR "Genesis can not be generated together with premine wallet")
endif()

if (GENERATE_PREMINE_WALLET)
    unset(GENERATE_PREMINE_WALLET CACHE)
    message(WARNING "Generating premine wallet")

    if (NOT DEFINED PREMINE_WALLET_PASSWORD OR PREMINE_WALLET_PASSWORD STREQUAL "")
        message(FATAL_ERROR "set PREMINE_WALLET_PASSWORD or GENESIS_PREMINE_ADDRESS to generate genesis block")
    endif()

    # Make wallet directory
    add_custom_target(
            premine_wallet
            "${CMAKE_COMMAND}" -E make_directory "${CMAKE_SOURCE_DIR}/premine_wallet"
            COMMENT "Creating premine wallet directory"
    )

    # Generate wallet
    add_custom_command(TARGET premine_wallet POST_BUILD
            COMMAND echo ${PREMINE_WALLET_PASSWORD} | $<TARGET_FILE:simplewallet> --generate-new-wallet ${CMAKE_SOURCE_DIR}/premine_wallet/premine_wallet
            COMMENT "Generating premine wallet in ${CMAKE_SOURCE_DIR}/premine_wallet"
    )

    add_dependencies(premine_wallet simplewallet)
endif()
