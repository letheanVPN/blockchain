

include_directories (${CMAKE_BINARY_DIR}/src ${CMAKE_BINARY_DIR}/src/currency_core)
include(${CMAKE_SOURCE_DIR}/cmake/config-vars.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/currency_configs/example.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/check-config-vars.cmake)
configure_file("currency_core/currency_config.h.in" "currency_core/currency_config.h")

# CAUTION - wallet generation will only work properly in UNIX line environment
set(GENERATE_FRESH_GENESIS OFF CACHE BOOL "Generate new genesis block")

set(GENESIS_PREMINE_ADDRESS "" CACHE STRING "Premine wallet address")
set(GENESIS_PROOF "" CACHE STRING "Genesis proof string")

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
            COMMAND echo ${PREMINE_WALLET_PASSWORD} | ${CMAKE_BINARY_DIR}/src/simplewallet --generate-new-wallet ${CMAKE_SOURCE_DIR}/premine_wallet/premine_wallet
            COMMENT "Generating premine wallet in ${CMAKE_SOURCE_DIR}/premine_wallet"
    )

    add_dependencies(premine_wallet simplewallet)
endif()

if (GENERATE_FRESH_GENESIS)
    unset(GENERATE_FRESH_GENESIS CACHE)
    add_executable(genesis_generator ${GENESIS_GENERATOR})
    target_link_libraries(genesis_generator currency_core crypto common zlibstatic ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)

    if (NOT DEFINED GENESIS_PREMINE_ADDRESS OR GENESIS_PREMINE_ADDRESS STREQUAL "")
        message(WARNING "GENESIS_PREMINE_ADDRESS not set, loading from ${CMAKE_SOURCE_DIR}/premine_wallet/premine_wallet.address")
        file(READ "${CMAKE_SOURCE_DIR}/premine_wallet/premine_wallet.address" GENESIS_PREMINE_ADDRESS)
        if (NOT DEFINED GENESIS_PREMINE_ADDRESS OR GENESIS_PREMINE_ADDRESS STREQUAL "")
            message(FATAL_ERROR "GENESIS_PREMINE_ADDRESS not set")
        endif()
    else()
        add_custom_command(TARGET genesis_generator POST_BUILD
                COMMAND ${CMAKE_BINARY_DIR}/src/genesis_generator --address ${GENESIS_PREMINE_ADDRESS} --proof ${GENESIS_PROOF} --output ${CMAKE_SOURCE_DIR}/src/currency_core/generated/
                COMMENT "Generating genesis data in ${CMAKE_SOURCE_DIR}/src/currency_core/"
        )
    endif()

endif()