# Copyright (c) Facebook, Inc. and its affiliates. All Rights Reserved
#

import os

from conans import ConanFile, CMake


class FBX2glTFConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "boost/1.84.0",
        "libiconv/1.17",
        "zlib/1.3.1",
        "libxml2/2.12.5",
        "fmt/5.3.0",
    )
    generators = "cmake_find_package", "cmake_paths"

    def configure(self):
        if (
            self.settings.compiler == "gcc"
            and self.settings.compiler.libcxx == "libstdc++"
        ):
            raise Exception(
                "Rerun 'conan install' with argument: '-s compiler.libcxx=libstdc++11'"
            )

    def build(self):
        cmake = CMake(self)
        cmake.definitions["FBXSDK_SDKS"] = os.getenv("FBXSDK_SDKS", "sdk")
        cmake.configure()
        cmake.build()
