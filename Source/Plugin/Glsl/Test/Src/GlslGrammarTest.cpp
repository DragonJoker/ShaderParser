/************************************************************************//**
 * @file ShaderParserStringUtilsTest.cpp
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief Class testing StringUtils functions
*
***************************************************************************/

#include "GlslParserTestPch.h"

#include "GlslGrammarTest.h"
#include "GlslParserTestPluginLoader.h"

#include <ShaderParserLogger.h>

using namespace ShaderParser;
using namespace GlslParser;

namespace GlslParserTest
{
	static const String GLSL_PLUGIN = STR( "GlslParser" );

	CGlslGrammarTest::CGlslGrammarTest()
	{
	}

	CGlslGrammarTest::~CGlslGrammarTest()
	{
	}

	boost::unit_test::test_suite * CGlslGrammarTest::Init_Test_Suite()
	{
		//!@remarks Create the internal TS instance.
#if BOOST_VERSION < 105900
		m_testSuite = new boost::unit_test::test_suite( "CGlslGrammarTest" );
#else
		m_testSuite = new boost::unit_test::test_suite( "CGlslGrammarTest", __FILE__, __LINE__ );
#endif

		//!@remarks Add the TC to the internal TS.
		m_testSuite->add( BOOST_TEST_CASE( std::bind( &CGlslGrammarTest::TestCase_ParseVertexShader, this ) ) );
		m_testSuite->add( BOOST_TEST_CASE( std::bind( &CGlslGrammarTest::TestCase_ParseTessDomainShader, this ) ) );
		m_testSuite->add( BOOST_TEST_CASE( std::bind( &CGlslGrammarTest::TestCase_ParseTessHullShader, this ) ) );
		m_testSuite->add( BOOST_TEST_CASE( std::bind( &CGlslGrammarTest::TestCase_ParseGeometryShader, this ) ) );
		m_testSuite->add( BOOST_TEST_CASE( std::bind( &CGlslGrammarTest::TestCase_ParseFragmentShader, this ) ) );
		m_testSuite->add( BOOST_TEST_CASE( std::bind( &CGlslGrammarTest::TestCase_ParseComputeShader, this ) ) );

		//!@remarks Return the TS instance.
		return m_testSuite;
	}

	void CGlslGrammarTest::TestCase_ParseVertexShader()
	{
		InitialiseSingletons();
		LoadPlugins( "" );

		auto l_grammar = CFactoryManager::Instance().CreateInstance( GLSL_PARSER_TYPE );

		std::string l_shader =
		"void main(void)\n"
		"{\n"
		"	vec4 b;\n"
		"	vec4 a = gl_Vertex;\n"
		//"	a.x = a.x * 0.5;\n"
		//"	a.y = a.y * 0.5;\n"
		//"	gl_Position = gl_ModelViewProjectionMatrix * a;\n"
		"}\n";

		auto l_begin = l_shader.begin();
		BOOST_CHECK( qi::phrase_parse( l_begin, l_shader.end(), *l_grammar, qi::ascii::space ) );
		BOOST_CHECK( l_begin == l_shader.end() );

		if ( l_begin != l_shader.end() )
		{
			CLogger::LogWarning( std::string( l_begin, l_shader.end() ) );
		}

		delete l_grammar;

		UnloadPlugins();
	}

	void CGlslGrammarTest::TestCase_ParseTessDomainShader()
	{
	}

	void CGlslGrammarTest::TestCase_ParseTessHullShader()
	{
	}

	void CGlslGrammarTest::TestCase_ParseGeometryShader()
	{
	}

	void CGlslGrammarTest::TestCase_ParseFragmentShader()
	{
	}

	void CGlslGrammarTest::TestCase_ParseComputeShader()
	{
	}
}
