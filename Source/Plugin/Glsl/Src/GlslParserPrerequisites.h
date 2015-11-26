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

#define BEGIN_NAMESPACE_GLSL_PARSER BEGIN_NAMESPACE_SHADER_PARSER { namespace GLSL
#define NAMESPACE_GLSL_PARSER NAMESPACE_SHADER_PARSER::GLSL
#define END_NAMESPACE_GLSL_PARSER } END_NAMESPACE_SHADER_PARSER

BEGIN_NAMESPACE_SHADER_PARSER
{
	namespace GLSL
	{
		// Pre-declare classes
		// Allows use of pointers in header files without including individual .h
		// so decreases dependencies between files
		class CGlslParser;
		class CPluginGlslParser;
		class CFactoryGlslParser;

		// Factory constants
		const String FACTORY_GLSL_PARSER = STR( "Factory ShaderParser GLSL" );

		// Plugin constants
		const String GLSL_PARSER_TYPE = STR( "ShaderParser.GLSL" );
		const String PLUGIN_NAME_GLSL_PARSER = STR( "Plugin ShaderParser GLSL" );
	}
}
END_NAMESPACE_SHADER_PARSER

#endif // ___GLSL_PARSER_PREREQUISITES_H___
