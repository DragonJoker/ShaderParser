/************************************************************************//**
* @file GlslParser.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a GLSL parser.
*
***************************************************************************/

#ifndef ___GLSL_PARSER_H___
#define ___GLSL_PARSER_H___

#include "GlslParserPrerequisites.h"

#include <ShaderParserPlugin.h>
#include <ShaderParserKeywords.h>

BEGIN_NAMESPACE_GLSL_PARSER
{
	/** Class defining a GLSL parser.
	*/
	class CGlslParser
	{
	public:
		/** Default constructor.
		*/
		CGlslParser();

		/** Destructor.
		*/
		virtual ~CGlslParser();
	};

} END_NAMESPACE_GLSL_PARSER

#endif // ___PLUGIN_GLSL_PARSER_H___
