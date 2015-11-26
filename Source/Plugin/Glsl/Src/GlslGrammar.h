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

#include <ShaderGrammar.h>

BEGIN_NAMESPACE_GLSL_PARSER
{
	/** Class defining a GLSL parser.
	*/
	class CGlslGrammar
		: public CShaderGrammar
	{
	public:
		/** Default constructor.
		*/
		CGlslGrammar();

		/** Destructor.
		*/
		virtual ~CGlslGrammar();
	};

} END_NAMESPACE_GLSL_PARSER

#endif // ___PLUGIN_GLSL_PARSER_H___
