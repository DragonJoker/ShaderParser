/************************************************************************//**
 * @file GlslGrammarTest.h
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief Class testing CGlslGrammar.
*
***************************************************************************/

#ifndef ___GLSL_GRAMMAR_TEST_H___
#define ___GLSL_GRAMMAR_TEST_H___

#include "GlslParserTestPrerequisites.h"

#include <boost/test/unit_test_suite.hpp>

namespace GlslParserTest
{
	/** GlslGrammar unit test class
	*/
	class CGlslGrammarTest
	{
		/** @name Default constructor / Destructor */
		//!@{
	public:
		/** Default constructor.
		*/
		CGlslGrammarTest();

		/** Destructor.
		*/
		~CGlslGrammarTest();
		//!@}

	public:
		/** @name Master TS implementation
		*  Required Master TS implementation in TC
		*/
		//!@{
		/** @brief  Initialization of the Internal TS
		 @return testSuite Pointer on the TS to be included in the Master TS.
		*/
		boost::unit_test::test_suite * Init_Test_Suite();

	private:
		boost::unit_test::test_suite * m_testSuite; //!< Instance of the internal TS.
		//!@}

	private:
		/** @name TCs' implementation
		*/
		//!@{

		/** Test GLSL grammar for a simple vertex shader
		*/
		void TestCase_ParseVertexShader();

		/** Test GLSL grammar for a simple tessellation domain shader
		*/
		void TestCase_ParseTessDomainShader();

		/** Test GLSL grammar for a simple tessellation hull shader
		*/
		void TestCase_ParseTessHullShader();

		/** Test GLSL grammar for a simple geometry shader
		*/
		void TestCase_ParseGeometryShader();

		/** Test GLSL grammar for a simple fragment shader
		*/
		void TestCase_ParseFragmentShader();

		/** Test GLSL grammar for a simple compute shader
		*/
		void TestCase_ParseComputeShader();

		//!@}
	};
}

#endif // ___SHADER_GLSL_STRINGUTILS_TEST_H___
