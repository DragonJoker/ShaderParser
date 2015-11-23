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

BEGIN_NAMESPACE_GLSL_PARSER
{
	/** Class defining a generic GLSL parser plugin.
	*/
	class CPluginGlslParser
		: public CPluginShaderParser
	{
	public:
		/** Default constructor.
		*/
		CPluginGlslParser();

		/** Destructor.
		*/
		virtual ~CPluginGlslParser();

		///@copydoc Database::CPlugin::GetName
		virtual const String GetName() const;

		///@copydoc Database::CPlugin::Initialise
		virtual void Initialise();

		///@copydoc Database::CPlugin::Shutdown
		virtual void Shutdown();

	protected:
		///@copydoc Database::CParameterListInterface::AddBaseParameters
		virtual void AddBaseParameters();
	};

} END_NAMESPACE_GLSL_PARSER

#endif // ___PLUGIN_GLSL_PARSER_H___
