add_executable(
  unit_test
  ${PROJECT_SOURCE_DIR}/tests/catch_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/simple_unicode_buffer.test.cpp)

target_link_libraries(unit_test PRIVATE project_options project_warnings)

target_link_libraries(unit_test PUBLIC CONAN_PKG::Catch2)

set_target_properties(unit_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                           ${PROJECT_SOURCE_DIR}/bin)
