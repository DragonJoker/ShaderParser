/************************************************************************//**
* @file ShaderParser.h
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

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Class defining a shader parser.
	*/
	class CShaderGrammar
		: public Grammar
	{
	public:
		/** Default constructor.
		*/
		ShaderParserExport CShaderGrammar();

		/** Destructor.
		*/
		ShaderParserExport virtual ~CShaderGrammar();

	protected:
		Rule identifier;
		Rule digit_sequence;
		Rule integer_constant;
		Rule uinteger_constant;
		Rule floating_suffix;
		Rule exponent_part;
		Rule fractional_constant;
		Rule floating_constant;
		Rule double_constant;
		Rule bool_constant;
		Rule translation_unit;
	};

} END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_H___
