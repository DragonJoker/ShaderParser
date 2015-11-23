/************************************************************************//**
* @file PluginShaderParser.h
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

#ifndef ___SHADER_PARSER_PLUGIN_SHADER_PARSER_H___
#define ___SHADER_PARSER_PLUGIN_SHADER_PARSER_H___

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Class defining a generic database plugin.
	*/
	class CPluginShaderParser
	{
	public:
		/** Constructor.
		@param factory
			The factory used to manage CShaderParser object creation.
		*/
		ShaderParserExport CPluginShaderParser( CFactoryShaderParser * factory );

		/** Destructor.
		*/
		ShaderParserExport virtual ~CPluginShaderParser();

		/** Perform the plugin initial installation sequence.
		@remarks
			An implementation must be supplied for this method. It must perform
			the startup tasks necessary to install anything else that is not dependent
			on system initialization, ie only dependent on the core. It must
			not perform any operations that would create specific objects at this stage,
			that should be done in Initialise ().
		*/
		ShaderParserExport virtual void Install();

		/** Perform the final plugin uninstallation sequence.
		@remarks
			An implementation must be supplied for this method. It must perform
			the cleanup tasks which haven't already been performed in Shutdown ()
			(e.g. final deletion of custom instances, if you kept them around incase
			the system was reinitialised). At this stage you cannot be sure what other
			plugins are still loaded or active. It must therefore not perform any
			operations that would reference any specific objects - those
			should have been sorted out in the 'Shutdown' method.
		*/
		ShaderParserExport virtual void Uninstall();

		/** Get plugin mame.
		@return
			Return the plugin name.
		@remarks
			An implementation must be supplied for this method to uniquely
			identify the plugin.
		*/
		ShaderParserExport virtual const String GetName() const = 0;

		/** Perform any tasks the plugin needs to perform on full system initialization.
		@remarks
			An implementation must be supplied for this method. It is called
			just after the system is fully initialised. You can use this hook to create
			any resources which are have specific implementations.
		*/
		ShaderParserExport virtual void Initialise() = 0;

		/** Perform any tasks the plugin needs to perform when the system is shut down.
		@remarks
			An implementation must be supplied for this method.
			This method is called just before key parts of the system are unloaded.
			You should use this hook to free up resources and decouple custom objects
			from the system, whilst all the instances of other plugins still exist.
		*/
		ShaderParserExport virtual void Shutdown() = 0;

	protected:
		//! ShaderParser object factory.
		CFactoryShaderParser * _factory;
		//! Plugin install state.
		bool _installed;
	};

}
END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_PLUGIN_SHADER_PARSER_H___
