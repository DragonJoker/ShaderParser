/************************************************************************//**
 * @file ShaderParserTestPrerequisites.h
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief ShaderParserTest prerequisite header.
 *
 * @details This file contains all ShaderParserTest prerequisite instructions.
 *
 ***************************************************************************/

#ifndef ___SHADER_PARSER_TEST_PREREQUISITES_H___
#define ___SHADER_PARSER_TEST_PREREQUISITES_H___

#include <ShaderParserPrerequisites.h>
//#include <ShaderParser.h>
#include <ShaderParserStringUtils.h>

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

namespace ShaderParserTest
{
	ShaderParser::String InitialiseSingletons();
}

#endif // ___SHADER_PARSER_TEST_PREREQUISITES_H___
