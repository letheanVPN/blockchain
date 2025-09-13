# This script handles downloading and building a specific version of Boost using CMake.
# It is intended to be included from the main CMakeLists.txt.

include(ExternalProject)
include(arch)

# --- Boost CMake Build Arguments ---
message(STATUS "[BoostCmake.cmake] Configuring Boost build. CMAKE_OSX_ARCHITECTURES: ${CMAKE_OSX_ARCHITECTURES}")

# For modern Boost versions (approx. 1.82+), the CMake build system uses a
# different set of variables to control the build.
set(BOOST_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    -DBUILD_TESTING=OFF
    # Use the standard BUILD_SHARED_LIBS to control static/shared builds.
    -DBUILD_SHARED_LIBS=OFF
    -DCMAKE_POLICY_DEFAULT_CMP0077=NEW # Required by Boost's CMake for modern behavior
)

# Pass the list of required libraries via the BUILD_LIBS variable, as a
# comma-separated string (not semicolon-separated).
string(REPLACE ";" "," BOOST_LIBS_STRING "${BOOST_LIBS_TO_BUILD}")
list(APPEND BOOST_CMAKE_ARGS "-DBUILD_LIBS=${BOOST_LIBS_STRING}")

set(BOOST_EXTRA_C_FLAGS "")
set(BOOST_EXTRA_CXX_FLAGS "")
set(BOOST_EXTRA_LINKER_FLAGS "")

# If ICU is required, add the necessary flags for Boost's CMake build.
if(ICU_ROOT)
    list(APPEND BOOST_CMAKE_ARGS "-DICU_ROOT=${ICU_ROOT}")
    # Explicitly add ICU include and lib paths to ensure the correct version is used.
    set(BOOST_EXTRA_C_FLAGS "${BOOST_EXTRA_C_FLAGS} -I${ICU_ROOT}/include")
    set(BOOST_EXTRA_CXX_FLAGS "${BOOST_EXTRA_CXX_FLAGS} -I${ICU_ROOT}/include")
    set(BOOST_EXTRA_LINKER_FLAGS "${BOOST_EXTRA_LINKER_FLAGS} -L${ICU_ROOT}/lib")

endif()

# If OpenSSL was found and built by our scripts, pass its location to Boost.
# This is crucial for Boost.Asio's SSL support. Boost's FindOpenSSL module
# respects the OPENSSL_ROOT_DIR variable.
if(TARGET OpenSSL::SSL)
    list(APPEND BOOST_CMAKE_ARGS "-DOPENSSL_ROOT_DIR=${OPENSSL_INSTALL_PREFIX}")
endif()

# Append architecture-specific flags from arch.cmake
#if(ARCH_C_FLAGS)
#    set(BOOST_EXTRA_C_FLAGS "${BOOST_EXTRA_C_FLAGS} ${ARCH_C_FLAGS}")
#endif()
#if(ARCH_CXX_FLAGS)
#    set(BOOST_EXTRA_CXX_FLAGS "${BOOST_EXTRA_CXX_FLAGS} ${ARCH_CXX_FLAGS}")
#endif()
#if(ARCH_LINKER_FLAGS)
#    set(BOOST_EXTRA_LINKER_FLAGS "${BOOST_EXTRA_LINKER_FLAGS} ${ARCH_LINKER_FLAGS}")
#endif()

# Explicitly forward the compilers to ensure the external project uses the same ones.
# This improves robustness, especially in complex or non-standard environments.
list(APPEND BOOST_CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER})
list(APPEND BOOST_CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER})

# Forward the C++ standard to ensure the dependency is built with the same
# standard as the main project. This prevents compilation and linking errors.
list(APPEND BOOST_CMAKE_ARGS -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD})
list(APPEND BOOST_CMAKE_ARGS -DCMAKE_CXX_STANDARD_REQUIRED=${CMAKE_CXX_STANDARD_REQUIRED})

# Pass build type for single-configuration generators (e.g., Makefiles)
if(CMAKE_BUILD_TYPE)
    list(APPEND BOOST_CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
endif()

# Combine warning flags and extra flags and pass them to the Boost build.
set(BOOST_WARNING_FLAGS "-w") # -w for GCC/Clang
if(MSVC)
  set(BOOST_WARNING_FLAGS "/W0")
endif()

string(STRIP "${BOOST_WARNING_FLAGS} ${BOOST_EXTRA_C_FLAGS}" BOOST_C_FLAGS_INIT)
if(BOOST_C_FLAGS_INIT)
    list(APPEND BOOST_CMAKE_ARGS "-DCMAKE_C_FLAGS_INIT=${BOOST_C_FLAGS_INIT}")
endif()

string(STRIP "${BOOST_WARNING_FLAGS} ${BOOST_EXTRA_CXX_FLAGS}" BOOST_CXX_FLAGS_INIT)
if(BOOST_CXX_FLAGS_INIT)
    # The argument must be quoted to ensure that the entire string of flags (which contains spaces)
    # is treated as a single argument. Without quotes, it gets split, and the flags are lost.
    list(APPEND BOOST_CMAKE_ARGS "-DCMAKE_CXX_FLAGS_INIT=${BOOST_CXX_FLAGS_INIT}")
endif()

# Pass linker flags to the Boost build. This is important on Apple platforms to
# ensure the linker targets the correct architecture, especially for dependencies.
if(BOOST_EXTRA_LINKER_FLAGS)
    string(STRIP "${BOOST_EXTRA_LINKER_FLAGS}" BOOST_LINKER_FLAGS_INIT)
    if(BOOST_LINKER_FLAGS_INIT)
        list(APPEND BOOST_CMAKE_ARGS "-DCMAKE_EXE_LINKER_FLAGS_INIT=${BOOST_LINKER_FLAGS_INIT}")
        list(APPEND BOOST_CMAKE_ARGS "-DCMAKE_SHARED_LINKER_FLAGS_INIT=${BOOST_LINKER_FLAGS_INIT}")
        list(APPEND BOOST_CMAKE_ARGS "-DCMAKE_MODULE_LINKER_FLAGS_INIT=${BOOST_LINKER_FLAGS_INIT}")
    endif()
endif()

# Forward macOS-specific settings for correct architecture and SDK.
# This is crucial for cross-compiling or building on Apple Silicon.
if(APPLE)
    if(DEFINED CMAKE_OSX_ARCHITECTURES)
        list(APPEND BOOST_CMAKE_ARGS -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES})
    endif()
    if(DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
        list(APPEND BOOST_CMAKE_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET})
    endif()
    if(DEFINED CMAKE_OSX_SYSROOT)
        list(APPEND BOOST_CMAKE_ARGS -DCMAKE_OSX_SYSROOT=${CMAKE_OSX_SYSROOT})
    endif()
endif()

# For static linking on Windows, ensure static runtime is used.
if(MSVC)
    list(APPEND BOOST_CMAKE_ARGS -DBOOST_USE_STATIC_RUNTIME=ON)
    # Prevent auto-linking by MSVC for the main project
    add_compile_definitions(BOOST_ALL_NO_LIB)
endif()

# If a compiler launcher like ccache is used, it can sometimes interfere with
# the configuration checks of external projects. We explicitly disable it for
# the Boost build to ensure a clean installation.
if(CMAKE_C_COMPILER_LAUNCHER OR CMAKE_CXX_COMPILER_LAUNCHER)
    list(APPEND BOOST_CMAKE_ARGS -DCMAKE_C_COMPILER_LAUNCHER= -DCMAKE_CXX_COMPILER_LAUNCHER=)
endif()

# Forward toolchain file for cross-compilation
if(CMAKE_TOOLCHAIN_FILE)
    list(APPEND BOOST_CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
endif()

# --- Prepare Verification Command Arguments ---
# We build the argument list for the verification script here to correctly handle
# optional variables. The test project expects a pipe-separated string of
# components, so we convert the CMake list here.
string(REPLACE ";" "|" BOOST_LIBS_TO_BUILD_STRING "${BOOST_LIBS_TO_BUILD}")

# We build the argument list for the verification script here to correctly handle
# optional variables. TEST_COMMAND does not support generator expressions, so we
# must construct the command manually.
set(VERIFY_BOOST_ARGS
    -DTEST_BOOST_INSTALL_PREFIX=<INSTALL_DIR>
    -DTEST_BOOST_LIBS_STRING=${BOOST_LIBS_TO_BUILD_STRING}
    -DTEST_BOOST_VERSION=${BOOST_VERSION}
    -DTEST_BOOST_WORK_DIR=${BOOST_WORK_DIR}
)

# Forward the ICU root path separately. This is more robust than constructing
# a complex, semicolon-separated path with an ExternalProject placeholder.
if(ICU_ROOT)
    list(APPEND VERIFY_BOOST_ARGS "-DTEST_ICU_ROOT=${ICU_ROOT}")
endif()

# Forward the build configuration to the verification script. This is crucial
# to ensure the test project is configured with the same settings as the main build.
if(CMAKE_GENERATOR)
    # Pass the generator as a -D variable. The -G flag is not for script mode (-P).
    # The entire -D... argument must be quoted for list(APPEND) to treat it as a
    # single element, correctly handling generators with spaces like "Unix Makefiles".
    list(APPEND VERIFY_BOOST_ARGS "-DTEST_CMAKE_GENERATOR=${CMAKE_GENERATOR}")
endif()
if(CMAKE_BUILD_TYPE)
    list(APPEND VERIFY_BOOST_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
endif()
if(CMAKE_TOOLCHAIN_FILE AND EXISTS "${CMAKE_TOOLCHAIN_FILE}")
    list(APPEND VERIFY_BOOST_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE})
endif()
if(APPLE)
    if(DEFINED CMAKE_OSX_ARCHITECTURES)
        list(APPEND VERIFY_BOOST_ARGS -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES})
    endif()
    if(DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
        list(APPEND VERIFY_BOOST_ARGS -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET})
    endif()
    if(DEFINED CMAKE_OSX_SYSROOT AND EXISTS "${CMAKE_OSX_SYSROOT}")
        list(APPEND VERIFY_BOOST_ARGS -DCMAKE_OSX_SYSROOT=${CMAKE_OSX_SYSROOT})
    endif()
endif()
list(APPEND VERIFY_BOOST_ARGS -P ${CMAKE_CURRENT_LIST_DIR}/VerifyBoost.cmake)

# --- Determine Processor Count for Parallel Build ---
include(ProcessorCount)
ProcessorCount(BOOST_JOBS)
if(BOOST_JOBS EQUAL 0)
    set(BOOST_JOBS 1) # Fallback to 1 core if detection fails.
endif()

# --- External Project Definition ---
ExternalProject_Add(
    boost_external
    PREFIX ${BOOST_WORK_DIR}
    DOWNLOAD_DIR ${SDK_CACHE_DIR}
    URL ${BOOST_URL}
    URL_HASH SHA256=${BOOST_SHA256}
    INSTALL_DIR ${BOOST_INSTALL_PREFIX}
    DEPENDS ${BOOST_EXTRA_DEPS}
    EXCLUDE_FROM_ALL 1 # Exclude from the default 'all' target to improve build system stability.
    # Configure, build, and install steps using CMake
    CMAKE_ARGS ${BOOST_CMAKE_ARGS}
    # Use generator expressions to handle multi-config generators

    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG> --parallel ${BOOST_JOBS}
    INSTALL_COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config $<CONFIG>

    LOG_CONFIGURE 0
    LOG_BUILD 0
    LOG_INSTALL 1

    # --- Verification Step ---
    # After installation, run a small test project to verify that the new Boost
    # installation is complete and usable. This helps catch issues with the build,
    # installation, or dependencies like ICU.
    TEST_AFTER_INSTALL 1
    TEST_COMMAND ${CMAKE_COMMAND} ${VERIFY_BOOST_ARGS}
)
