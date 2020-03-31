cmake_minimum_required(VERSION 2.8.12)
project(PackageTest CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(sanity_check sanity_check.cpp)
target_link_libraries(sanity_check ${CONAN_LIBS})
