cmake_minimum_required(VERSION 3.1...3.15)

if(CMAKE_VERSION VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

project(
  utopia
  VERSION 1.0.0
  DESCRIPTION "utf8 string library in C++"
  LANGUAGES CXX)

include(cmake/StandardProjectSettings.cmake)

# interface to add properties to all targets in the project
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
target_include_directories(project_options INTERFACE ${PROJECT_SOURCE_DIR}/include)


# Fix for compile error messages being uncolored somehow.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(project_options INTERFACE -fdiagnostics-color=always)
endif()

# default project warnings
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# conan stuff
set(CONAN_EXTRA_OPTIONS "")
include(cmake/Conan.cmake)
run_conan()

# exports compile_commands.json to be used by linters
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# enabling tests
option(ENABLE_TESTS "Build tests" ON)
if(ENABLE_TESTS)
  message("Tests enabled. Building tests")
  add_subdirectory(tests)
else()
  message("Tests disabled")
endif()
add_subdirectory(src)
