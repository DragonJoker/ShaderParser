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

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Class defining a shader parser.
	*/
	class CShaderParser
	{
	public:
		/** Default constructor.
		*/
		ShaderParserExport CShaderParser();

		/** Destructor.
		*/
		ShaderParserExport virtual ~CShaderParser();

		/** Parses a shader in a string.
		@param[in] p_shader
			The shader text.
		*/
		ShaderParserExport virtual bool Parse( String const & p_shader ) = 0;
	};

} END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_H___
