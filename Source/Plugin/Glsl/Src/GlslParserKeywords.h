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

BEGIN_NAMESPACE_GLSL_PARSER
{
	/** Class listing GLSL keywords
	*/
	class CKeywords
		: public CParserKeywords< EKeyword >
	{
	public:
		CKeywords();
		~CKeywords();
	};
}
END_NAMESPACE_GLSL_PARSER

#endif // ___GLSL_PARSER_KEYWORDS_H___
