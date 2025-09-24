# Copyright (c) 2014-2019 Zano Project
# Copyright (c) 2014 The Cryptonote developers
# Distributed under the MIT/X11 software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# Define CMake generator

ifneq ($(OS),Windows_NT)
system := $(shell uname)
ifneq (, $(findstring MINGW, $(system)))
  cmake_gen = -G 'MSYS Makefiles'
endif
endif
PROFILES := $(patsubst cmake/profiles/%,%,$(wildcard cmake/profiles/*))
SORTED_PROFILES := $(sort $(PROFILES))
CONAN_CACHE := $(CURDIR)/build/sdk
DEFAULT_CONAN_PROFILE := $(CONAN_CACHE)/cmake/profiles/default

cmake = cmake $(cmake_gen)

cmake_debug = $(cmake) -D CMAKE_BUILD_TYPE=Debug
cmake_release = $(cmake) -D CMAKE_BUILD_TYPE=Release

cmake_gui = -D BUILD_GUI=ON
cmake_static = -D STATIC=ON
cmake_tests = -D BUILD_TESTS=ON

# Helper macro
define CMAKE
  mkdir -p $1 && cd $1 && $2 ../../
endef

build = build
dir_debug = $(build)/debug
dir_release = $(build)/release

all: help

release: conan-profile-detect
	@echo "Building profile: release"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/release --build=missing -s build_type=Release
	cmake -S . -B build/release -DCMAKE_TOOLCHAIN_FILE=build/release/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
	cmake --build build/release --config=Release --parallel=2

debug: conan-profile-detect
	@echo "Building profile: debug"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/debug --build=missing -s build_type=Debug
	cmake -S . -B build/debug -DCMAKE_TOOLCHAIN_FILE=build/debug/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/debug --config=Debug --parallel=2

static: static-release
static-release: conan-profile-detect
	@echo "Building profile: release-static"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/release-static --build=missing
	cmake -S . -B build/release-static -DCMAKE_TOOLCHAIN_FILE=build/release-static/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -D STATIC=ON
	cmake --build build/release-static --config=Release --parallel=2

conan-profile-detect:
	@if [ ! -f "$(DEFAULT_CONAN_PROFILE)" ]; then \
		echo "Default conan profile not found. Detecting a new one..."; \
		CONAN_HOME=$(CONAN_CACHE) conan profile detect --name=default --force; \
	fi


# Rule for each profile
$(PROFILES): conan-profile-detect
	@echo "Building profile: $@"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/$@ --profile=cmake/profiles/$@ --build=missing
	cmake -S . -B build/$@ -DCMAKE_TOOLCHAIN_FILE=build/$@/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
	cmake --build build/$@ --config=Release --parallel=2

help:
	@echo "Available targets:"
	@printf "  %-22s %s\n" "all:" "Build all profiles"
	@printf "  %-22s %s\n" "clean:" "Clean all build directories"
	@printf "  %-22s %s\n" "release:" "Build release"
	@printf "  %-22s %s\n" "static:" "Build static release"
	@printf "  %-22s %s\n" "debug:" "Build debug"
	@$(foreach profile,$(SORTED_PROFILES),printf "  %-22s %s\n" "make $(profile):" "Build the $(profile) profile";)
	@printf "  %-22s %s\n" "help:" "Show this help message"

#
# Tests
#

test: test-release
test-release:
	@echo "Building profile: test-release"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/test-release --build=missing
	cmake -S . -B build/test-release -DCMAKE_TOOLCHAIN_FILE=build/test-release/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -D BUILD_TESTS=ON
	cmake --build build/test-release --config=Release --parallel=2
	$(MAKE) test

test-debug:
	@echo "Building profile: test-debug"
	CONAN_HOME=$(CONAN_CACHE) conan install . --output-folder=build/test-debug --build=missing
	cmake -S . -B build/test-debug -DCMAKE_TOOLCHAIN_FILE=build/test-debug/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -D BUILD_TESTS=ON
	cmake --build build/test-debug --config=Debug --parallel=2
	$(MAKE) test

clean:
	rm -rf build

tags:
	ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ src contrib tests/gtest

.PHONY: all release debug static static-release gui gui-release gui-static gui-release-static gui-debug test test-release test-debug clean tags conan-profile-detect $(PROFILES)
