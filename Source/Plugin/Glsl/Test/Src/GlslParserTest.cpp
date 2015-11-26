/************************************************************************//**
 * @file GlslParserTest.cpp
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

#include "GlslParserTestPch.h"

#include "GlslParserTest.h"
#include "GlslParserTestPluginLoader.h"
#include "GlslGrammarTest.h"

#include <boost/test/unit_test.hpp>

NAMESPACE_SHADER_PARSER::String g_path;

std::unique_ptr< NAMESPACE_GLSL_PARSER_TEST::CGlslGrammarTest > g_grammarTest;
std::unique_ptr< NAMESPACE_GLSL_PARSER_TEST::CGlslPluginLoader > g_pluginLoader;

void Startup( char * arg )
{
	g_path = arg;
	NAMESPACE_SHADER_PARSER::StringUtils::Replace( g_path, STR( '\\' ), NAMESPACE_SHADER_PARSER::PATH_SEP );
	NAMESPACE_SHADER_PARSER::StringUtils::Replace( g_path, STR( '/' ), NAMESPACE_SHADER_PARSER::PATH_SEP );
	g_path = g_path.substr( 0, g_path.rfind( NAMESPACE_SHADER_PARSER::PATH_SEP ) + 1 );
	srand( uint32_t( time( NULL ) ) );

	// Configure logger
#if defined( NDEBUG )
	NAMESPACE_SHADER_PARSER::CLogger::Initialise( NAMESPACE_SHADER_PARSER::ELogType_INFO );
#else
	NAMESPACE_SHADER_PARSER::CLogger::Initialise( NAMESPACE_SHADER_PARSER::ELogType_DEBUG );
#endif
	NAMESPACE_SHADER_PARSER::CLogger::SetFileName( g_path + STR( "GlslParserTest.log" ) );

	g_grammarTest = std::make_unique< NAMESPACE_GLSL_PARSER_TEST::CGlslGrammarTest >();
	g_pluginLoader = std::make_unique< NAMESPACE_GLSL_PARSER_TEST::CGlslPluginLoader >();
}

void Shutdown()
{
	g_pluginLoader.reset();
	g_grammarTest.reset();
	NAMESPACE_SHADER_PARSER::CLogger::Cleanup();
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

	NAMESPACE_GLSL_PARSER_TEST::Tests_Creation();

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
	boost::unit_test::unit_test_main( &NAMESPACE_GLSL_PARSER_TEST::boost_main_init_function, argc, argv );

	Shutdown();

	//!@remarks Exit the test application.
	return 0;
}

BEGIN_NAMESPACE_GLSL_PARSER_TEST
{
	bool boost_main_init_function()
	{
		//!@remarks execute the test suite.
		Tests_Creation();

		//!@remarks Exit the Master TS initialization.
		return true;
	}
}
END_NAMESPACE_GLSL_PARSER_TEST
#endif

BEGIN_NAMESPACE_GLSL_PARSER_TEST
{
	void Tests_Creation()
	{
		//!@remarks Clear the TS' List
		TS_List.clear();

		//!@remarks Create the TS' sequences
		TS_List.push_back( g_grammarTest->Init_Test_Suite() );

#if defined( TESTING_PLUGIN_GLSL )
#endif
#if defined( TESTING_PLUGIN_HLSL )
#endif

		//!@remarks Add the TS' sequences into the Master TS
		for ( auto suite : TS_List )
		{
			boost::unit_test::framework::master_test_suite().add( suite );
		}
	}

	String InitialiseSingletons()
	{
		StringStream modulePath;
		size_t index = g_path.substr( 0, g_path.size() - 1 ).rfind( PATH_SEP );

		if ( index != String::npos )
		{
			modulePath << g_path.substr( 0, index + 1 );
		}
		else
		{
			modulePath << STR( ".." ) << PATH_SEP;
		}

		modulePath << STR( "lib" ) << PATH_SEP << STR( "ShaderParser" ) << PATH_SEP;
		String result = modulePath.str();

		CPluginManager::Instance().SetApplicationPath( result );
		CPluginManager::Instance().SetPluginsPath( result );
		CPluginManager::Instance().SetTranslationsPath( result );

		return result;
	}

	static const String GLSL_PLUGIN = STR( "GlslParser" );

	void LoadPlugins( const String & path )
	{
		SPluginsConfig pluginsConfig;
#if !defined( STATIC_LIB )
		pluginsConfig.m_glsl = std::make_unique< CPluginConfig >( true, CPluginManager::Instance().GetPluginsPath() + path, GLSL_PLUGIN );
#else
		pluginsConfig.m_glsl = std::make_unique< CPluginConfig< GLSL::CShaderParserPluginGlsl > >( true );
#endif
		g_pluginLoader->Load( std::move( pluginsConfig ) );
	}

	void UnloadPlugins()
	{
		g_pluginLoader->Unload();
	}
}
END_NAMESPACE_GLSL_PARSER_TEST
