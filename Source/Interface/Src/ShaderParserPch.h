/************************************************************************//**
* @file ShaderParserPch.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief ShaderParser precompiled header
*
* @details This file generates the ShaderParser precompiled headers
*
***************************************************************************/

#ifndef ___SHADER_PARSER_PCH_H___
#define ___SHADER_PARSER_PCH_H___

#include <string>
#include <vector>
#include <map>
#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream>
#include <sstream>
#include <locale>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

#include <wchar.h>
#include <sys/stat.h>

#if defined( _WIN32 )
#	include <Windows.h>
#	undef min
#	undef max
#	undef abs
#endif

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/locale.hpp>
#include <boost/format.hpp>

#endif // ___SHADER_PARSER_PCH_H___
