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

target_include_directories(lthn_api INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${oatpp_INCLUDE_DIRS})
include_directories(${oatpp-swagger_INCLUDE_DIRS})
add_executable(lethean-api main.cpp)

target_link_libraries(lethean-api PRIVATE lthn::api PUBLIC oatpp::oatpp oatpp::oatpp-swagger)

add_definitions(-DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res")
#add_subdirectory(tests)
