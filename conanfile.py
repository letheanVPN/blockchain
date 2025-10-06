import os

from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, CMake


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
        "testnet": False,
        "boost/*:without_test": True
    }

    tool_requires = "ccache/4.11"

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
        self.folders.generators = os.path.join("build", str(self.settings.build_type).lower(), "generators")
        self.folders.build = os.path.join("build", str(self.settings.build_type).lower())

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()