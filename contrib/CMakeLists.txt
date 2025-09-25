
add_subdirectory(db)
add_subdirectory(ethereum)

if(USE_BITCOIN_SECP256K1_FOR_ECDSA)
  option(SECP256K1_BUILD_BENCHMARK "Build benchmarks." OFF)
  option(SECP256K1_BUILD_TESTS "Build tests." OFF)
  option(SECP256K1_BUILD_EXHAUSTIVE_TESTS "Build exhaustive tests." OFF)
  option(SECP256K1_BUILD_CTIME_TESTS "Build constant-time tests." OFF)
  option(SECP256K1_BUILD_EXAMPLES "Build examples." OFF)
  set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

  if(STATIC)
    set(SECP256K1_DISABLE_SHARED ON CACHE BOOL "Disable shared library for secp256k1")
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries by default" FORCE) 
  endif()
  add_subdirectory(bitcoin-secp256k1)
  set_property(TARGET secp256k1 PROPERTY FOLDER "contrib")
  set_property(TARGET secp256k1_precomputed PROPERTY FOLDER "contrib")
endif()


if(CMAKE_SYSTEM_NAME STREQUAL "iOS" OR CMAKE_SYSTEM_NAME STREQUAL "Android")
  message("excluded upnp support for IOS build")
  return()
endif()

set_property(TARGET mdbx PROPERTY FOLDER "contrib")
set_property(TARGET lmdb PROPERTY FOLDER "contrib")


set_property(TARGET mdbx_chk mdbx_copy mdbx_dump mdbx_load mdbx_stat PROPERTY FOLDER "unused")
