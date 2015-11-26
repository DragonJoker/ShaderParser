/************************************************************************//**
* @file EToken.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief EToken enumeration declaration.
*
* @details Enumeration of supported common tokens.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_TOKEN_H___
#define ___SHADER_PARSER_TOKEN_H___

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Enumeration of supported GLSL keywords.
	*/
	typedef enum EToken
	{
		EToken_IDENTIFIER,
		EToken_TYPE_NAME,
		EToken_FLOAT_CONSTANT,
		EToken_DOUBLE_CONSTANT,
		EToken_INT_CONSTANT,
		EToken_UINT_CONSTANT,
		EToken_BOOL_CONSTANT,
		EToken_FIELD_SELECTION,
		EToken_LEFT_OP,
		EToken_RIGHT_OP,
		EToken_INC_OP,
		EToken_DEC_OP,
		EToken_LE_OP,
		EToken_GE_OP,
		EToken_EQ_OP,
		EToken_NE_OP,
		EToken_AND_OP,
		EToken_OR_OP,
		EToken_XOR_OP,

		EToken_MUL_ASSIGN,
		EToken_DIV_ASSIGN,
		EToken_ADD_ASSIGN,
		EToken_MOD_ASSIGN,
		EToken_LEFT_ASSIGN,
		EToken_RIGHT_ASSIGN,
		EToken_AND_ASSIGN,
		EToken_XOR_ASSIGN,
		EToken_OR_ASSIGN,
		EToken_SUB_ASSIGN,

		EToken_LEFT_PAREN,
		EToken_RIGHT_PAREN,
		EToken_LEFT_BRACKET,
		EToken_RIGHT_BRACKET,
		EToken_LEFT_BRACE,
		EToken_RIGHT_BRACE,
		EToken_DOT,
		EToken_COMMA,
		EToken_COLON,
		EToken_EQUAL,
		EToken_SEMICOLON,
		EToken_BANG,
		EToken_DASH,
		EToken_TILDE,
		EToken_PLUS,
		EToken_STAR,
		EToken_SLASH,
		EToken_PERCENT,
		EToken_LEFT_ANGLE,
		EToken_RIGHT_ANGLE,
		EToken_VERTICAL_BAR,
		EToken_CARET,
		EToken_AMPERSAND,
		EToken_QUESTION,

		EToken_COUNT
	}	EToken;
}
END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_TOKEN_H___
