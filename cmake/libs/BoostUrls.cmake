# This file contains the database of known Boost versions, their download URLs,
# SHA256 hashes, and build system information. It is included by Boost.cmake.

# --- Boost Version Database ---
# To add a new version, add its corresponding variables here.

# Version 1.80.0 (b2 build system) - From non-GitHub sources
set(BOOST_VERSION_1_80_0_BUILD_SYSTEM "b2")
set(BOOST_VERSION_1_80_0_SHA256 "9c2f4b99bc7ddb95a8babff8ba78a4108aa0951243ea919166a7e2e279825502")
set(BOOST_VERSION_1_80_0_URLS
    "https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1.80.0.tar.gz"
    "https://sourceforge.net/projects/boost/files/boost/1.80.0/boost_1.80.0.tar.gz/download"
)

# Version 1.81.0 (b2 build system)
set(BOOST_VERSION_1_81_0_BUILD_SYSTEM "b2")
set(BOOST_VERSION_1_81_0_SHA256 "9339a2d1e99415613a7e5436451a54b9eaf045091638425f2847343ed9a16416")
set(BOOST_VERSION_1_81_0_URLS
    "https://github.com/boostorg/boost/releases/download/boost-1.81.0/boost-1.81.0.tar.gz"
    "https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz")

# Version 1.82.0 (b2 build system)
set(BOOST_VERSION_1_82_0_BUILD_SYSTEM "b2")
set(BOOST_VERSION_1_82_0_SHA256 "b136218d6e3201a03dc74533c48112344071a5c48f8b04b3a44503f15a99ea29")
set(BOOST_VERSION_1_82_0_URLS
    "https://github.com/boostorg/boost/releases/download/boost-1.82.0/boost-1.82.0.tar.gz"
    "https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz"
)

# Version 1.83.0 (b2 build system)
set(BOOST_VERSION_1_83_0_BUILD_SYSTEM "b2")
set(BOOST_VERSION_1_83_0_SHA256 "495a64134b2233481a2734a95099800182c217df02501994e488388c2f1e34b8")
set(BOOST_VERSION_1_83_0_URLS
    "https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.gz"
    "https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.tar.gz"
)

# Version 1.84.0 (b2 build system)
set(BOOST_VERSION_1_84_0_BUILD_SYSTEM "b2")
set(BOOST_VERSION_1_84_0_SHA256 "4d27e9efed0f6f152dc28db6430b9d3dfb40c0345da7342eaa5a987dde57bd95")
set(BOOST_VERSION_1_84_0_URLS
    "https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.gz"
    "https://boostorg.jfrog.io/artifactory/main/release/1.84.0/source/boost_1_84_0.tar.gz"
)

# Version 1.85.0 (CMake build system)
set(BOOST_VERSION_1_85_0_BUILD_SYSTEM "cmake")
set(BOOST_VERSION_1_85_0_SHA256 "ab9c9c4797384b0949dd676cf86b4f99553f8c148d767485aaac412af25183e6")
set(BOOST_VERSION_1_85_0_URLS "https://github.com/boostorg/boost/releases/download/boost-1.85.0/boost-1.85.0-cmake.tar.gz")

# Version 1.86.0 (CMake build system) - NOTE: No more '-cmake' tarball from this version onwards
set(BOOST_VERSION_1_86_0_BUILD_SYSTEM "cmake")
set(BOOST_VERSION_1_86_0_SHA256 "c62ce6e64d34414864fef946363db91cea89c1b90360eabed0515f0eda74c75c")
set(BOOST_VERSION_1_86_0_URLS "https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.gz")

# Version 1.87.0 (CMake build system)
set(BOOST_VERSION_1_87_0_BUILD_SYSTEM "cmake")
set(BOOST_VERSION_1_87_0_SHA256 "78fbf579e3caf0f47517d3fb4d9301852c3154bfecdc5eeebd9b2b0292366f5b")
set(BOOST_VERSION_1_87_0_URLS
    "https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.tar.gz"
    "https://boostorg.jfrog.io/artifactory/main/release/1.87.0/source/boost_1_87_0-cmake.tar.gz"
    "https://sourceforge.net/projects/boost/files/boost/1.87.0/boost_1_87_0-cmake.tar.gz/download"
)

# Version 1.88.0 (CMake build system)
set(BOOST_VERSION_1_88_0_BUILD_SYSTEM "cmake")
set(BOOST_VERSION_1_88_0_SHA256 "59c4be52268a7985163c48c433575a6f3a38458903b231a9a69cf2ac1f8323f4")
set(BOOST_VERSION_1_88_0_URLS
    "https://github.com/boostorg/boost/releases/download/boost-1.88.0/boost-1.88.0-cmake.tar.gz"
    "https://boostorg.jfrog.io/artifactory/main/release/1.88.0/source/boost_1_88_0-cmake.tar.gz"
    "https://sourceforge.net/projects/boost/files/boost/1.88.0/boost_1_88_0-cmake.tar.gz/download"
)

# Version 1.89.0 (CMake build system)
set(BOOST_VERSION_1_89_0_BUILD_SYSTEM "cmake")
set(BOOST_VERSION_1_89_0_SHA256 "3385155a85d3ac357aa2794371754a3e60a13322d33454407166c88a2c885e3c")
set(BOOST_VERSION_1_89_0_URLS "https://github.com/boostorg/boost/releases/download/boost-1.89.0/boost-1.89.0-cmake.7z")

# --- ICU Dependency ---
set(ICU_VERSION "73.2")
set(ICU_URL "https://github.com/unicode-org/icu/releases/download/release-73-2/icu4c-73_2-src.tgz")
set(ICU_SHA256 "818a80712ed3caacd9b652305e01afc7fa167e6f2e94996da44b90c2ab604ce1")
set(ICU_CONFIGURE_PATH "source/configure") # Relative path from extracted source dir

# --- Boost Version Database (Pre-compiled Cache Hashes) ---
# These are the SHA256 hashes for the pre-compiled binary archives.
# The variable name format is BOOST_VERSION_<version>_CACHE_SHA256_<platform_id>
# NOTE: These are placeholders. You must generate the real hashes for your archives.
set(BOOST_VERSION_1_84_0_CACHE_SHA256_gcc_x64 "PLACEHOLDER_HASH_FOR_1_84_0_GCC_X64_ARCHIVE")
set(BOOST_VERSION_1_84_0_CACHE_SHA256_appleclang_arm64 "PLACEHOLDER_HASH_FOR_1_84_0_APPLECLANG_ARM64_ARCHIVE")
set(BOOST_VERSION_1_85_0_CACHE_SHA256_gcc_x64 "PLACEHOLDER_HASH_FOR_1_85_0_GCC_X64_ARCHIVE")
