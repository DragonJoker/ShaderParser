/************************************************************************//**
* @file DllPluginGlslParser.cpp
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

#include "GlslParserPch.h"

#include "GlslParserPlugin.h"

#include <ShaderParserPluginManager.h>

using namespace ShaderParser;

#if defined( _WIN32 ) && !defined ( __MINGW32__ ) && !defined ( STATIC_LIB )
#	ifdef GlslParser_EXPORTS
#		define GlslParserExport __declspec ( dllexport )
#	else
#		if defined ( __MINGW32__ )
#			define GlslParserExport
#		else
#			define GlslParserExport __declspec ( dllimport )
#		endif
#	endif
#else
#    define GlslParserExport
#endif

namespace GlslParser
{
	CPluginGlslParser * g_plugin = NULL;

#ifndef STATIC_LIB
	extern "C" void GlslParserExport DllStartPlugin()
	{
		///@remarks Create plugin.
		g_plugin = new CPluginGlslParser();

		///@remarks Register plugin.
		CPluginManager::Instance().InstallPlugin( g_plugin );
	}

	extern "C" void GlslParserExport DllStopPlugin()
	{
		///@remarks Unregister plugin.
		CPluginManager::Instance().UninstallPlugin( g_plugin );

		///@remarks Delete plugin.
		delete g_plugin;
	}
#endif
}
