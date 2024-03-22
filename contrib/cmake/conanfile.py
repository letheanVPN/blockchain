# This file is managed by Conan, contents will be overwritten.
# To keep your changes, remove these comment lines, but the plugin won't be able to modify your requirements
import os
from io import StringIO
from conan import ConanFile
from conan.tools.files import load, copy
from conan.tools.cmake import CMake, cmake_layout, CMakeToolchain

class ConanApplication(ConanFile):
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        # The root of the project is one level above
        #self.folders.root = os.path.dirname(os.path.dirname('.'))
        # The source of the project (the root CMakeLists.txt) is the source folder
        #self.folders.source = "."
        #self.folders.build = "build"
        cmake_layout(self)

    def requirements(self):
        requirements = self.conan_data.get('requirements', [])
        #self.requires("qt/5.15.13", options={"shared":True, "qtwebengine":True, "gui": True, "qtwebchannel": True, "qtlocation": True, "qtdeclarative": True})
        for requirement in requirements:
            self.requires(requirement)