/************************************************************************//**
* @file PluginManager.cpp
* @author spastor
* @version 1.0
* @date 11/23/2015
*
*
* @brief Manager for plugins.
*
* @details This manager is used to load and unload plugins.
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderParserDynLib.h"
#include "ShaderParserDynLibManager.h"
#include "ShaderParserPlugin.h"
#include "ShaderParserPluginManager.h"
#include "ShaderParserException.h"

#include "ShaderParserLogger.h"

namespace ShaderParser
{
	const String SYMBOL_DLL_STOP = STR( "DllStopPlugin" );
	const String SYMBOL_DLL_START = STR( "DllStartPlugin" );

	const String INFO_DB_INSTALLING_PLUGIN = STR( "Installing plugin \"%s\"" );
	const String INFO_DB_PLUGIN_SUCCESSFULLY_INSTALLED = STR( "CPlugin \"%s\" successfully installed" );
	const String INFO_DB_UNINSTALLING_PLUGIN = STR( "Uninstalling plugin \"%s\"" );
	const String INFO_DB_PLUGIN_SUCCESSFULLY_UNINSTALLED = STR( "CPlugin \"%s\" successfully uninstalled" );

	const String ERROR_DB_SYMBOL_DLL_STOP_NOT_FOUND = STR( "Cannot find symbol DllStopPlugin in library " );
	const String ERROR_DB_SYMBOL_DLL_START_NOT_FOUND = STR( "Cannot find symbol DllStartPlugin in library " );

	typedef void ( *DLL_START_PLUGIN )();
	typedef void ( *DLL_STOP_PLUGIN )();

	CPluginManager::CPluginManager()
	{
	}

	CPluginManager::~CPluginManager()
	{
		UnloadPlugins();
	}

	void CPluginManager::ShutdownPlugins()
	{
		//!@remarks Shutdown plugins in reverse order to enforce dependencies.
		for ( auto && l_rit = m_plugins.rbegin(); l_rit != m_plugins.rend(); ++l_rit )
		{
			( *l_rit )->Shutdown();
		}
	}

	void CPluginManager::InitialisePlugins()
	{
		for ( auto && l_plugin : m_plugins )
		{
			l_plugin->Initialise();
		}
	}

	void CPluginManager::UnloadPlugins()
	{
		//!@remarks Unload all dynamic libs first.
		for ( auto && l_rit = m_pluginLibs.rbegin(); l_rit != m_pluginLibs.rend(); ++l_rit )
		{
			DynLibSPtr l_lib = l_rit->lock();

			//!@remarks Call plugin shutdown.
			DLL_STOP_PLUGIN l_func = ( DLL_STOP_PLUGIN )l_lib->GetSymbol( SYMBOL_DLL_STOP );

			if ( l_func )
			{
				//!@remarks This will call UninstallPlugin
				l_func();
			}

			//!@remarks Unload the library (destroyed by CDynLibManager).
			CDynLibManager::Instance().Unload( *l_lib );
		}

		m_pluginLibs.clear();

		//!@remarks Now deal with any remaining plugins that were registered through other means
		for ( auto && l_rit = m_plugins.rbegin(); l_rit != m_plugins.rend(); ++l_rit )
		{
			//!@remarks Note this does NOT call uninstallPlugin - this shutdown is for the detail objects
			PluginShaderParserRPtr l_plugin = ( *l_rit );
			l_plugin->Uninstall();
			delete l_plugin;
		}

		m_plugins.clear();
	}

	void CPluginManager::LoadPlugin( const String & p_pluginName )
	{
		DynLibSPtr l_lib = CDynLibManager::Instance().Load( p_pluginName );

		//!@remarks Check for existence, because if it's called more than 2 times CDynLibManager returns the existing entry.
		auto && l_it = std::find_if( m_pluginLibs.begin(), m_pluginLibs.end(), [&l_lib]( DynLibWPtr p_lib )
		{
			return l_lib == p_lib.lock();
		} );

		if ( l_it == m_pluginLibs.end() )
		{
			//!@remarks Store for later unload.
			m_pluginLibs.push_back( l_lib );

			//!@remarks Call the startup function.
			DLL_START_PLUGIN l_func = ( DLL_START_PLUGIN )l_lib->GetSymbol( SYMBOL_DLL_START );

			if ( !l_func )
			{
				StringStream l_stream;
				l_stream << ERROR_DB_SYMBOL_DLL_START_NOT_FOUND << p_pluginName;
				PARSER_EXCEPT( EShaderParserExceptionCodes_ItemNotFound, l_stream.str() );
			}

			//!@remarks This must call InstallPlugin
			l_func();
		}
	}

	void CPluginManager::InstallPlugin( PluginShaderParserRPtr p_plugin )
	{
		CLogger::LogDebug( ( Format( INFO_DB_INSTALLING_PLUGIN ) % p_plugin->GetName() ).str() );

		m_plugins.push_back( p_plugin );
		p_plugin->Install();
		p_plugin->Initialise();

		CLogger::LogDebug( ( Format( INFO_DB_PLUGIN_SUCCESSFULLY_INSTALLED ) % p_plugin->GetName() ).str() );
	}

	void CPluginManager::UninstallPlugin( PluginShaderParserRPtr p_plugin )
	{
		CLogger::LogDebug( ( Format( INFO_DB_UNINSTALLING_PLUGIN ) % p_plugin->GetName() ).str() );

		auto && l_it = std::find( m_plugins.begin(), m_plugins.end(), p_plugin );

		if ( l_it != m_plugins.end() )
		{
			p_plugin->Shutdown();
			p_plugin->Uninstall();
			m_plugins.erase( l_it );
		}

		CLogger::LogDebug( ( Format( INFO_DB_PLUGIN_SUCCESSFULLY_UNINSTALLED ) % p_plugin->GetName() ).str() );
	}

	void CPluginManager::UnloadPlugin( const String & p_pluginName )
	{
		//!@remarks Searches the lib by its name.
		auto l_it = std::find_if( m_pluginLibs.begin(), m_pluginLibs.end(), [&]( DynLibWPtr p_lib )
		{
			return p_lib.lock()->GetName() == p_pluginName;
		} );

		if ( l_it != m_pluginLibs.end() )
		{
			DynLibSPtr l_lib = l_it->lock();

			//!@remarks Call the plugin shutdown.
			DLL_STOP_PLUGIN l_func = ( DLL_STOP_PLUGIN )l_lib->GetSymbol( SYMBOL_DLL_STOP );

			if ( !l_func )
			{
				StringStream l_stream;
				l_stream  << ERROR_DB_SYMBOL_DLL_STOP_NOT_FOUND << p_pluginName;
				PARSER_EXCEPT( EShaderParserExceptionCodes_ItemNotFound, l_stream.str() );
			}

			//!@remarks This must call UninstallPlugin
			l_func();

			//!@remarks Unload the library (destroyed by CDynLibManager).
			CDynLibManager::Instance().Unload( *l_lib );

			//!@remarks Remove the lib in the list.
			m_pluginLibs.erase( l_it );
		}
	}
}
