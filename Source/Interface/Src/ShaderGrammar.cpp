/************************************************************************//**
* @file ShaderParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a shader parser.
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderGrammar.h"
#include "ShaderParserKeywords.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	CShaderGrammar::CShaderGrammar()
		: Grammar( translation_unit )
	{
		Rule non_digit = qi::ascii::alpha
			| qi::char_( '_' );

		Rule digit = qi::standard::digit;

		Rule nonzero_digit = digit - qi::char_( '0' );

		Rule octal_digit = qi::int_parser< int, 8 >();

		Rule hexadecimal_digit = qi::standard::xdigit;

		Rule sign = qi::char_( '-' )
			| qi::char_( '+' );

		Rule integer_suffix = qi::char_( 'u' )
			| qi::char_( 'U' );

		Rule decimal_constant = nonzero_digit
			| ( decimal_constant >> digit );

		Rule octal_constant = -sign >> qi::char_( '0' )
			| ( octal_constant >> octal_digit );

		Rule hexadecimal_constant = qi::string( "0x" ) >> hexadecimal_digit
			| qi::string( "0X" ) >> hexadecimal_digit
			| hexadecimal_constant >> hexadecimal_digit;

		identifier = non_digit
			| ( identifier >> non_digit )
			| ( identifier >> digit );

		integer_constant = -sign >> decimal_constant >> -integer_suffix
			| octal_constant >> -integer_suffix
			| hexadecimal_constant >> -integer_suffix;

		uinteger_constant = decimal_constant >> -integer_suffix
			| octal_constant >> -integer_suffix
			| hexadecimal_constant >> -integer_suffix;

		digit_sequence = digit >> *digit;

		floating_suffix = qi::char_( 'f' )
			| qi::char_( 'F' )
			| qi::string( "lf" )
			| qi::string( "LF" )
			| qi::string( "d" )
			| qi::string( "D" );

		exponent_part = qi::char_( 'e' ) >> -sign >> digit_sequence
			| qi::char_( 'E' ) >> -sign >> digit_sequence;

		fractional_constant = digit_sequence >> qi::char_( '.' ) >> digit_sequence
			| digit_sequence >> qi::char_( '.' )
			| qi::char_( '.' ) >> digit_sequence;

		floating_constant = fractional_constant >> -exponent_part >> -floating_suffix
			| digit_sequence >> exponent_part >> -floating_suffix;

		double_constant = fractional_constant >> -exponent_part >> -floating_suffix
			| digit_sequence >> exponent_part >> -floating_suffix;

		bool_constant = qi::string( "true" )
			| qi::string( "false" );
	}

CShaderGrammar::~CShaderGrammar()
	{
	}
}
END_NAMESPACE_SHADER_PARSER
