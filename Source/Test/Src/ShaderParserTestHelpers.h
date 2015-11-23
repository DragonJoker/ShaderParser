/************************************************************************//**
* @file ShaderParserTestHelpers.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Helpers for ShaderParser tests.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_TEST_HELPERS_H___
#define ___SHADER_PARSER_TEST_HELPERS_H___

#include <random>

namespace std
{
	inline ostream & operator <<( basic_ostream< char, char_traits< char > > & out, const wstring & value )
	{
		out << NAMESPACE_SHADER_PARSER::StringUtils::ToUtf8( value, "UTF-8" );
		return out;
	}
}

BEGIN_NAMESPACE_SHADER_PARSER_TEST
{
}
END_NAMESPACE_SHADER_PARSER_TEST

#endif // ___SHADER_PARSER_TEST_HELPERS_H___
