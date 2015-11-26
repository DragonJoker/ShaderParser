/************************************************************************//**
 * @file GlslParserTestPluginLoader.cpp
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief Specialization of CStaticLibLoader for ShaderParser needed plugin
 *
 * @details Loads the static library of the ShaderParser needed plugin
 *
 ***************************************************************************/

#include "GlslParserTestPch.h"

#include "GlslParserTestPluginLoader.h"

#include <ShaderParserPluginManager.h>

BEGIN_NAMESPACE_GLSL_PARSER_TEST
{
	//***********************************************************************************************

	CPluginConfigBase::CPluginConfigBase( bool load )
		: _load( load )
	{
	}

	//***********************************************************************************************

#if defined( STATIC_LIB )
	template< typename PluginType >
	CPluginConfig( bool load )
		: CPluginConfigBase( load )
	{
	}

	template< typename PluginType >
	void CPluginConfig< PluginType >::Load()
	{
		if ( _load && !_plugin )
		{
			//!@remarks Create the plugin.
			_plugin = new PluginType;

			//!@remarks Register the plugin.
			CPluginManager::Instance().InstallPlugin( _plugin );
		}
	}

	template< typename PluginType >
	void CPluginConfig< PluginType >::Unload()
	{
		if ( _plugin )
		{
			//!@remarks Unregister the plugin.
			CPluginManager::Instance().UninstallPlugin( _plugin );

			//!@remarks Delete the plugin.
			delete _plugin;
			_plugin = NULL;
		}
	}
#else

	//***********************************************************************************************

	namespace
	{
#if defined( _WIN32 )
		static const String LIB_PREFIX;
		static const String LIB_EXT = STR( ".dll" );
#else
		static const String LIB_PREFIX = STR( "lib" );
		static const String LIB_EXT = STR( ".so" );
#endif
#if defined( NDEBUG )
		static const String LIB_SUFFIX;
#else
		static const String LIB_SUFFIX = "d";
#endif

		String GetLibName( const String & name )
		{
			return LIB_PREFIX + name + LIB_SUFFIX + LIB_EXT;
		}
	}

	//***********************************************************************************************

	CPluginConfig::CPluginConfig( bool load, const String & path, const String & name )
		: CPluginConfigBase( load )
		, _path( path )
		, _plugin( name )
	{
	}

	void CPluginConfig::Load()
	{
		if ( _load )
		{
			CPluginManager::Instance().LoadPlugin( _path + GetLibName( _plugin ) );
		}
	}

	void CPluginConfig::Unload()
	{
		if ( _load )
		{
			CPluginManager::Instance().UnloadPlugin( _path + GetLibName( _plugin ) );
		}
	}
#endif

	//***********************************************************************************************

	CGlslPluginLoader::CGlslPluginLoader()
		: _config()
	{
	}

	CGlslPluginLoader::~CGlslPluginLoader()
	{
	}

	void CGlslPluginLoader::Load( SPluginsConfig && config )
	{
		_config.m_glsl = std::move( config.m_glsl );
		OnLoad();
	}

	void CGlslPluginLoader::Unload()
	{
		OnUnload();
	}

	void CGlslPluginLoader::OnLoad()
	{
		_config.m_glsl->Load();
	}

	void CGlslPluginLoader::OnUnload()
	{
		_config.m_glsl->Unload();
	}

	//***********************************************************************************************
}
END_NAMESPACE_GLSL_PARSER_TEST

