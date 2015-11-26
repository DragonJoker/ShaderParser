/************************************************************************//**
 * @file GlslParserTestPluginsStaticLoader.h
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief CGlslPluginLoader class
 *
 * @details Class used to load pluginsm dynamically or statically
 *
 ***************************************************************************/

#ifndef ___GLSL_PARSER_TEST_STATIC_LOADER_H___
#define ___GLSL_PARSER_TEST_STATIC_LOADER_H___

#include "GlslParserTestPrerequisites.h"

#if defined( STATIC_LIB )
#   include <GlslParserPlugin.h>
#endif

BEGIN_NAMESPACE_GLSL_PARSER_TEST
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
	};

	/** Class used to load pluginsm dynamically or statically
	*/
	class CGlslPluginLoader
	{
	public:
		/** Default constructor
		*/
		CGlslPluginLoader();

		/** Destructor
		*/
		virtual ~CGlslPluginLoader();

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
END_NAMESPACE_GLSL_PARSER_TEST

#endif //___GLSL_PARSER_TEST_STATIC_LOADER_H___

