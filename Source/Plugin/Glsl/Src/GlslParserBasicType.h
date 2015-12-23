/************************************************************************//**
* @file GlslParserBasicType.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class listing GLSL basic types.
*
***************************************************************************/

#ifndef ___GLSL_PARSER_BASIC_TYPES_H___
#define ___GLSL_PARSER_BASIC_TYPES_H___

#include "EKeyword.h"

#include <ShaderParserBasicTypes.h>

namespace GlslParser
{
	/** Class listing GLSL basic types.
	*/
	class CBasicTypes
		: public ShaderParser::CParserBasicTypes< EKeyword >
	{
	public:
		CBasicTypes();
		~CBasicTypes();
	};
}

#endif // ___GLSL_PARSER_BASIC_TYPES_H___
