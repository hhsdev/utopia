# option to cmake debug messages
option(DEBUG_CMAKE "Enable cmake debug messages" ON)


if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(
    STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()

# Using ccache speeds up subsequent compilations
find_program(CCACHE ccache)
if(CCACHE)
  message("using ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
else()
	message("Unable to find ccache. Using normal compiler")
endif()


option(ENABLE_IPO "Enable Interprocedural Optimization" OFF)
if (ENABLE_IPO)
	include(CheckIPOSupported)
	check_ipo_supported(RESULT result OUTPUT output)
	if (result)
		set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
	else()
		message(SEND_ERROR "IPO is not supported: ${output}")
	endif()
endif()

