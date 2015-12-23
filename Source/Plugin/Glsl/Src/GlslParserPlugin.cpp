/************************************************************************//**
* @file PluginGlslParser.cpp
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

#include "GlslParserPch.h"

#include "GlslParserFactory.h"
#include "GlslParserPlugin.h"

using namespace ShaderParser;

namespace GlslParser
{
	CPluginGlslParser::CPluginGlslParser()
		: CPluginShaderParser( new CFactoryGlslGrammar() )
	{
		// Empty
	}

	CPluginGlslParser::~CPluginGlslParser()
	{
		// Empty
	}

	const String CPluginGlslParser::GetName() const
	{
		return PLUGIN_NAME_GLSL_PARSER;
	}

	void CPluginGlslParser::Initialise()
	{
	}

	void CPluginGlslParser::Shutdown()
	{
	}

	void CPluginGlslParser::AddBaseParameters()
	{
		// Empty
	}
}
