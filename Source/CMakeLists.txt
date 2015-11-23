cmake_minimum_required( VERSION 2.8.10 )
#--------------------------------------------------------------------------------------------------
#	Initial configurations
#--------------------------------------------------------------------------------------------------
# Set project name, used in folders and in workspace creation
set( MAIN_PROJECT_NAME "ShaderParser" )

# Set project version numbers
set( VERSION_MAJOR	0		)
set( VERSION_MINOR	1		)
set( VERSION_BUILD	0		)
set( VERSION_YEAR	2015	)

# Used to look for external modules
set( CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/CMake
	${CMAKE_SOURCE_DIR}/CMake/Modules
)
set( CMAKE_TEMPLATES_DIR ${CMAKE_SOURCE_DIR}/Templates )
# Experimental Precompiled headers support for GCC
include( PCHSupport )

set( CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Set only Debug and Release configuration types" FORCE )

# Enable CTest
enable_testing()
    
# Declare the project
project( ${MAIN_PROJECT_NAME} )

include( Setup )
include( Project )
include( CompilerVersion )
include( UnitTest )
include( CompilationFlags )
include( AStyleUtils )
include( ExternalDependencies )

option( BUILD_STATIC "Build Static" FALSE )

# Organize projects into folders
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

#--------------------------------------------------------------------------------------------------
#	Looking for needed libraries
#--------------------------------------------------------------------------------------------------
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_STATIC_RUNTIME OFF )
set( Boost_USE_MULTITHREADED ON )

find_package( Boost 1.49 REQUIRED date_time locale filesystem system )

#--------------------------------------------------------------------------------------------------
#	Adding include dirs to include search path
#--------------------------------------------------------------------------------------------------
include_directories( Interface/Src )
include_directories( ${CMAKE_CURRENT_BINARY_DIR}/Interface/Src )

if( Boost_FOUND )
	include_directories( ${Boost_INCLUDE_DIRS} )
	link_directories( ${Boost_LIBRARY_DIRS} )

	#Boost Libs
	set( BoostLibraries "")
	FOREACH(Lib ${Boost_LIBRARIES})
		if (BoostLibraries)
			set(BoostLibraries "${BoostLibraries}|${Lib}")
		else()
			set(BoostLibraries "${Lib}")
		endif()
	ENDFOREACH()

	if( MSVC )
		# We remove the existing /Zm flag to replace it by /Zm300
		string( REGEX REPLACE ".*(/Zm[0-9]+).*" "\\1" ZmFlag ${CMAKE_CXX_FLAGS} )
		if( (NOT "${ZmFlag}" STREQUAL "") AND (NOT "${CMAKE_CXX_FLAGS}" STREQUAL "${ZmFlag}") )
			string( REPLACE ${ZmFlag} "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} )
		endif()
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zm300" )
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa" )
	endif()

	msg_debug( "CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")
	msg_debug( "CMAKE_C_FLAGS    : ${CMAKE_C_FLAGS}" )
	msg_debug( "CMAKE_CXX_FLAGS  : ${CMAKE_CXX_FLAGS}" )

	SET( MinLibraries
		${BoostLibraries}
	)

	SET( BinsDependencies "" )

	set( SHADER_PARSER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

	add_subdirectory( Interface )
	add_subdirectory( Plugin )

	PluginInit()

	PluginBuild()

	add_subdirectory( Test )

	SET( msg "Database following plugins will be built" )
	PluginSummary( ${msg} )
	MESSAGE( STATUS ${msg} )
	
	if ( ( "${PROJECTS_PACKAGE_WIX}" STREQUAL "ON" ) OR ( "${PROJECTS_PACKAGE_DEB}" STREQUAL "ON" ) OR ( "${PROJECTS_PACKAGE_RPM}" STREQUAL "ON" ) )
		get_filename_component( PARENT_DIR ${CMAKE_SOURCE_DIR} PATH )
		file( MAKE_DIRECTORY "${PROJECTS_SETUP_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}" )
		set( CPACK_PACKAGE_NAME "${MAIN_PROJECT_NAME}" )
		set( CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_BUILD}" )
		set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "${MAIN_PROJECT_NAME}" )
		set( CPACK_PACKAGE_DESCRIPTION "Allows ${MAIN_PROJECT_NAME} developments" )
		set( CPACK_PACKAGE_RELEASE 1 )
		set( CPACK_PACKAGE_CONTACT "dragonjoker59@hotmail.com" )
		set( CPACK_PACKAGE_VENDOR "DragonJoker" )
		set( CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${PROJECTS_PLATFORM}" )
		set( CPACK_OUTPUT_FILE_PREFIX "${PROJECTS_SETUP_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}" )
		set( CPACK_RESOURCE_FILE_LICENSE "${PARENT_DIR}/LGPL.txt" )

		if ( "${PROJECTS_PACKAGE_WIX}" STREQUAL "ON" )
			set( CPACK_GENERATOR "WIX" )
			set( CPACK_PACKAGE_INSTALL_DIRECTORY "${MAIN_PROJECT_NAME}" )
			set( CPACK_WIX_UPGRADE_GUID "2CD0B303-63BD-43DB-ADF4-F24E11C9A977" )
			set( CPACK_WIX_PRODUCT_GUID "11BAF390-80DB-46C4-B33E-E8F7CEF0F893" )
			set( CPACK_WIX_PRODUCT_ICON "${PARENT_DIR}/install/${MAIN_PROJECT_NAME}.ico" )
			set( CPACK_WIX_UI_DIALOG "${PARENT_DIR}/install/dialog.bmp" )
			set( CPACK_WIX_UI_BANNER "${PARENT_DIR}/install/banner.bmp" )
			set( CPACK_WIX_PROGRAM_MENU_FOLDER "${MAIN_PROJECT_NAME}" )
			set( CPACK_WIX_CULTURES "fr-FR;en-EN" )
			include(CPack)
		elseif ( "${PROJECTS_PACKAGE_DEB}" STREQUAL "ON" )
			set( CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} )
			set( CPACK_DEB_COMPONENT_INSTALL ON )
			set( CPACK_GENERATOR "DEB" )
			set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Sylvain Doremus" )
			set( CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}libboost (>= 1.49.0)" )
			set( CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${CMAKE_SYSTEM_ARCHITECTURE}" )
			set( CPACK_DEBIAN_PACKAGE_SECTION "devel" )
			set( CPACK_DEBIAN_PACKAGE_PRIORITY "optional" )
			include(CPack)
		elseif ( "${PROJECTS_PACKAGE_RPM}" STREQUAL "ON" )
			set( ${PROJECT_PACKAGE_DIR} ${CMAKE_BINARY_DIR}/_CPack_Packages/Linux/RPM )
			set( CPACK_RPM_COMPONENT_INSTALL ON )
			set( CPACK_RPM_PACKAGE_SUMMARY "${MAIN_PROJECT_NAME}" )
			set( CPACK_RPM_PACKAGE_ARCHITECTURE "${CMAKE_SYSTEM_ARCHITECTURE}" )
			set( CPACK_RPM_PACKAGE_GROUP "Development/Tools/Other" )
			set( CPACK_RPM_PACKAGE_LICENSE "LGPL" )
			set( CPACK_RPM_SPEC_MORE_DEFINE "%define _rpmdir ${PROJECT_PACKAGE_DIR}" )
			set( CPACK_RPM_SPEC_MORE_DEFINE "%define _rpmfilename ${CPACK_PACKAGE_FILE_NAME}.rpm" )
			set( CPACK_RPM_SPEC_MORE_DEFINE "%define _unpackaged_files_terminate_build 0" )
			set( CPACK_RPM_SPEC_MORE_DEFINE "%define _topdir ${PROJECT_PACKAGE_DIR}" )
			include(CPack)
		endif()
	endif ()

	cpack_add_install_type( Minimal )
	cpack_add_install_type( Developer )
	cpack_add_install_type( Full )
	
	cpack_add_component_group( Core
		EXPANDED
		DISPLAY_NAME "Core libraries"
		DESCRIPTION "Base libraries needed to use ${MAIN_PROJECT_NAME}"
	)
	cpack_add_component_group( ShaderParserPlugins
		DISPLAY_NAME "Plugins"
		DESCRIPTION "Plugins to use with ${MAIN_PROJECT_NAME}"
	)
	cpack_add_component_group( Development
		DISPLAY_NAME "Development libraries and headers"
		DESCRIPTION "All the tools needed to develop a project using ${MAIN_PROJECT_NAME}"
	)
	cpack_add_component_group( Documentation
		DISPLAY_NAME "Documentation"
		DESCRIPTION "Projects documentations"
	)

	cpack_add_component( ShaderParser
		DISPLAY_NAME "${MAIN_PROJECT_NAME} interface"
		DESCRIPTION "Base ${MAIN_PROJECT_NAME} interface"
		REQUIRED
		GROUP Core
		INSTALL_TYPES Minimal Full
	)
	cpack_add_component( ShaderParser_dev
		DISPLAY_NAME "${MAIN_PROJECT_NAME} SDK"
		DESCRIPTION "Base ${MAIN_PROJECT_NAME} interface development libraries and includes"
		GROUP Development
		INSTALL_TYPES Developer Full
	)

	cpack_add_component( ShaderParserTest
		DISPLAY_NAME "${MAIN_PROJECT_NAME} test application"
		DESCRIPTION "Base ${MAIN_PROJECT_NAME} test application"
		REQUIRED
		GROUP Development
		INSTALL_TYPES Developer Full
	)
	
	PluginSetup()
else()
	SET( msg "ShaderParser projects can't be built because of missing libraries:" )
	if( NOT Boost_FOUND )
		SET( msg "${msg}\n\tBoost" )
	endif()
	MESSAGE( SEND_ERROR ${msg} )
endif()
