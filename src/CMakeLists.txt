add_library(utopia STATIC ${CMAKE_CURRENT_SOURCE_DIR}/utopia.cpp)

target_include_directories(utopia PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(utopia PRIVATE project_options project_warnings)

set_target_properties(utopia PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)


