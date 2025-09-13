cmake_minimum_required(VERSION 3.26.3)

PROJECT(Zano)
set(VERSION "1.0")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(INSERT CMAKE_MODULE_PATH 0
        "${CMAKE_SOURCE_DIR}/cmake")

include(Policy)

# The arch module centralizes architecture detection and flag setting.
# It should be included early, especially on Apple platforms.
include(arch)

# --- SDK Build Target ---
# This custom target serves as an umbrella for all dependency builds.
# The individual dependency scripts (e.g., OpenSSL.cmake, Boost.cmake)
# will add their external project targets as dependencies to this target.
add_custom_target(build_sdk COMMENT "Building all bundled SDK dependencies (e.g., OpenSSL, Boost)...")


# On Apple platforms, define deployment target and other settings.
if(APPLE)
  # Set deployment target based on build type
  if(STATIC)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 15.0)
  else()
    set(CMAKE_OSX_DEPLOYMENT_TARGET 14.0)
  endif()

  # Define SDK folder name and expose variables to Makefile
  if(CMAKE_OSX_ARCHITECTURES)
    string(REPLACE ";" "-" SDK_ARCHS "${CMAKE_OSX_ARCHITECTURES}")
  else()
    # Fallback to current architecture if not specified
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm|aarch64")
      set(SDK_ARCHS "arm64")
    else()
      set(SDK_ARCHS "x86_64")
    endif()
  endif()

  string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMPILER_ID_LOWER)
  string(REGEX REPLACE "\\..*" "" DEPLOYMENT_TARGET_MAJOR "${CMAKE_OSX_DEPLOYMENT_TARGET}")
  set(ZANO_SDK_SUBDIR "${COMPILER_ID_LOWER}-${DEPLOYMENT_TARGET_MAJOR}-${SDK_ARCHS}")
  set(ZANO_SDK_DIR "sdk/${ZANO_SDK_SUBDIR}" CACHE STRING "Zano SDK directory")

  # Create a file for the Makefile to include
  set(MAKEFILE_VARS_FILE "${CMAKE_BINARY_DIR}/macos_build_vars.mk")
  file(WRITE ${MAKEFILE_VARS_FILE} "CMAKE_OSX_DEPLOYMENT_TARGET:=${CMAKE_OSX_DEPLOYMENT_TARGET}\n")
  file(APPEND ${MAKEFILE_VARS_FILE} "ZANO_SDK_DIR:=${ZANO_SDK_DIR}\n")
  message(STATUS "Generated Makefile variables in ${MAKEFILE_VARS_FILE}")

  # On Apple platforms, we need to explicitly set the SDK path (sysroot) to
  # ensure that the correct headers and libraries are found, especially for
  # dependencies like ICU.
  if(NOT CMAKE_OSX_SYSROOT)
      execute_process(
          COMMAND xcrun --sdk macosx --show-sdk-path
          OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
          OUTPUT_STRIP_TRAILING_WHITESPACE
      )
      message(STATUS "macOS SDK path not set, detected: ${CMAKE_OSX_SYSROOT}")
  endif()

  # For cross-compiling or special architectures on Apple, the link step
  # in try_compile can fail. Compiling to a static library avoids the link
  # step for symbol existence checks, which is a more robust way to check
  # for features like libm support in subprojects.
  set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "iOS" OR CMAKE_SYSTEM_NAME STREQUAL "Android")
  add_definitions(-DMOBILE_WALLET_BUILD)
  if(CMAKE_SYSTEM_NAME STREQUAL "iOS" )   
    add_definitions(-DIOS_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fembed-bitcode -Wno-enum-constexpr-conversion")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fembed-bitcode -Wno-enum-constexpr-conversion")			
  endif()
  if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    add_definitions(-DANDROID_BUILD)
    message("Android sdk prefix: ${CMAKE_CXX_ANDROID_TOOLCHAIN_PREFIX}")    
    message("Android CMAKE_CXX_COMPILER prefix: ${CMAKE_CXX_COMPILER}")    
    message("Android ANDROID_LD: ${ANDROID_LD}")
  endif()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# build types
if (UNIX AND NOT APPLE)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo")
  if (NOT CMAKE_BUILD_TYPE) # single configurations, defaults to Release
    set(CMAKE_BUILD_TYPE "Release")
  endif()
elseif (WIN32)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
  if (NOT CMAKE_BUILD_TYPE OR NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Release")) # single configurations, defaults to Release
    set(CMAKE_BUILD_TYPE "Release")
  endif()
endif()
message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}, and built type: ${CMAKE_BUILD_TYPE}")

enable_testing()

set(USE_PCH FALSE CACHE BOOL "Use shared precompiled headers")
set(DISABLE_TOR FALSE CACHE BOOL "Disable TOR library(and related tor-connect submodule)")
set(TESTNET FALSE CACHE BOOL "Compile for testnet")
if (NOT TESTNET)
  option (USE_CCACHE "Use ccache if a usable instance is found" ON)
  if (USE_CCACHE)
  #  include(FindCcache) # Has to be included after the project() macro, to be able to read the CXX variable.
  else()
    message(STATUS "ccache deselected")
  endif()
endif()
set(BUILD_GUI FALSE CACHE BOOL "Build qt-daemon")
set(USE_BITCOIN_SECP256K1_FOR_ECDSA FALSE CACHE BOOL "Use bitcoin-secp256k1 library for validating ECDSA(instead of OpenSSL)")
if(NOT USE_BITCOIN_SECP256K1_FOR_ECDSA)
  add_compile_definitions(USE_OPEN_SSL_FOR_ECDSA)
endif()

# --- Version Target Definition ---
# This target generates the version.h file. It's defined early so other parts
# of the build system can add dependencies to it.
set(COMMIT_ID_IN_VERSION ON CACHE BOOL "Include commit ID in version")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/version")
if (NOT COMMIT_ID_IN_VERSION)
  set(VERSION "${VERSION}-unknown")
  configure_file("src/version.h.in" "version/version.h")
  add_custom_target(version ALL)
elseif(DEFINED COMMIT)
  string(REPLACE "." "\\." VERSION_RE "${VERSION}")
  if(NOT REFS MATCHES "(\\(|, )tag: v${VERSION_RE}(\\)|, )")
    set(VERSION "${VERSION}-g${COMMIT}")
  endif()
  configure_file("src/version.h.in" "version/version.h")
  add_custom_target(version ALL)
else()
  find_package(Git QUIET)
  if(Git_FOUND OR GIT_FOUND)
    message(STATUS "Found Git: ${GIT_EXECUTABLE}")
    add_custom_target(version ALL "${CMAKE_COMMAND}" "-D" "VERSION=${VERSION}" "-D" "GIT=${GIT_EXECUTABLE}" "-D" "TO=${CMAKE_BINARY_DIR}/version/version.h" "-P" "src/version.cmake" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
  else()
    message(STATUS "WARNING: Git was not found!")
    set(VERSION "${VERSION}-unknown")
    configure_file("src/version.h.in" "version/version.h")
    add_custom_target(version ALL)
  endif()
endif()

# The version target should depend on the entire SDK being built.
add_dependencies(version build_sdk)

include_directories(src contrib/eos_portable_archive contrib contrib/epee/include contrib/jwt-cpp/include "${CMAKE_BINARY_DIR}/version" "${CMAKE_BINARY_DIR}/contrib/zlib")

if(TESTNET)
  message("!!!!!! NOTICE: Project is building for TESTNET !!!!!!")  
  add_compile_definitions(TESTNET)
endif()

if(CAKEWALLET)
  message("NOTICE: Building libraries for CAKEWALLET")  
  add_compile_definitions(CAKEWALLET DISABLE_PFR_SERIALIZATION_SELFCHECK)
endif()

if(DISABLE_TOR)
  message("NOTICE: Building with disabled TOR support!")  
  add_compile_definitions(DISABLE_TOR)
endif()


set(STATIC ${MSVC} CACHE BOOL "Link libraries statically")
if (UNIX AND NOT APPLE)
  # Note that at the time of this writing the -Wstrict-prototypes flag added below will make this fail
  find_package(Threads REQUIRED)
endif()

# TODO(unassigned): expand on types and versions, and then refactor.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set(CLANG TRUE)
endif()


if(MSVC)
  add_compile_definitions(
      _CRT_SECURE_NO_WARNINGS
      _WIN32_WINNT=0x0600
      WIN32_LEAN_AND_MEAN
      GTEST_HAS_TR1_TUPLE=0
  )
  add_compile_options(/EHa /bigobj /Zm1000 /Z7 /MP2 /W3 /GS- /wd4996 /wd4503 /wd4345 /wd4091 /FIinline_c.h)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10485760 /DEBUG dbghelp.lib crypt32.lib")
  if(STATIC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
  else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
  endif()
  include_directories(SYSTEM src/platform/msc)
  configure_file(utils/Directory.Build.props.in ${CMAKE_BINARY_DIR}/Directory.Build.props)
else()
  set(WARNINGS "-Wall -Wextra -Wpointer-arith -Wvla -Wwrite-strings -Wno-error=extra -Wno-error=sign-compare -Wno-error=strict-aliasing -Wno-error=type-limits -Wno-unused-parameter -Wno-error=unused-variable -Wno-aggregate-return -Wno-comment -Wno-unknown-pragmas -Wno-pragmas")
#  if(NOT APPLE)
#    set(WARNINGS "${WARNINGS} -Werror")
#  endif()
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(WARNINGS "${WARNINGS} -Wno-implicit-function-declaration -Wno-shift-count-overflow -Wno-error=mismatched-tags -Wno-error=null-conversion -Wno-overloaded-shift-op-parentheses -Wno-error=shift-count-overflow -Wno-error=tautological-constant-out-of-range-compare -Wno-error=unused-private-field -Wno-error=unneeded-internal-declaration -Wno-deprecated-copy -Wno-deprecated-declarations")
  else()
    set(WARNINGS "${WARNINGS} -Wno-error=write-strings")
  endif()

  # Since gcc 4.9 the LTO format is non-standard (slim), so we need the gcc-specific ar and ranlib binaries
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9.0) AND NOT (CMAKE_SYSTEM_NAME STREQUAL "Android"))
    set(CMAKE_AR "gcc-ar")
    set(CMAKE_RANLIB "gcc-ranlib")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT APPLE AND NOT (CMAKE_SYSTEM_NAME STREQUAL "Android"))
    set(CMAKE_AR "llvm-ar")
    set(CMAKE_RANLIB "llvm-ranlib")
  endif()


  if(MINGW)
    set(WARNINGS "${WARNINGS} -Wno-error=unused-value")
    set(MINGW_FLAG "-DWIN32_LEAN_AND_MEAN")
    include_directories(SYSTEM src/platform/mingw)
  else()
    set(MINGW_FLAG "")
  endif()
  if(APPLE)
    set(APPLE_FLAG "-DGTEST_USE_OWN_TR1_TUPLE=1")
  else()
    set(APPLE_FLAG "")
  endif()
  set(C_WARNINGS "-Waggregate-return -Wnested-externs -Wstrict-prototypes -Wno-comment")
  set(CXX_WARNINGS "-Wno-reorder -Wno-missing-field-initializers")
  try_compile(STATIC_ASSERT_RES "${CMAKE_CURRENT_BINARY_DIR}/static-assert" "${CMAKE_CURRENT_SOURCE_DIR}/utils/test-static-assert.c" COMPILE_DEFINITIONS "-std=c++14")
  if(STATIC_ASSERT_RES)
    set(STATIC_ASSERT_FLAG "")
  else()
    set(STATIC_ASSERT_FLAG "-Dstatic_assert=_Static_assert")
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -D_GNU_SOURCE ${MINGW_FLAG} ${STATIC_ASSERT_FLAG} ${WARNINGS} ${C_WARNINGS} ${ARCH_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -ftemplate-depth-1024 -D_GNU_SOURCE ${APPLE_FLAG} ${MINGW_FLAG} ${WARNINGS} ${CXX_WARNINGS} ${ARCH_CXX_FLAGS}")
  if (NOT APPLE AND NOT MSVC)
    if (CLANG)
      set(LLVM_USE_LINKER "gold")
    else()
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")
      link_libraries("$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:-lstdc++fs>") # GCC < 9 requires additional linking for std::filesystem. Remove after stop supporting GCC 8.x -- sowle
    endif()
  endif()
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND NOT (CMAKE_C_COMPILER_VERSION VERSION_LESS 4.8))
    set(DEBUG_FLAGS "-g3 -O0") #set(DEBUG_FLAGS "-g3 -Og")
  else()
    set(DEBUG_FLAGS "-g3 -O0")
  endif()
  set(RELEASE_FLAGS "-Ofast -DNDEBUG -Wno-unused-variable")

  if(NOT APPLE AND NOT (CMAKE_SYSTEM_NAME STREQUAL "Android"))
    set(RELEASE_FLAGS "${RELEASE_FLAGS} -flto=auto -g3")
  endif()
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND NOT MINGW)
    set(RELEASE_FLAGS "${RELEASE_FLAGS} -fno-fat-lto-objects")
  endif()
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS}")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS}")
  if(STATIC)
    if(APPLE)
      #message(SEND_ERROR "Static build is not supported on MacOS X")
    else()
      #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif()
  endif()
endif()


# always use local Boost installation rather than the system-wide (unless USE_SYSTEM_BOOST is defined for some reason, which is not recommended)
if(NOT DEFINED USE_SYSTEM_BOOST)
#  set(Boost_NO_SYSTEM_PATHS ON)
endif()

if(MSVC)
  set(Boost_USE_STATIC_LIBS ON)
endif()

if(STATIC)  
  set(Boost_USE_STATIC_LIBS ON)  
  set(Boost_USE_STATIC_RUNTIME ON)
endif()

message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

# --- SDK Dependencies ---
# This includes all external dependencies like OpenSSL and Boost.
include(sdk)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/contrib/ethereum/libethash)
# Link additional system libraries required by Boost components or the application
if(MINGW)
  list(APPEND Boost_LIBRARIES ws2_32 mswsock)
endif()

if(BUILD_GUI)
  find_package(Qt6 REQUIRED COMPONENTS Core5Compat Widgets WebEngineWidgets WebChannel PrintSupport)
  message(STATUS "Found QT Packages")
endif()

set(BUILD_TESTS FALSE CACHE BOOL "Build Zano tests")
set(DISABLE_MDBX FALSE CACHE BOOL "Exclude mdbx from build(need for a first time)") 
if(NOT DISABLE_MDBX)
   add_definitions(-DENABLED_ENGINE_MDBX)
endif()

add_subdirectory(contrib)
add_subdirectory(src)

if (BUILD_TESTS)
  add_subdirectory(tests)
endif()
