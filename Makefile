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
TESTNET ?= 0
BUILD_TYPE ?=Release

# -----------------------------------------------------------------
# Unix‑like systems (Linux, macOS, *BSD, etc.)
# -----------------------------------------------------------------
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

# -----------------------------------------------------------------
# Windows (detected by the built‑in $(OS) variable set by GNU make)
# -----------------------------------------------------------------
ifeq ($(OS),Windows_NT)
    # Prefer the environment variable that Windows sets for us.
    # It works in both cmd.exe and PowerShell.
    CPU_CORES := $(NUMBER_OF_PROCESSORS)

    # If for some reason the env var is empty, fall back to PowerShell.
    ifeq ($(CPU_CORES),)
        CPU_CORES := $(shell powershell -NoProfile -Command ^ "[Environment]::ProcessorCount")
    endif
endif

#testnet-genesis-new:
#	$(eval command += $(cmake_release) $(testnet))
#	$(call CMAKE,$(dir_release),$(command) -DGENERATE_PREMINE_WALLET=1 -DPREMINE_WALLET_PASSWORD=12345678) && cmake --build ./src --target premine_wallet || true
#	$(eval command += $(cmake_release) $(testnet))
#	$(call CMAKE,$(dir_release),$(command) -DGENERATE_FRESH_GENESIS=1) && cmake --build ./src --target genesis_generator
#	$(eval command += $(cmake_release) $(testnet))
#	$(call CMAKE,$(dir_release),$(command)) && $(MAKE)
#
#genesis-new:
#	$(eval command += $(cmake_release))
#	$(call CMAKE,$(dir_release),$(command) -DGENERATE_FRESH_GENESIS=1) && cmake --build ./src --target genesis_generator
#	$(eval command += $(cmake_release))
#	$(call CMAKE,$(dir_release),$(command)) && $(MAKE)

# -----------------------------------------------------------------
# Safety net – ensure we always have a positive integer.
# -----------------------------------------------------------------
CPU_CORES := $(or $(CPU_CORES),1)
CPU_CORES := $(shell expr $(CPU_CORES) + 0 2>/dev/null || echo 1)
CONAN_CPU_COUNT=$(CPU_CORES)


PROFILES := $(patsubst cmake/profiles/%,%,$(wildcard cmake/profiles/*))
SORTED_PROFILES := $(sort $(PROFILES))
CONAN_CACHE := $(CURDIR)/build/sdk
DEFAULT_CONAN_PROFILE := $(CONAN_CACHE)/profiles/default

all: help

release: conan-profile-detect
	@echo "Building profile: release"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/release --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B build/release -DCMAKE_TOOLCHAIN_FILE=build/release/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DTESTNET=$(TESTNET)
	cmake --build build/release --config=$(BUILD_TYPE) --parallel=$(CPU_CORES)

debug: conan-profile-detect
	@echo "Building profile: debug"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/debug --build=missing -s build_type=Debug
	cmake -S . -B build/debug -DCMAKE_TOOLCHAIN_FILE=build/debug/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DTESTNET=$(TESTNET)
	cmake --build build/debug --config=Debug --parallel=$(CPU_CORES)

static: static-release
static-release: conan-profile-detect
	@echo "Building profile: release-static"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/release-static --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B build/release-static -DCMAKE_TOOLCHAIN_FILE=build/release-static/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -D STATIC=ON -DTESTNET=$(TESTNET)
	cmake --build build/release-static --config=Release --parallel=$(CPU_CORES)

conan-profile-detect:
	@if [ ! -f "$(DEFAULT_CONAN_PROFILE)" ]; then \
		echo "Default conan profile not found. Detecting a new one..."; \
		CONAN_HOME=$(CONAN_CACHE) conan profile detect --name=default --force; \
	fi


# Rule for each profile
$(PROFILES): conan-profile-detect
	@echo "Building profile: $@"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/$@ -pr:b=$(DEFAULT_CONAN_PROFILE) -pr:h=cmake/profiles/$@ --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B build/$@ -DCMAKE_TOOLCHAIN_FILE=build/$@/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DTESTNET=$(TESTNET)
	cmake --build build/$@ --config=$(BUILD_TYPE) --parallel=$(CPU_CORES)

help:
	@echo "Available targets:"
	@printf "  %-42s %s\n" "make clean" "Clean all build directories"
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
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/test-release --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B build/test-release -DCMAKE_TOOLCHAIN_FILE=build/test-release/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -D BUILD_TESTS=ON
	cmake --build build/test-release --config=Release --parallel=$(CPU_CORES)
	$(MAKE) test

test-debug:
	@echo "Building profile: test-debug"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/test-debug --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B build/test-debug -DCMAKE_TOOLCHAIN_FILE=build/test-debug/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -D BUILD_TESTS=ON
	cmake --build build/test-debug --config=Debug --parallel=$(CPU_CORES)
	$(MAKE) test

configure:
	@echo "Running Config: release"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/release --build=missing -s build_type=$(BUILD_TYPE)
	cmake -S . -B build/release -DCMAKE_TOOLCHAIN_FILE=build/release/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

docs: configure
	@echo "Building Documentation"
	cmake --build build/release --target=docs --config=Release --parallel=$(CPU_CORES)

docs-dev: configure
	@echo "Building Documentation"
	cmake --build build/release --target=serve_docs --config=Release

docker-chain-node:
	@echo "Building docker image: lthn/chain"
	docker build utils/docker/images/lthn-chain  -t lthn/chain $(CURDIR)

clean:
	rm -rf build

tags:
	ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ src contrib tests/gtest

.PHONY: all release docker-chain-node debug docs docs-dev configure static static-release test test-release test-debug clean tags conan-profile-detect $(PROFILES)
