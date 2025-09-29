add_executable(genesis_generator EXCLUDE_FROM_ALL generate_test_genesis.cpp)

target_link_libraries(genesis_generator
    PRIVATE
        config
        currency_core
        crypto
        common
        ZLIB::ZLIB
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES}
        OpenSSL::SSL
        OpenSSL::Crypto
)

set_property(TARGET genesis_generator PROPERTY FOLDER "prog")

if (GENERATE_FRESH_GENESIS)
    if (NOT DEFINED GENESIS_PREMINE_ADDRESS OR GENESIS_PREMINE_ADDRESS STREQUAL "")
        set(address_file "${CMAKE_SOURCE_DIR}/premine_wallet/premine_wallet.address")
        message(STATUS "GENESIS_PREMINE_ADDRESS not set, attempting to load from ${address_file}")
        if(EXISTS "${address_file}")
            file(READ "${address_file}" GENESIS_PREMINE_ADDRESS)
            string(STRIP "${GENESIS_PREMINE_ADDRESS}" GENESIS_PREMINE_ADDRESS)
        endif()
    endif()

    if (NOT DEFINED GENESIS_PREMINE_ADDRESS OR GENESIS_PREMINE_ADDRESS STREQUAL "")
        message(FATAL_ERROR "GENESIS_PREMINE_ADDRESS is not set and could not be read from file. Please set it via -DGENESIS_PREMINE_ADDRESS=<address>")
    else()
         add_custom_command(TARGET genesis_generator POST_BUILD
            COMMAND $<TARGET_FILE:genesis_generator> --address ${GENESIS_PREMINE_ADDRESS} --proof "${GENESIS_PROOF}" --output "${CMAKE_SOURCE_DIR}/src/genesis/"
            COMMENT "Generating genesis data..."
            VERBATIM
        )
    endif()
endif()
