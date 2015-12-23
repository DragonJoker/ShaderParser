/************************************************************************//**
* @file PluginGlslParser.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a generic GLSL parser plugin.
*
* @details Class defining a generic GLSL parser plugin.
*
***************************************************************************/

#ifndef ___PLUGIN_GLSL_PARSER_H___
#define ___PLUGIN_GLSL_PARSER_H___

#include "GlslParserPrerequisites.h"

#include <ShaderParserPlugin.h>

namespace GlslParser
{
	/** Class defining a generic GLSL parser plugin.
	*/
	class CPluginGlslParser
		: public ShaderParser::CPluginShaderParser
	{
	public:
		/** Default constructor.
		*/
		CPluginGlslParser();

		/** Destructor.
		*/
		virtual ~CPluginGlslParser();

		///@copydoc Database::CPlugin::GetName
		virtual const ShaderParser::String GetName() const;

		///@copydoc Database::CPlugin::Initialise
		virtual void Initialise();

		///@copydoc Database::CPlugin::Shutdown
		virtual void Shutdown();

	protected:
		///@copydoc Database::CParameterListInterface::AddBaseParameters
		virtual void AddBaseParameters();
	};
}

#endif // ___PLUGIN_GLSL_PARSER_H___
