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

add_library(lthn_api ApiServer.cpp)
add_library(lthn::api ALIAS lthn_api)

target_include_directories(lthn_api PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${oatpp_INCLUDE_DIRS}
  ${oatpp-swagger_INCLUDE_DIRS}
)

target_link_libraries(lthn_api PUBLIC
  oatpp::oatpp
  oatpp::oatpp-swagger
)

# Define path to swagger resources for the installed package.
# This assumes the executable is in 'bin' and resources are in 'share/lthn_api'.
target_compile_definitions(lthn_api PUBLIC -DOATPP_SWAGGER_RES_PATH="../share/lthn_api/res")

# Copy resources to build directory for development builds (e.g. running in CLion)
file(COPY ${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res DESTINATION ${CMAKE_BINARY_DIR}/share/lthn_api)
file(COPY ${CMAKE_SOURCE_DIR}/utils/sdk/spec/oas-3.0.0.json DESTINATION ${CMAKE_BINARY_DIR}/share/lthn_api)

# Install swagger resources to a conventional location for packaging.
install(DIRECTORY ${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res DESTINATION share/lthn_api)

# Install OpenAPI spec for SDK generation for packaging.
install(FILES ${CMAKE_SOURCE_DIR}/utils/sdk/spec/oas-3.0.0.json DESTINATION share/lthn_api)


#add_executable(lethean-api main.cpp)
#
#target_include_directories(lethean-api PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(lthn_api
    PRIVATE
        config
        lthn::api
        rpc
        stratum
        currency_core
        crypto
        common
        ethash
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        OpenSSL::SSL
        OpenSSL::Crypto
        ZLIB::ZLIB
)

#add_subdirectory(tests)
