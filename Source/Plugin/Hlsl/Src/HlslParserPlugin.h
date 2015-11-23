/************************************************************************//**
* @file PluginHlslParser.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a generic HLSL parser plugin.
*
* @details Class defining a generic HLSL parser plugin.
*
***************************************************************************/

#ifndef ___PLUGIN_HLSL_PARSER_H___
#define ___PLUGIN_HLSL_PARSER_H___

#include "HlslParserPrerequisites.h"

#include <ShaderParserPlugin.h>

BEGIN_NAMESPACE_HLSL_PARSER
{
	/** Class defining a generic HLSL parser plugin.
	*/
	class CPluginHlslParser
		: public CPluginShaderParser
	{
	public:
		/** Default constructor.
		*/
		CPluginHlslParser();

		/** Destructor.
		*/
		virtual ~CPluginHlslParser();

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

} END_NAMESPACE_HLSL_PARSER

#endif // ___PLUGIN_HLSL_PARSER_H___
