/************************************************************************//**
* @file FactoryHlslParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief HLSL parser factory class.
*
* @details CObject factory used to manage HLSL parser creation.
*
***************************************************************************/

#include "HlslParserPch.h"

#include "HlslParserFactory.h"

BEGIN_NAMESPACE_HLSL_PARSER
{
	CFactoryHlslParser::CFactoryHlslParser()
		: CFactoryShaderGrammar()
	{
		// Empty
	}

	CFactoryHlslParser::~CFactoryHlslParser()
	{
		// Empty
	}

	void CFactoryHlslParser::RegisterServices()
	{
		///@remarks Register function for creation of a HlslParser object.
		//RegisterCreatorFunction( HLSL_PARSER_TYPE, CHlslParser::Create );
	}

	void CFactoryHlslParser::RegisterObjectTypes()
	{
		m_objTypes.push_back( HLSL_PARSER_TYPE );
	}

}
END_NAMESPACE_HLSL_PARSER
