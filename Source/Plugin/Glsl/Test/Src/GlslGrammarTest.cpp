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

BEGIN_NAMESPACE_GLSL_PARSER_TEST
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
		testSuite = new boost::unit_test::test_suite( "CGlslGrammarTest", __FILE__, __LINE__ );
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
END_NAMESPACE_GLSL_PARSER_TEST
