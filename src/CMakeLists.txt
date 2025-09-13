# This definition will be applied to all targets in this directory and subdirectories.
# It is the most reliable way to disable Boost auto-linking across the entire project.
if(USE_SYSTEM_DEPS AND WIN32)
    add_compile_definitions(BOOST_ALL_NO_LIB)
    # Brute-force add the OpenSSL include directory to all targets to fix propagation issues.
    get_target_property(OPENSSL_INCLUDE_DIR OpenSSL::SSL INTERFACE_INCLUDE_DIRECTORIES)
    if(OPENSSL_INCLUDE_DIR)
        include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})
    endif()
endif()

# if(POLICY CMP0043)
#   cmake_policy(SET CMP0043 OLD)
# endif()

# define USE_PCH to YES for using precomiled headers
# Windows: using custom-made shared PCH -- this is unusual case for MSVC... so mystery, such hack, many wow. See also: https://stackoverflow.com/questions/645747/sharing-precompiled-headers-between-projects-in-visual-studio/4170902#4170902
# Linux: using CMake-enabled shared PCH (which appeared in CMake 3.16)
function(INIT_SHARED_PCH)
  if(USE_PCH)
    message(STATUS "...... enabling precompiled headers, creating 'pch' target")
    # This target exists solely to generate the PCH file that other targets will reuse.
    add_library(pch INTERFACE)
    target_precompile_headers(pch INTERFACE "pch/stdafx.h")
    set(PCH_LIB_NAME pch PARENT_SCOPE)
  endif()
endfunction()

function(ENABLE_SHARED_PCH target)
  if(USE_PCH AND TARGET pch)
    message(STATUS "...... enabling precompiled headers for: ${target}")
    # Link against the 'pch' interface library. This automatically sets up
    # the correct compiler flags to use the precompiled header.
    target_link_libraries(${target} PRIVATE pch)
  endif()
endfunction()

#####  End of Precompiled Headers macros  ######

option(BUILD_CONNECTIVITY_TOOL "Build the connectivity_tool utility" OFF)

file(GLOB_RECURSE PCH pch/*)
file(GLOB_RECURSE COMMON common/*)
file(GLOB_RECURSE CRYPTO crypto/*)
file(GLOB_RECURSE CURRENCY_CORE currency_core/*)
file(GLOB_RECURSE CURRENCY_PROTOCOL currency_protocol/*)
file(GLOB_RECURSE DAEMON daemon/*)

file(GLOB_RECURSE P2P p2p/*)
file(GLOB_RECURSE RPC rpc/*)
file(GLOB_RECURSE STRATUM stratum/*)
file(GLOB_RECURSE SIMPLEWALLET simplewallet/*)
file(GLOB_RECURSE WALLET wallet/*)
file(GLOB_RECURSE MINER miner/*)

if(BUILD_GUI)
  if(MSVC)
    file(GLOB_RECURSE QTDAEMON gui/qt-daemon/*.cpp gui/qt-daemon/*.h gui/qt-daemon/app.rc)
  elseif(APPLE)
    file(GLOB_RECURSE QTDAEMON gui/qt-daemon/*.cpp gui/qt-daemon/*.h gui/qt-daemon/*.mm)
  else()
    file(GLOB_RECURSE QTDAEMON gui/qt-daemon/*.cpp gui/qt-daemon/*.h)
  endif()
  list(FILTER QTDAEMON EXCLUDE REGEX "node_modules")
endif()


source_group(pch FILES ${PCH})
source_group(common FILES ${COMMON})
source_group(crypto FILES ${CRYPTO})
source_group(currency_core FILES ${CURRENCY_CORE})
source_group(currency_protocol FILES ${CURRENCY_PROTOCOL})
source_group(daemon FILES ${DAEMON})
source_group(p2p FILES ${P2P})
source_group(rpc FILES ${RPC})
source_group(stratum FILES ${STRATUM})
source_group(simplewallet FILES ${SIMPLEWALLET})
source_group(wallet FILES ${WALLET})

if(BUILD_GUI)
  source_group(qtdaemon FILES ${QTDAEMON})
endif()


INIT_SHARED_PCH()

# Create a list of Boost imported targets from the component list in sdk.cmake
if(USE_SYSTEM_DEPS)
    set(ZANO_BOOST_TARGETS "")
    foreach(COMPONENT ${ZANO_BOOST_COMPONENTS})
        list(APPEND ZANO_BOOST_TARGETS "Boost::${COMPONENT}")
    endforeach()
endif()

add_library(common ${COMMON})
add_dependencies(common version ${PCH_LIB_NAME})

# --- Modern Boost Linking ---
if(USE_SYSTEM_DEPS)
    target_link_libraries(common PUBLIC ${ZANO_BOOST_TARGETS})
else()
    add_dependencies(common build_sdk)
    target_link_libraries(common PUBLIC Boost::headers)
endif()

ENABLE_SHARED_PCH(common)

if(NOT MSVC AND NOT APPLE AND NOT CLANG)  # TODO(unassigned): do we really need the clang equivalent?
   target_compile_options(common PRIVATE -fno-var-tracking-assignments)
endif()

# disable specific warning in order not to touch original code by D. J. Bernstein
if(MSVC)
  set_source_files_properties("crypto/chacha8_stream.c" PROPERTIES COMPILE_FLAGS "/wd4018")
else()
  set_source_files_properties("crypto/chacha8_stream.c" PROPERTIES COMPILE_FLAGS "-Wno-sign-compare -Wno-strict-prototypes")
endif()

if(WIN32)
  set(BCRYPT_LIB bcrypt)
endif()

add_library(crypto ${CRYPTO})
add_dependencies(crypto build_sdk)
if(USE_BITCOIN_SECP256K1_FOR_ECDSA)
  add_dependencies(crypto secp256k1)
  target_link_libraries(crypto PUBLIC secp256k1 ${BCRYPT_LIB})
else()
  target_link_libraries(crypto PUBLIC OpenSSL::SSL OpenSSL::Crypto ${BCRYPT_LIB})
endif()

add_library(currency_core ${CURRENCY_CORE})
add_dependencies(currency_core version ${PCH_LIB_NAME} build_sdk)
target_link_libraries(currency_core PUBLIC common crypto lmdb mdbx)
ENABLE_SHARED_PCH(currency_core)

add_library(wallet  ${WALLET})
add_dependencies(wallet version ${PCH_LIB_NAME} build_sdk)
if(CMAKE_SYSTEM_NAME STREQUAL "Android" )
  target_link_libraries(wallet PUBLIC currency_core crypto common zlibstatic ${CMAKE_THREAD_LIBS_INIT} android log)
else()
  target_link_libraries(wallet PUBLIC currency_core common)
  ENABLE_SHARED_PCH(wallet)
endif()

if(NOT DISABLE_TOR)
  target_link_libraries(wallet PUBLIC tor-connect)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
  install(TARGETS wallet currency_core crypto common DESTINATION lib)
  message("Generating install for iOS")
  return()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
  install(TARGETS wallet currency_core crypto common zlibstatic DESTINATION "${CMAKE_ANDROID_ARCH_ABI}/lib")
  message("Generating install for Android")

  file(GLOB WALLET_INCLUDES wallet/*.h)
  install(FILES ${WALLET_INCLUDES} DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
  return()
endif()

add_library(rpc ${RPC})
add_dependencies(rpc version ${PCH_LIB_NAME} build_sdk)
target_link_libraries(rpc PUBLIC common OpenSSL::SSL OpenSSL::Crypto)
ENABLE_SHARED_PCH(rpc)

add_library(stratum ${STRATUM})
add_dependencies(stratum version ${PCH_LIB_NAME} build_sdk)
target_link_libraries(stratum PUBLIC common)
ENABLE_SHARED_PCH(stratum)

# --- Executable Targets ---

add_executable(daemon ${DAEMON} ${P2P} ${CURRENCY_PROTOCOL})
add_dependencies(daemon version build_sdk)
if(USE_SYSTEM_DEPS)
    target_link_libraries(daemon PRIVATE rpc stratum currency_core crypto common libminiupnpc-static zlibstatic ethash ${CMAKE_THREAD_LIBS_INIT} ${ZANO_BOOST_TARGETS})
else()
    target_link_libraries(daemon PRIVATE rpc stratum currency_core crypto common libminiupnpc-static zlibstatic ethash ${CMAKE_THREAD_LIBS_INIT})
endif()
ENABLE_SHARED_PCH(daemon)

if(BUILD_CONNECTIVITY_TOOL)
  file(GLOB_RECURSE CONN_TOOL connectivity_tool/*)
  source_group(connectivity-tool FILES ${CONN_TOOL})
  add_executable(connectivity_tool ${CONN_TOOL})
  add_dependencies(connectivity_tool version build_sdk)
  if(USE_SYSTEM_DEPS)
      target_link_libraries(connectivity_tool PRIVATE currency_core crypto common zlibstatic ethash ${CMAKE_THREAD_LIBS_INIT} ${ZANO_BOOST_TARGETS})
  else()
      target_link_libraries(connectivity_tool PRIVATE currency_core crypto common zlibstatic ethash ${CMAKE_THREAD_LIBS_INIT})
  endif()
  ENABLE_SHARED_PCH(connectivity_tool)
  set_property(TARGET connectivity_tool PROPERTY FOLDER "prog")
endif()

add_executable(simplewallet ${SIMPLEWALLET})
add_dependencies(simplewallet version build_sdk)
if(USE_SYSTEM_DEPS)
    target_link_libraries(simplewallet PRIVATE wallet rpc currency_core crypto common zlibstatic ethash ${CMAKE_THREAD_LIBS_INIT} ${ZANO_BOOST_TARGETS})
else()
    target_link_libraries(simplewallet PRIVATE wallet rpc currency_core crypto common zlibstatic ethash ${CMAKE_THREAD_LIBS_INIT})
endif()
ENABLE_SHARED_PCH(simplewallet)

set_property(TARGET common PROPERTY FOLDER "libs")
set_property(TARGET crypto PROPERTY FOLDER "libs")
set_property(TARGET currency_core PROPERTY FOLDER "libs")
set_property(TARGET rpc PROPERTY FOLDER "libs")
set_property(TARGET stratum PROPERTY FOLDER "libs")
set_property(TARGET wallet PROPERTY FOLDER "libs")

set_property(TARGET daemon PROPERTY FOLDER "prog")
set_property(TARGET simplewallet PROPERTY FOLDER "prog")

set_target_properties(daemon PROPERTIES OUTPUT_NAME "zanod")
