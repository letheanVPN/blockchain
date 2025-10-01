import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeDeps, CMakeToolchain, CMake


class BlockchainConan(ConanFile):
    name = "blockchain"
    version = "6.0.1"
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "static": [True, False],
        "testnet": [True, False]
    }
    default_options = {
        "static": False,
        "testnet": False
    }

    requires = [
        "zlib/1.3.1",
        "boost/1.85.0",
        "openssl/3.2.0",
        "miniupnpc/2.2.5",
        "jwt-cpp/0.7.1"
    ]

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.variables["STATIC"] = self.options.static
        tc.variables["TESTNET"] = self.options.testnet
        # tc.preprocessor_definitions["TESTNET"] = None
        # tc.variables["BUILD_VERSION"] = self.options.build_version
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()