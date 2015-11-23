/************************************************************************//**
 * @file ShaderParserTestPluginsStaticLoader.h
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief CTestPluginsLoader class
 *
 * @details Class used to load pluginsm dynamically or statically
 *
 ***************************************************************************/

#ifndef ___SHADER_PARSER_TEST_STATIC_LOADER_H___
#define ___SHADER_PARSER_TEST_STATIC_LOADER_H___

#include "ShaderParserTestPrerequisites.h"

#if defined( STATIC_LIB )
#   include <PluginShaderParserMySql.h>
#   include <PluginShaderParserOdbcMySql.h>
#   include <PluginShaderParserOdbcMsSql.h>
#endif

BEGIN_NAMESPACE_SHADER_PARSER_TEST
{
	/** Structure holding the needed loading informations about one plugin
	*/
	class CPluginConfigBase
	{
	public:
		/** Constructor
		*/
		CPluginConfigBase( bool load );

		/** Loads the plugin, if needed
		*/
		virtual void Load() = 0;

		/** Unloads the plugin, if needed
		*/
		virtual void Unload() = 0;

		//! Tells if plugin is to load/loaded
		bool _load = false;
	};

#if defined( STATIC_LIB )
	template< typename PluginType >
	class CPluginConfig
		: public CPluginConfigBase
	{
	public:
		/** Constructor
		*/
		CPluginConfig( bool load );

		/** Loads the plugin, if needed
		*/
		void Load();

		/** Unloads the plugin, if needed
		*/
		void Unload();

		//! The plugin
		PluginType * _plugin = NULL;
	};
#else
	/** Structure holding the needed loading informations about one plugin
	*/
	class CPluginConfig
		: public CPluginConfigBase
	{
	public:
		/** Constructor
		*/
		CPluginConfig( bool load, const String & path, const String & name );

		/** Loads the plugin, if needed
		*/
		void Load();

		/** Unloads the plugin, if needed
		*/
		void Unload();

		//! The plugins path
		String _path;
		//! The plugin name
		String _plugin;
	};
#endif

	/** Structure holding the needed informations about plugins to load, and plugins path
	*/
	struct SPluginsConfig
	{
		//! The GLSL plugin
		std::unique_ptr< CPluginConfigBase > m_glsl;
		//! The HLSL plugin
		std::unique_ptr< CPluginConfigBase > m_hlsl;
	};

	/** Class used to load pluginsm dynamically or statically
	*/
	class CTestPluginsLoader
	{
	public:
		/** Default constructor
		*/
		CTestPluginsLoader();

		/** Destructor
		*/
		virtual ~CTestPluginsLoader();

		/** Load the plugins wanted in the given config
		@param[in] config
			The config
		*/
		void Load( SPluginsConfig && config );

		/** Unloads every loaded plugin
		*/
		void Unload();

	private:
		/** Load all the needed plugins.
		*/
		void OnLoad();

		/** Unload all the needed plugins.
		*/
		void OnUnload();

		//! The current configuration
		SPluginsConfig _config;
	};
}
END_NAMESPACE_SHADER_PARSER_TEST

#endif //___SHADER_PARSER_TEST_STATIC_LOADER_H___

