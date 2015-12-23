/************************************************************************//**
* @file ShaderGrammar.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a shader parser.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_H___
#define ___SHADER_PARSER_H___

#include "EToken.h"

#if defined( VOID )
#	undef VOID
#endif

namespace ShaderParser
{
	/** Class defining a shader parser.
	*/
	class CShaderGrammar
		: public Grammar
	{
	public:
		/** Default constructor.
		*/
		ShaderParserExport CShaderGrammar( Rule const & translation_unit );

		/** Destructor.
		*/
		ShaderParserExport virtual ~CShaderGrammar();

	protected:
		Rule non_digit;
		Rule digit;
		Rule nonzero_digit;
		Rule octal_digit;
		Rule hexadecimal_digit;
		Rule sign;
		Rule integer_suffix;
		Rule decimal_constant;
		Rule octal_constant;
		Rule hexadecimal_constant;
		Rule identifier;
		Rule type_name;
		Rule digit_sequence;
		Rule integer_constant;
		Rule uinteger_constant;
		Rule floating_suffix;
		Rule exponent_part;
		Rule fractional_constant;
		Rule floating_constant;
		Rule double_constant;
		Rule bool_constant;

		Rule LEFT_ANGLE;
		Rule RIGHT_ANGLE;
		Rule LEFT_PAREN;
		Rule RIGHT_PAREN;
		Rule LEFT_BRACKET;
		Rule RIGHT_BRACKET;
		Rule LEFT_BRACE;
		Rule RIGHT_BRACE;
		Rule AMPERSAND;
		Rule CARET;
		Rule VERTICAL_BAR;
		Rule QUESTION;
		Rule EQUAL;
		Rule COLON;
		Rule COMMA;
		Rule DOT;
		Rule SEMICOLON;
		Rule BANG;
		Rule PLUS;
		Rule DASH;
		Rule TILDE;
		Rule STAR;
		Rule SLASH;
		Rule PERCENT;

		Rule LEFT_OP;
		Rule RIGHT_OP;
		Rule LE_OP;
		Rule GE_OP;
		Rule EQ_OP;
		Rule NE_OP;
		Rule AND_OP;
		Rule OR_OP;
		Rule XOR_OP;
		Rule MUL_ASSIGN;
		Rule DIV_ASSIGN;
		Rule MOD_ASSIGN;
		Rule ADD_ASSIGN;
		Rule SUB_ASSIGN;
		Rule LEFT_ASSIGN;
		Rule RIGHT_ASSIGN;
		Rule AND_ASSIGN;
		Rule XOR_ASSIGN;
		Rule OR_ASSIGN;
		Rule INC_OP;
		Rule DEC_OP;

		Rule ELSE;
		Rule IF;
		Rule CASE;
		Rule DEFAULT;
		Rule SWITCH;
		Rule WHILE;
		Rule DO;
		Rule FOR;
		Rule CONTINUE;
		Rule BREAK;
		Rule RETURN;

		Rule VOID;
		Rule FLOAT;
		Rule DOUBLE;
		Rule INT;
		Rule UINT;
		Rule BOOL;
	};
}

#endif // ___SHADER_PARSER_H___
