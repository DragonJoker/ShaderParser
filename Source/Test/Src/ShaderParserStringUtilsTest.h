/************************************************************************//**
 * @file ShaderParserStringUtilsTest.h
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief Class testing StringUtils functions
*
***************************************************************************/

#ifndef ___SHADER_PARSER_STRINGUTILS_TEST_H___
#define ___SHADER_PARSER_STRINGUTILS_TEST_H___

#include "ShaderParserTestPrerequisites.h"

#include <boost/test/unit_test_suite.hpp>

BEGIN_NAMESPACE_SHADER_PARSER_TEST
{
	/** ShaderParser unit test class
	*/
	class CShaderParserStringUtilsTest
	{
		/** @name Default constructor / Destructor */
		//!@{
	public:
		/** Default constructor.
		*/
		CShaderParserStringUtilsTest();

		/** Destructor.
		*/
		~CShaderParserStringUtilsTest();
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
		boost::unit_test::test_suite * testSuite; //!< Instance of the internal TS.
		//!@}

	private:
		/** @name TCs' implementation
		*/
		//!@{

		/** Test StringUtils::IsUpperCase and StringUtils::IsLowerCase functions
		*/
		void TestCase_StringUtilsIsUpperIsLower();

		/** Test StringUtils::UpperCase and StringUtils::LowerCase functions
		*/
		void TestCase_StringUtilsUpperLower();

		/** Test StringUtils::ToUpperCase and StringUtils::ToLowerCase functions
		*/
		void TestCase_StringUtilsToUpperToLower();

		/** Test StringUtils::ToStr, StringUtils::ToWStr, StringUtils::ToString, and StringUtils::ToUtf8 functions
		*/
		void TestCase_StringUtilsConversions();

		/** Test StringUtils::Split functions
		*/
		void TestCase_StringUtilsSplit();

		/** Test StringUtils::Trim functions
		*/
		void TestCase_StringUtilsTrim();

		/** Test StringUtils::Replace functions
		*/
		void TestCase_StringUtilsReplace();

		/** Test StringUtils::Formalize functions
		*/
		void TestCase_StringUtilsFormalize();

		//!@}
	};
}
END_NAMESPACE_SHADER_PARSER_TEST

#endif // ___SHADER_PARSER_STRINGUTILS_TEST_H___
