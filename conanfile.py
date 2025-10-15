import os

from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, CMake


class BlockchainConan(ConanFile):
    name = "blockchain"
    version = "6.0.1"
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "static": [True, False],
        "testnet": [True, False],
        "ci": [True, False]
    }
    default_options = {
        "static": False,
        "testnet": False,
        "ci": False,
        "boost/*:without_test": True
    }

    tool_requires = [
        "cmake/3.31.9"
    ]

    requires = [
        "zlib/1.3.1",
        "boost/1.85.0",
        "openssl/3.2.0",
        "miniupnpc/2.2.5",
        "jwt-cpp/0.7.1",
        "oatpp/1.3.0.latest",
        "oatpp-swagger/1.3.0.latest"
    ]

    def generate(self):
        tc = CMakeToolchain(self)

        os_val = str(self.settings.os).lower()
        # arch_val = str(self.settings.arch).lower()
        # compiler_val = str(self.settings.compiler).lower()
        # tc.presets_prefix = f"{os_val}"

        tc.user_presets_path = "ConanPresets.json"
        tc.variables["STATIC"] = self.options.static
        tc.variables["TESTNET"] = self.options.testnet
        # tc.preprocessor_definitions["TESTNET"] = None
        # tc.variables["BUILD_VERSION"] = self.options.build_version
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def layout(self):
        if self.settings.compiler == "msvc":
            # For multi-config, all configurations go into the same "build" folder.
            self.folders.build = "build/release"
            self.folders.generators = "build/release/generators"
        else:
            # For single-config, we create a subfolder for each build type.
            build_type_str = str(self.settings.build_type).lower()
            self.folders.build = os.path.join("build", build_type_str)
            self.folders.generators = os.path.join(self.folders.build, "generators")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
