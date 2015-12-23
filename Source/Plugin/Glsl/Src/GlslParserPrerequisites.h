/************************************************************************//**
* @file GlslParserPrerequisites.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief GLSL parser prerequisite header.
*
* @details This file contains all GLSL parser prerequisite instructions.
*
***************************************************************************/

#ifndef ___GLSL_PARSER_PREREQUISITES_H___
#define ___GLSL_PARSER_PREREQUISITES_H___

#include <ShaderParserPrerequisites.h>

#include <ShaderParserLogger.h>

namespace GlslParser
{
	// Pre-declare classes
	// Allows use of pointers in header files without including individual .h
	// so decreases dependencies between files
	class CPluginGlslParser;
	class CFactoryGlslParser;

	class CGlslGrammar;
	class CGlslExpressionGrammar;
	class CGlslTypeGrammar;

	// Factory constants
	const ShaderParser::String FACTORY_GLSL_PARSER = STR( "Factory ShaderParser GLSL" );

	// Plugin constants
	const ShaderParser::String GLSL_PARSER_TYPE = STR( "ShaderParser.GLSL" );
	const ShaderParser::String PLUGIN_NAME_GLSL_PARSER = STR( "Plugin ShaderParser GLSL" );
}

#endif // ___GLSL_PARSER_PREREQUISITES_H___
