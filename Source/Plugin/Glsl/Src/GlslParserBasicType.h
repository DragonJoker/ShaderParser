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

BEGIN_NAMESPACE_GLSL_PARSER
{
	/** Class listing GLSL basic types.
	*/
	class CBasicTypes
		: public CParserBasicTypes< EKeyword >
	{
	public:
		CBasicTypes();
		~CBasicTypes();
	};
}
END_NAMESPACE_GLSL_PARSER

#endif // ___GLSL_PARSER_BASIC_TYPES_H___
