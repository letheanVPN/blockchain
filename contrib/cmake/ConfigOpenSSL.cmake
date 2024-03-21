if (APPLE AND NOT IOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")
    if (NOT OPENSSL_ROOT_DIR)
        EXECUTE_PROCESS(COMMAND brew --prefix openssl
                OUTPUT_VARIABLE OPENSSL_ROOT_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE)
        message(STATUS "Using OpenSSL found at ${OPENSSL_ROOT_DIR}")
    endif()
endif()

find_package(OpenSSL REQUIRED)
message(STATUS "Using OpenSSL include dir at ${OPENSSL_INCLUDE_DIR}")
include_directories(${OPENSSL_INCLUDE_DIR})
if(STATIC AND NOT IOS)
    if(UNIX)
        set(OPENSSL_LIBRARIES "${OPENSSL_LIBRARIES};${CMAKE_DL_LIBS};${CMAKE_THREAD_LIBS_INIT}")
    endif()
endif()

if (WIN32)
    list(APPEND OPENSSL_LIBRARIES ws2_32 crypt32)
endif()
