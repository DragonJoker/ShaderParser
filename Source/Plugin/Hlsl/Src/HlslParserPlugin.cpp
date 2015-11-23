/************************************************************************//**
* @file PluginHlslParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a generic HLSL parser plugin.
*
* @details Class defining a generic HLSL parser plugin.
*
***************************************************************************/

#include "HlslParserPch.h"

#include "HlslParserFactory.h"
#include "HlslParserPlugin.h"

BEGIN_NAMESPACE_HLSL_PARSER
{
	CPluginHlslParser::CPluginHlslParser()
		: CPluginShaderParser( new CFactoryHlslParser() )
	{
		// Empty
	}

	CPluginHlslParser::~CPluginHlslParser()
	{
		// Empty
	}

	const String CPluginHlslParser::GetName() const
	{
		return HLSL::PLUGIN_NAME_HLSL_PARSER;
	}

	void CPluginHlslParser::Initialise()
	{
	}

	void CPluginHlslParser::Shutdown()
	{
	}

	void CPluginHlslParser::AddBaseParameters()
	{
		// Empty
	}
}
END_NAMESPACE_HLSL_PARSER
