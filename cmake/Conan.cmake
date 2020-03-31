macro(run_conan)
  # Download automatically, you can also just copy the conan.cmake file
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(
      STATUS
        "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD
         "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
         "${CMAKE_BINARY_DIR}/conan.cmake" STATUS conan_download_status)
    list(GET conan_download_status 0 conan_download_status_code)
    if(NOT conan_download_status_code EQUAL 0)
      message(WARNING "Unable to download conan.cmake. Using local fallback")
      file(COPY ${PROJECT_SOURCE_DIR}/conan.cmake
           DESTINATION ${CMAKE_BINARY_DIR})
    endif()
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)
  option(CONAN_LOCAL_SERVER "Add local conan server to remote list" ENABLED)

  if(${CONAN_LOCAL_SERVER})
    conan_add_remote(NAME local_server INDEX 0 URL http://localhost:9300)
  endif()
  conan_add_remote(NAME bincrafters URL
                   https://api.bintray.com/conan/bincrafters/public-conan)

  conan_cmake_run(
    CONANFILE
    conanfile.py
    OPTIONS
    ${CONAN_EXTRA_OPTIONS}
    BASIC_SETUP
    CMAKE_TARGETS # individual targets to link to
    BUILD
    missing)
endmacro()
