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
#include "GlslGrammar.h"

using namespace ShaderParser;

namespace GlslParser
{
	CFactoryGlslGrammar::CFactoryGlslGrammar()
		: CFactoryShaderGrammar()
	{
		// Empty
	}

	CFactoryGlslGrammar::~CFactoryGlslGrammar()
	{
		// Empty
	}

	void CFactoryGlslGrammar::RegisterServices()
	{
		///@remarks Register function for creation of a CGlslGrammar object.
		RegisterCreatorFunction( GLSL_PARSER_TYPE, CGlslGrammar::Create );
	}

	void CFactoryGlslGrammar::RegisterObjectTypes()
	{
		m_objTypes.push_back( GLSL_PARSER_TYPE );
	}
}
