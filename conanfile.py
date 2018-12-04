from conans import ConanFile, CMake

class diplomacyConan(ConanFile):
    name = "diplomacy"
    version = "0.1.0"
    author = "Tim Quelch"
    requires = ("fmt/5.2.1@bincrafters/stable",
                "catch2/2.4.1@bincrafters/stable")
    generators = ("cmake_paths")

    def _cmake_configure(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._cmake_configure()
        cmake.build()
