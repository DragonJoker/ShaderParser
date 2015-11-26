/************************************************************************//**
* @file FactoryShaderParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief ShaderParser factory class.
*
* @details CFactoryShaderGrammar is used to manage CShaderParser creation.
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderParserFactory.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	CFactoryShaderGrammar::CFactoryShaderGrammar()
	{
		// Empty
	}

	CFactoryShaderGrammar::~CFactoryShaderGrammar()
	{
		// Empty
	}

	void CFactoryShaderGrammar::Initialise()
	{
		RegisterServices();
		RegisterObjectTypes();
	}

	void CFactoryShaderGrammar::RegisterCreatorFunction( const String & idKey, CreatorFunction classCreator )
	{
		auto && l_it = GetMapFactory()->find( idKey );

		if ( l_it != GetMapFactory()->end() )
		{
			PARSER_EXCEPT( EShaderParserExceptionCodes_DuplicateItem, ERROR_DUPLICATE_FUNCTION );
		}

		GetMapFactory()->insert( std::pair< String, CreatorFunction >( idKey, classCreator ) );
	}

	CShaderGrammar * CFactoryShaderGrammar::CreateInstance( const String & idKey )
	{
		auto && l_it = GetMapFactory()->find( idKey );

		if ( l_it != GetMapFactory()->end() )
		{
			if ( l_it->second )
			{
				return l_it->second();
			}
		}

		return NULL;
	}
}
END_NAMESPACE_SHADER_PARSER
