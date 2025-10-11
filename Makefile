# Copyright (c) 2017-2025 Lethean https://lt.hn
# Copyright (c) 2014-2019 Zano Project
# Copyright (c) 2014 The Cryptonote developers
# Distributed under the MIT/X11 software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# ------------------------------------------------------------
# Detect the number of logical CPU cores – works on Linux,
# macOS, BSD, and Windows (both cmd.exe and PowerShell).
# ------------------------------------------------------------

# Default to “unknown” – will be overwritten below.
CPU_CORES := 1
TESTNET:= 0
STATIC:= 0
BUILD_TYPE ?=Release
BUILD_VERSION:=6.0.1
BUILD_FOLDER:=build/release
PRESET_BUILD:=conan-release
PRESET_CONFIGURE:=conan-release

UNAME_S := $(shell uname -s 2>/dev/null || echo Unknown)

ifeq ($(UNAME_S),Linux)
    # Linux: try nproc first, fall back to /proc
    CPU_CORES := $(shell nproc 2>/dev/null || \
                  grep -c ^processor /proc/cpuinfo 2>/dev/null || echo 1)
endif

ifeq ($(UNAME_S),Darwin)
    # macOS: sysctl reports the number of logical CPUs
    CPU_CORES := $(shell sysctl -n hw.logicalcpu 2>/dev/null || echo 1)
endif

ifeq ($(filter %BSD,$(UNAME_S)),%BSD)
    # *BSD: also sysctl, but the key differs on some variants
    CPU_CORES := $(shell sysctl -n hw.ncpu 2>/dev/null || echo 1)
endif

ifeq ($(OS),Windows_NT)

PRESET_CONFIGURE:=conan-default

    # Prefer the environment variable that Windows sets for us.
    # It works in both cmd.exe and PowerShell.
    CPU_CORES := $(NUMBER_OF_PROCESSORS)

    # If for some reason the env var is empty, fall back to PowerShell.
    ifeq ($(CPU_CORES),)
        CPU_CORES := $(shell powershell -NoProfile -Command ^ "[Environment]::ProcessorCount")
    endif
endif

# -----------------------------------------------------------------
# Safety net – ensure we always have a positive integer.
# -----------------------------------------------------------------
CPU_CORES := $(or $(CPU_CORES),1)
CPU_CORES := $(shell expr $(CPU_CORES) + 0 2>/dev/null || echo 1)
CONAN_CPU_COUNT=$(CPU_CORES)


PROFILES := $(patsubst cmake/profiles/%,%,$(wildcard cmake/profiles/*))
SORTED_PROFILES := $(sort $(PROFILES))
CONAN_CACHE := $(CURDIR)/build/sdk
CONAN_URL:=https://artifacts.host.uk.com/artifactory/api/conan/conan-build
CONAN_USER:=public
CONAN_PASSWORD:=Lethean1234
DEFAULT_CONAN_PROFILE := $(CONAN_CACHE)/profiles/default
CONAN_EXECUTABLE := $(CURDIR)/build/bin/conan
CC_DOCKER_FILE?=utils/docker/images/lthn-chain/Dockerfile

all: help

testnet:
	$(MAKE) configure TESTNET=1
	CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) build .

mainnet:
	$(MAKE) configure TESTNET=0
	CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) build .

release: docs build
	(cd $(BUILD_FOLDER) && cpack)
	@rm -rf $(CURDIR)/build/packages/_CPack_Packages

build: configure
	cmake --build --preset $(PRESET_BUILD) --parallel=$(CPU_CORES)

build-deps: conan-profile-detect
	@echo "Build Dependencies: $(BUILD_TYPE) testnet=$(TESTNET)"
	CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) install . --build=missing  -s build_type=$(BUILD_TYPE)

configure: build-deps
	@echo "Running Configure: $(BUILD_TYPE) testnet=$(TESTNET)"
	cmake --preset $(PRESET_CONFIGURE) -DSTATIC=$(STATIC) -DTESTNET=$(TESTNET) -DBUILD_VERSION=$(BUILD_VERSION)

docs: configure
	@echo "Building Documentation"
	cmake --build build/release --target=docs --config=Release --parallel=$(CPU_CORES)

# Rule for each profile
$(PROFILES): conan-profile-detect
	@echo "Building profile: $@"
	CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) install . -pr:h=cmake/profiles/$@ --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B $(BUILD_FOLDER) -DCMAKE_TOOLCHAIN_FILE=$(BUILD_FOLDER)/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DSTATIC=$(STATIC) -DTESTNET=$(TESTNET) -DBUILD_VERSION=$(BUILD_VERSION)
	cmake --build $(BUILD_FOLDER) --config=$(BUILD_TYPE) --parallel=$(CPU_CORES)
	(cd $(BUILD_FOLDER) && cpack)

help:
	@echo "Available targets:"
	@printf "  %-42s %s\n" "make clean" "Clean all build directories"
	@printf "  %-42s %s\n" "make get-conan" "Download and install conan locally"
	@printf "  %-42s %s\n" "make release" "Build release"
	@printf "  %-42s %s\n" "make static" "Build static release"
	@printf "  %-42s %s\n" "make debug" "Build debug"
	@printf "  %-42s %s\n" "make test" "Build & run tests"
	@printf "  %-42s %s\n" "make docs" "Builds offline documentation website"
	@printf "  %-42s %s\n" "make docs-dev" "Runs local doc server, for editing/adding docs"
	@printf "  %-42s %s\n" "make conan-profile-detect" "Creates host config"
	@printf "  %-42s %s\n" "make configure" "Runs a cmake configure within conan build flow"
	@$(foreach profile,$(SORTED_PROFILES),printf "  %-42s %s\n" "make $(profile)" "Build the $(profile) profile";)
	@printf "  %-42s %s\n" "make help" "Show this help message"

#
# Tests
#

test: test-release
test-release:
	@echo "Building profile: test-release"
	CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) install . --output-folder=build/test-release --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B build/test-release -DCMAKE_TOOLCHAIN_FILE=build/test-release/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -D BUILD_TESTS=ON
	cmake --build build/test-release --config=Release --parallel=$(CPU_CORES)
	$(MAKE) test

test-debug:
	@echo "Building profile: test-debug"
	CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) install . --output-folder=build/test-debug --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B build/test-debug -DCMAKE_TOOLCHAIN_FILE=build/test-debug/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -D BUILD_TESTS=ON
	cmake --build build/test-debug --config=Debug --parallel=$(CPU_CORES)
	$(MAKE) test

# allowing this target to error quietly saves cross brwoser file detection
conan-get:
	cmake -P cmake/ConanGet.cmake
	(CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) remote add conan_build $(CONAN_URL) && \
	CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) remote login conan_build $(CONAN_USER) -p $(CONAN_PASSWORD)) || true

conan-upload:
	CONAN_HOME=$(CONAN_CACHE) $(CONAN_EXECUTABLE) upload "*" -r=conan_build --confirm

conan-profile-detect: conan-get
	cmake -P cmake/ConanProfileSetup.cmake

docs-dev: configure
	@echo "Building Documentation"
	cmake --build build/release --target=serve_docs --config=Release

clean:
	@cmake -P cmake/CleanBuild.cmake

clean-build: clean
	rm -rf build

tags:
	ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ src contrib tests/gtest

.PHONY: all release upload-conan-cache docs docs-dev configure static static-release test test-release test-debug clean tags conan-profile-detect get-conan $(PROFILES)
