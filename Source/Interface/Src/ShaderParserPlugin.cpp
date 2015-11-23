/************************************************************************//**
* @file PluginShaderParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a generic database plugin.
*
* @details Class defining a generic database plugin.
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderParserPlugin.h"

#include "ShaderParserFactory.h"
#include "ShaderParserFactoryManager.h"
#include "ShaderParserFileUtils.h"
#include "ShaderParserStringUtils.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	const String ERROR_DB_FACTORY_IS_NULL = STR( "ShaderParser factory is null" );

	CPluginShaderParser::CPluginShaderParser( CFactoryShaderParser * factory )
		: _factory( factory )
		, _installed( false )
	{
		if ( _factory == NULL )
		{
			PARSER_EXCEPT( EShaderParserExceptionCodes_NullPointer, ERROR_DB_FACTORY_IS_NULL );
		}
	}

	CPluginShaderParser::~CPluginShaderParser()
	{
		delete _factory;
		_factory = NULL;
	}

	void CPluginShaderParser::Install()
	{
		if ( !_installed )
		{

			//!@remarks Initialise the factory.
			_factory->Initialise();

			//!@remarks Register factory.
			CFactoryManager::Instance().AddFactory( _factory );

			_installed = true;
		}
	}

	void CPluginShaderParser::Uninstall()
	{
		if ( _installed )
		{
			//!@remarks Unregister factory.
			CFactoryManager::Instance().RemoveFactory( _factory );

			_installed = false;
		}
	}
}
END_NAMESPACE_SHADER_PARSER
