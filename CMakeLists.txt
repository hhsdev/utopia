cmake_minimum_required(VERSION 3.1...3.15)

if(CMAKE_VERSION VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

project(
  utopia
  VERSION 1.0.0
  LANGUAGES CXX)

include(cmake/StandardProjectSettings.cmake)

# interface to add properties to all targets in the project
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# default project warnings
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# conan stuff
set(CONAN_REQUIRED_PACKAGES "")
set(CONAN_EXTRA_OPTIONS "")
include(cmake/Conan.cmake)
run_conan()

# enabling tests
if(ENABLE_TESTS)
  message("Tests enabled. Building tests")
  add_subdirectory(test)
else()
  message("Tests disabled")
endif()
add_subdirectory(src)
