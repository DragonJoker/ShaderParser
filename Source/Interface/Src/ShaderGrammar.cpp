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
		, LEFT_ANGLE( qi::char_( '<' ), "LEFT_ANGLE" )
		, RIGHT_ANGLE( qi::char_( '>' ), "RIGHT_ANGLE" )
		, LEFT_PAREN( qi::char_( '(' ), "LEFT_PAREN" )
		, RIGHT_PAREN( qi::char_( ')' ), "RIGHT_PAREN" )
		, LEFT_BRACKET( qi::char_( '[' ), "LEFT_BRACKET" )
		, RIGHT_BRACKET( qi::char_( ']' ), "RIGHT_BRACKET" )
		, LEFT_BRACE( qi::char_( '{' ), "LEFT_BRACE" )
		, RIGHT_BRACE( qi::char_( '}' ), "RIGHT_BRACE" )
		, AMPERSAND( qi::char_( '&' ), "AMPERSAND(" )
		, CARET( qi::char_( '^' ), "CARET" )
		, VERTICAL_BAR( qi::char_( '|' ), "VERTICAL_BAR" )
		, QUESTION( qi::char_( '?' ), "QUESTION" )
		, EQUAL( qi::char_( '=' ), "EQUAL" )
		, COLON( qi::char_( ':' ), "COLON" )
		, COMMA( qi::char_( ',' ), "COMMA" )
		, DOT( qi::char_( '.' ), "DOT" )
		, SEMICOLON( qi::char_( ';' ), "SEMICOLON" )
		, BANG( qi::char_( '!' ), "BANG" )
		, PLUS( qi::char_( '+' ), "PLUS" )
		, DASH( qi::char_( '-' ), "DASH" )
		, TILDE( qi::char_( '~' ), "TILDE" )
		, STAR( qi::char_( '*' ), "STAR" )
		, SLASH( qi::char_( '/' ), "SLASH" )
		, PERCENT( qi::char_( '%' ), "PERCENT" )
		, LEFT_OP( qi::string( "<<" ), "LEFT_OP" )
		, RIGHT_OP( qi::string( ">>" ), "RIGHT_OP" )
		, LE_OP( qi::string( "<=" ), "LE_OP" )
		, GE_OP( qi::string( ">=" ), "GE_OP" )
		, EQ_OP( qi::string( "==" ), "EQ_OP" )
		, NE_OP( qi::string( "!=" ), "NE_OP" )
		, AND_OP( qi::string( "&&" ), "AND_OP" )
		, OR_OP( qi::string( "||" ), "OR_OP" )
		, XOR_OP( qi::string( "^^" ), "XOR_OP" )
		, MUL_ASSIGN( qi::string( "*=" ), "MUL_ASSIGN" )
		, DIV_ASSIGN( qi::string( "/=" ), "DIV_ASSIGN" )
		, MOD_ASSIGN( qi::string( "%=" ), "MOD_ASSIGN" )
		, ADD_ASSIGN( qi::string( "+=" ), "ADD_ASSIGN" )
		, SUB_ASSIGN( qi::string( "-=" ), "SUB_ASSIGN" )
		, LEFT_ASSIGN( qi::string( "<<=" ), "LEFT_ASSIGN" )
		, RIGHT_ASSIGN( qi::string( ">>=" ), "RIGHT_ASSIGN" )
		, AND_ASSIGN( qi::string( "&=" ), "AND_ASSIGN" )
		, XOR_ASSIGN( qi::string( "^=" ), "XOR_ASSIGN" )
		, OR_ASSIGN( qi::string( "|=" ), "OR_ASSIGN" )
		, INC_OP( qi::string( "++" ), "INC_OP" )
		, DEC_OP( qi::string( "--" ), "DEC_OP" )
		, ELSE( qi::string( "else" ), "ELSE" )
		, IF( qi::string( "if" ), "IF" )
		, CASE( qi::string( "case" ), "CASE" )
		, DEFAULT( qi::string( "default" ), "DEFAULT" )
		, SWITCH( qi::string( "switch" ), "SWITCH" )
		, WHILE( qi::string( "while" ), "WHILE" )
		, DO( qi::string( "do" ), "DO" )
		, FOR( qi::string( "for" ), "FOR" )
		, CONTINUE( qi::string( "continue" ), "CONTINUE" )
		, BREAK( qi::string( "break" ), "BREAK" )
		, RETURN( qi::string( "return" ), "RETURN" )
	{
		non_digit = qi::ascii::alpha
			| qi::char_( '_' );
		non_digit.name( "non_digit" );

		digit = qi::standard::digit;
		digit.name( "digit" );

		nonzero_digit = digit - qi::char_( '0' );
		nonzero_digit.name( "nonzero_digit" );

		octal_digit = qi::int_parser< int, 8 >();
		octal_digit.name( "octal_digit" );

		hexadecimal_digit = qi::standard::xdigit;
		hexadecimal_digit.name( "hexadecimal_digit" );

		sign = qi::char_( '-' )
			| qi::char_( '+' );
		sign.name( "sign" );

		integer_suffix = qi::char_( 'u' )
			| qi::char_( 'U' );
		integer_suffix.name( "integer_suffix" );

		decimal_constant = nonzero_digit
			| ( decimal_constant >> digit );
		decimal_constant.name( "decimal_constant" );

		octal_constant = -sign >> qi::char_( '0' )
			| ( octal_constant >> octal_digit );
		octal_constant.name( "octal_constant" );

		hexadecimal_constant = qi::string( "0x" ) >> hexadecimal_digit
			| qi::string( "0X" ) >> hexadecimal_digit
			| hexadecimal_constant >> hexadecimal_digit;
		hexadecimal_constant.name( "hexadecimal_constant" );

		identifier = non_digit
			| ( identifier >> non_digit )
			| ( identifier >> digit );
		identifier.name( "identifier" );

		type_name = identifier
			| ( identifier >> non_digit )
			| ( identifier >> digit );
		type_name.name( "type_name" );

		integer_constant = -sign >> decimal_constant >> -integer_suffix
			| octal_constant >> -integer_suffix
			| hexadecimal_constant >> -integer_suffix;
		integer_constant.name( "integer_constant" );

		uinteger_constant = decimal_constant >> -integer_suffix
			| octal_constant >> -integer_suffix
			| hexadecimal_constant >> -integer_suffix;
		uinteger_constant.name( "uinteger_constant" );

		digit_sequence = digit >> *digit;
		digit_sequence.name( "digit_sequence" );

		floating_suffix = qi::char_( 'f' )
			| qi::char_( 'F' )
			| qi::string( "lf" )
			| qi::string( "LF" )
			| qi::string( "d" )
			| qi::string( "D" );
		floating_suffix.name( "floating_suffix" );

		exponent_part = qi::char_( 'e' ) >> -sign >> digit_sequence
			| qi::char_( 'E' ) >> -sign >> digit_sequence;
		exponent_part.name( "exponent_part" );

		fractional_constant = digit_sequence >> qi::char_( '.' ) >> digit_sequence
			| digit_sequence >> qi::char_( '.' )
			| qi::char_( '.' ) >> digit_sequence;
		fractional_constant.name( "fractional_constant" );

		floating_constant = fractional_constant >> -exponent_part >> -floating_suffix
			| digit_sequence >> exponent_part >> -floating_suffix;
		floating_constant.name( "floating_constant" );

		double_constant = fractional_constant >> -exponent_part >> -floating_suffix
			| digit_sequence >> exponent_part >> -floating_suffix;
		double_constant.name( "double_constant" );

		bool_constant = qi::string( "true" )
			| qi::string( "false" );
		bool_constant.name( "bool_constant" );
	}

CShaderGrammar::~CShaderGrammar()
	{
	}
}
END_NAMESPACE_SHADER_PARSER
