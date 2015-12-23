/************************************************************************//**
 * @file ShaderParserTest.cpp
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief Main application for boost tests with Suites.
 *
 * @details This is the implementation to include tests in Boost suites.
 *
 ***************************************************************************/

#include "ShaderParserTestPch.h"

#include "ShaderParserTest.h"
#include "ShaderParserStringUtilsTest.h"

#include <boost/test/unit_test.hpp>

ShaderParser::String g_path;

std::unique_ptr< ShaderParserTest::CShaderParserStringUtilsTest > g_databaseStringUtilsTest;

void Startup( char * arg )
{
	g_path = arg;
	ShaderParser::StringUtils::Replace( g_path, STR( '\\' ), ShaderParser::PATH_SEP );
	ShaderParser::StringUtils::Replace( g_path, STR( '/' ), ShaderParser::PATH_SEP );
	g_path = g_path.substr( 0, g_path.rfind( ShaderParser::PATH_SEP ) + 1 );
	srand( uint32_t( time( NULL ) ) );

	// Configure logger
#if defined( NDEBUG )
	ShaderParser::CLogger::Initialise( ShaderParser::ELogType_INFO );
#else
	ShaderParser::CLogger::Initialise( ShaderParser::ELogType_DEBUG );
#endif
	ShaderParser::CLogger::SetFileName( g_path + STR( "ShaderParserTest.log" ) );

	g_databaseStringUtilsTest = std::make_unique< ShaderParserTest::CShaderParserStringUtilsTest >();
}

void Shutdown()
{
	g_databaseStringUtilsTest.reset();
	ShaderParser::CLogger::Cleanup();
}

#if BOOST_STATIC_LIB
/** Main Entry Point in static mode.
@param  argc    Arguments number
@param  argv    Aruments' list
@return test_suite  Test Suite Pointer
*/
boost::unit_test::test_suite * init_unit_test_suite( int argc, char * argv[] )
{
	Startup( argv[0] );

	ShaderParserTest::Tests_Creation();

	Shutdown();
	//!@remarks Exit the test application.
	return 0;
}
#else
/** Main Entry Point in dynamic mode.
@param  argc    Arguments number
@param  argv    Arguments' list
@return int     Execution return code
*/
int main( int argc, char * argv[] )
{
	Startup( argv[0] );

	//!@remarks Master TS initialization.
	boost::unit_test::master_test_suite_t & masterTestSuite = boost::unit_test::framework::master_test_suite();
	boost::unit_test::init_unit_test_func();

	//!@remarks Master TS Execution.
	boost::unit_test::unit_test_main( &ShaderParserTest::boost_main_init_function, argc, argv );

	Shutdown();

	//!@remarks Exit the test application.
	return 0;
}

namespace ShaderParserTest
{
	bool boost_main_init_function()
	{
		//!@remarks execute the test suite.
		Tests_Creation();

		//!@remarks Exit the Master TS initialization.
		return true;
	}
}

#endif

namespace ShaderParserTest
{
	void Tests_Creation()
	{
		//!@remarks Clear the TS' List
		TS_List.clear();

		//!@remarks Create the TS' sequences
		TS_List.push_back( g_databaseStringUtilsTest->Init_Test_Suite() );

		//!@remarks Add the TS' sequences into the Master TS
		for ( auto suite : TS_List )
		{
			boost::unit_test::framework::master_test_suite().add( suite );
		}
	}

	ShaderParser::String InitialiseSingletons()
	{
		ShaderParser::StringStream modulePath;
		size_t index = g_path.substr( 0, g_path.size() - 1 ).rfind( ShaderParser::PATH_SEP );

		if ( index != ShaderParser::String::npos )
		{
			modulePath << g_path.substr( 0, index + 1 );
		}
		else
		{
			modulePath << STR( ".." ) << ShaderParser::PATH_SEP;
		}

		modulePath << STR( "lib" ) << ShaderParser::PATH_SEP << STR( "ShaderParser" ) << ShaderParser::PATH_SEP;
		ShaderParser::String result = modulePath.str();

		ShaderParser::CPluginManager::Instance().SetApplicationPath( result );
		ShaderParser::CPluginManager::Instance().SetPluginsPath( result );
		ShaderParser::CPluginManager::Instance().SetTranslationsPath( result );

		return result;
	}
}
