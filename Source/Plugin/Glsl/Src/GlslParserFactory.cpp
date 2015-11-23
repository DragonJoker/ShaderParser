/************************************************************************//**
* @file FactoryGlslParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief GLSL parser factory class.
*
* @details CObject factory used to manage GLSL parser creation.
*
***************************************************************************/

#include "GlslParserPch.h"

#include "GlslParserFactory.h"

BEGIN_NAMESPACE_GLSL_PARSER
{
	CFactoryGlslParser::CFactoryGlslParser()
		: CFactoryShaderParser()
	{
		// Empty
	}

	CFactoryGlslParser::~CFactoryGlslParser()
	{
		// Empty
	}

	void CFactoryGlslParser::RegisterServices()
	{
		///@remarks Register function for creation of a GlslParser object.
		//RegisterCreatorFunction( GLSL_PARSER_TYPE, CGlslParser::Create );
	}

	void CFactoryGlslParser::RegisterObjectTypes()
	{
		m_objTypes.push_back( GLSL_PARSER_TYPE );
	}

}
END_NAMESPACE_GLSL_PARSER
