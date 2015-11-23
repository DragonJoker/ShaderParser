/************************************************************************//**
* @file GlslParserPch.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief GLSL parser precompiled header.
*
* @details This file generates the GLSL parser precompiled headers.
*
***************************************************************************/

#ifndef ___GLSL_PARSER_PCH_H___
#define ___GLSL_PARSER_PCH_H___

// Stable headers wich will be used for precompilation if the compiler
// supports it. Add entries here when headers are unlikely to change.
// NB: a change to any of these headers will result in a full rebuild,
// so don't add things to this lightly.
#include <ShaderParserPrerequisites.h>
#include <ShaderParserException.h>
#include <ShaderParserFactory.h>
#include <ShaderParserPlugin.h>
#include <ShaderParserPluginManager.h>
#include <ShaderParserLogger.h>
#include <ShaderParserStringUtils.h>

#if defined( _WIN32 )
#	include <Windows.h>
#	undef min
#	undef max
#	undef abs
#endif

#include "GlslParserPrerequisites.h"

#endif // ___GLSL_PARSER_PCH_H___
