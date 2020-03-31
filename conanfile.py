from conans import CMake, ConanFile


class UtopiaConan(ConanFile):
    name = "utopia"
    version = "1.0.0"
    license = "MIT"
    author = "hhsdev heinhtetsoe.dev@gmail.com"
    url = "http://www.github.com/hhsdev/utopia"
    description = "C++ utf-8 string library"
    topics = ("C++", "unicode", "utf-8", "string")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    exports_sources = "src/*", "include/utopia/*"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.h", dst="include/utopia", src="include/utopia")
        self.copy("*.lib", dst="lib", src="lib", keep_path=False)
        self.copy("*.dll", dst="bin", src="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", src="lib", keep_path=False)
        self.copy("*.so", dst="lib", src="lib", keep_path=False)
        self.copy("*.a", dst="lib", src="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["utopia"]
