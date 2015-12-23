/************************************************************************//**
* @file PluginGlslParser.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a generic GLSL parser plugin.
*
* @details Class defining a generic GLSL parser plugin.
*
***************************************************************************/

#ifndef ___GLSL_PARSER_KEYWORDS_H___
#define ___GLSL_PARSER_KEYWORDS_H___

#include "EKeyword.h"

#include <ShaderParserKeywords.h>

namespace GlslParser
{
	/** Class listing GLSL keywords
	*/
	class CKeywords
		: public ShaderParser::CParserKeywords< EKeyword >
	{
	public:
		CKeywords();
		~CKeywords();
	};
}

#endif // ___GLSL_PARSER_KEYWORDS_H___
