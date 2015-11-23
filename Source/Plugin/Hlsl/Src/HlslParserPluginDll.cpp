/************************************************************************//**
* @file DllPluginHlslParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief DLL Interface.
*
* @details DLL Interface.
*
***************************************************************************/

#include "HlslParserPch.h"

#include "HlslParserPlugin.h"

#include <ShaderParserPluginManager.h>

#if defined( _WIN32 ) && !defined ( __MINGW32__ ) && !defined ( STATIC_LIB )
#	ifdef HlslParser_EXPORTS
#		define HlslParserExport __declspec ( dllexport )
#	else
#		if defined ( __MINGW32__ )
#			define HlslParserExport
#		else
#			define HlslParserExport __declspec ( dllimport )
#		endif
#	endif
#else
#    define HlslParserExport
#endif

BEGIN_NAMESPACE_HLSL_PARSER
{
	CPluginHlslParser * g_plugin = NULL;

#ifndef STATIC_LIB
	extern "C" void HlslParserExport DllStartPlugin()
	{
		///@remarks Create plugin.
		g_plugin = new CPluginHlslParser();

		///@remarks Register plugin.
		CPluginManager::Instance().InstallPlugin( g_plugin );
	}

	extern "C" void HlslParserExport DllStopPlugin()
	{
		///@remarks Unregister plugin.
		CPluginManager::Instance().UninstallPlugin( g_plugin );

		///@remarks Delete plugin.
		delete g_plugin;
	}
#endif
}
END_NAMESPACE_HLSL_PARSER
