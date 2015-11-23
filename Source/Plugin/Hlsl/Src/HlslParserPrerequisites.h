/************************************************************************//**
* @file HlslParserPrerequisites.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief HLSL parser prerequisite header.
*
* @details This file contains all HLSL parser prerequisite instructions.
*
***************************************************************************/

#ifndef ___HLSL_PARSER_PREREQUISITES_H___
#define ___HLSL_PARSER_PREREQUISITES_H___

#include <ShaderParserPrerequisites.h>

#define BEGIN_NAMESPACE_HLSL_PARSER BEGIN_NAMESPACE_SHADER_PARSER { namespace HLSL
#define NAMESPACE_HLSL_PARSER NAMESPACE_SHADER_PARSER::HLSL
#define END_NAMESPACE_HLSL_PARSER } END_NAMESPACE_SHADER_PARSER

BEGIN_NAMESPACE_SHADER_PARSER
{
	namespace HLSL
	{
		// Pre-declare classes
		// Allows use of pointers in header files without including individual .h
		// so decreases dependencies between files
		class CHlslParser;
		class CPluginHlslParser;
		class CFactoryHlslParser;

		// Factory constants
		const String FACTORY_HLSL_PARSER = STR( "Factory ShaderParser HLSL" );

		// Plugin constants
		const String HLSL_PARSER_TYPE = STR( "ShaderParser.HLSL" );
		const String PLUGIN_NAME_HLSL_PARSER = STR( "Plugin ShaderParser HLSL" );
	}
}
END_NAMESPACE_SHADER_PARSER

#endif // ___HLSL_PARSER_PREREQUISITES_H___
