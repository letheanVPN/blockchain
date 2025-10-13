if(NOT PROJECT_NAME)
  project(lethean-api)
endif()

find_package(oatpp 1.3.0 REQUIRED)
if(oatpp_FOUND)
  message(STATUS "Found oatpp version: ${oatpp_VERSION_STRING}")
else()
  message(FATAL_ERROR "Could not find oatpp")
endif()

find_package(oatpp-swagger  1.3.0 REQUIRED)
if(oatpp-swagger_FOUND)
  message(STATUS "Found oatpp-swagger version: ${oatpp-swagger_VERSION_STRING}")
else()
  message(FATAL_ERROR "Could not find oatpp-swagger")
endif()

add_library(lthn_api INTERFACE)
add_library(lthn::api ALIAS lthn_api)

# Add the current directory for API headers and the main src directory for core headers
target_include_directories(lthn_api INTERFACE 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src
)

include_directories(${oatpp_INCLUDE_DIRS})
include_directories(${oatpp-swagger_INCLUDE_DIRS})

# Add P2P and currency_protocol sources directly to the executable, like the main daemon does
add_executable(lethean-api main.cpp ApiServer.cpp ${P2P} ${CURRENCY_PROTOCOL})

# Explicitly add the project's main src directory to the executable's include paths
target_include_directories(lethean-api PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link against the correct, existing library targets
target_link_libraries(lethean-api 
    PRIVATE
        lthn::api
        rpc
        stratum
        currency_core
        crypto
        common
        config
        ethash
        oatpp::oatpp 
        oatpp::oatpp-swagger
        ${Boost_LIBRARIES}
        OpenSSL::SSL
        OpenSSL::Crypto
        ZLIB::ZLIB
)

add_definitions(-DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res")
#add_subdirectory(tests)
