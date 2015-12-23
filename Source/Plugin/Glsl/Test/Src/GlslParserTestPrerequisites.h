/************************************************************************//**
 * @file GlslParserTestPrerequisites.h
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief ShaderParserTest prerequisite header.
 *
 * @details This file contains all GlslParserTest prerequisite instructions.
 *
 ***************************************************************************/

#ifndef ___GLSL_PARSER_TEST_PREREQUISITES_H___
#define ___GLSL_PARSER_TEST_PREREQUISITES_H___

#include <GlslParserPrerequisites.h>

#ifdef BOOST_STATIC_LIB
#   define BOOST_TEST_MAIN
#else
#   define BOOST_TEST_NO_MAIN
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/execution_monitor.hpp>
#include <boost/test/debug.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/test/results_collector.hpp>
#include <boost/test/progress_monitor.hpp>
#include <boost/test/results_reporter.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/detail/global_typedef.hpp>

namespace GlslParserTest
{
	ShaderParser::String InitialiseSingletons();
	void LoadPlugins( const ShaderParser::String & path );
	void UnloadPlugins();
}

#endif // ___GLSL_PARSER_TEST_PREREQUISITES_H___
