# This file is managed by Conan, contents will be overwritten.
# To keep your changes, remove these comment lines, but the plugin won't be able to modify your requirements
import os
from conan import ConanFile
from conan.tools.files import load, copy
from conan.tools.cmake import cmake_layout, CMakeToolchain

class ConanApplication(ConanFile):
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def layout(self):
        # The root of the project is one level above
        #self.folders.root = os.path.dirname(os.path.dirname('.'))
        # The source of the project (the root CMakeLists.txt) is the source folder
        #self.folders.source = "."
        #self.folders.build = "build"
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()

    def requirements(self):
        requirements = self.conan_data.get('requirements', [])
        for requirement in requirements:
            self.requires(requirement)