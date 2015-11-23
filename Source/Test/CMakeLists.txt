project( ShaderParserTest )

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/Src
	${CMAKE_CURRENT_BINARY_DIR}
)

if( WIN32 )
	include_directories( 
		${CMAKE_CURRENT_SOURCE_DIR}/Src/Win32
	)
endif()

configure_file( ${CMAKE_TEMPLATES_DIR}/ShaderParserTestUtilities.h.in ${CMAKE_CURRENT_BINARY_DIR}/ShaderParserTestUtilities.h NEWLINE_STYLE LF )

set( PROJECT_DESC "ShaderParser Test" )
set( ${PROJECT_NAME}_VERSION_MAJOR	0 )
set( ${PROJECT_NAME}_VERSION_MINOR	1 )
set( ${PROJECT_NAME}_VERSION_BUILD	0 )

set( BinsDependencies
	${BinsDependencies}
	ShaderParser
)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../Plugin/Glsl/Src )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../Plugin/Hlsl/Src )

find_package( Boost COMPONENTS unit_test_framework )

if( Boost_UNIT_TEST_FRAMEWORK_FOUND )
	link_directories( ${Boost_LIBRARY_DIR} )
	#Boost unit test Libs
	set( BoostUnitTestLibraries "")
	FOREACH(Lib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
		if (BoostUnitTestLibraries)
			set(BoostUnitTestLibraries "${BoostUnitTestLibraries}|${Lib}")
		else()
			set(BoostUnitTestLibraries "${Lib}")
		endif()
	ENDFOREACH()

	if ( MSVC )
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj" )
	endif ()
	
	add_target(
		${PROJECT_NAME}
		bin_dos
		"${BinsDependencies}"
		"${BinsDependencies};${BoostUnitTestLibraries};${MinLibraries};"
		"ShaderParserTestPch.h"
		"ShaderParserTestPch.cpp"
		""
		""
		""
		"${CMAKE_CURRENT_BINARY_DIR}/ShaderParserTestUtilities.h"
	)

	if( ${BUILD_GLSL_PLUGIN} )
		add_dependencies( ${PROJECT_NAME} GlslParser )
		set( ADDITIONAL_FLAGS ${ADDITIONAL_FLAGS} TESTING_PLUGIN_GLSL )
	endif()

	if( ${BUILD_HLSL_PLUGIN} )
		add_dependencies( ${PROJECT_NAME} HlslParser )
		set( ADDITIONAL_FLAGS ${ADDITIONAL_FLAGS} TESTING_PLUGIN_HLSL )
	endif()

	set( ADDITIONAL_FLAGS ${ADDITIONAL_FLAGS} BOOST_TEST_DYN_LINK )

	if ( NOT "" STREQUAL "${ADDITIONAL_FLAGS}" )
	  set_target_properties( ${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "${ADDITIONAL_FLAGS}" )
	endif ()

	set_property( TARGET ${PROJECT_NAME} PROPERTY FOLDER "Test" )
	add_target_astyle( ${PROJECT_NAME} ".h;.hpp;.inl;.cpp" )
	
	# Adding debug test
	add_test( NAME ${PROJECT_NAME}_boost_test_debug
		CONFIGURATIONS Debug
		COMMAND "${PROJECT_NAME}d"
		WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug"
	)

	# Adding release test
	add_test( NAME ${PROJECT_NAME}_boost_test_release
		CONFIGURATIONS Release
		COMMAND "${PROJECT_NAME}"
		WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release"
	)

	copy_dll( ${PROJECT_NAME} "${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_DEBUG}" Debug )
	copy_dll( ${PROJECT_NAME} "${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE}" Release )
	copy_dll( ${PROJECT_NAME} "${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE}" RelWithDebInfo )
else()
	message( STATUS "Test can't be built (missing Boost)" )
endif()
