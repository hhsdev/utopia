add_executable(
  unit_test
  ${PROJECT_SOURCE_DIR}/tests/catch_main.cpp

  ${PROJECT_SOURCE_DIR}/src/simple_unicode_buffer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/simple_unicode_buffer.test.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/convert.test.cpp
  #${PROJECT_SOURCE_DIR}/src/bits.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/bits.test.cpp)

option(ENABLE_BENCHMARKING "Enables benchmarking functions in test files" OFF)
if(ENABLE_BENCHMARKING)
  target_compile_definitions(unit_test PRIVATE CATCH_CONFIG_ENABLE_BENCHMARKING)
endif()

target_link_libraries(unit_test PRIVATE project_options project_warnings)

target_link_libraries(unit_test PUBLIC CONAN_PKG::Catch2)

set_target_properties(unit_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                           ${PROJECT_SOURCE_DIR}/bin)
