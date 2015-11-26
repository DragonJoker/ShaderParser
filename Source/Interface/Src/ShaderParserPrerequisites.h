/************************************************************************//**
* @file ShaderParserPrerequisites.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief ShaderParser prerequisite header.
*
* @details This file contains all ShaderParser prerequisite instructions.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_PREREQUISITES_H___
#define ___SHADER_PARSER_PREREQUISITES_H___

#define BEGIN_NAMESPACE_SHADER_PARSER namespace ShaderParser
#define NAMESPACE_SHADER_PARSER ShaderParser
#define END_NAMESPACE_SHADER_PARSER

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
#include <functional>
#include <deque>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

#include <boost/format.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include "ShaderParserMacros.h"

#if defined( _WIN32 )
#	ifdef ShaderParser_EXPORTS
#		define ShaderParserExport __declspec ( dllexport )
#	else
#		if defined ( __MINGW32__ )
#			define ShaderParserExport
#		else
#			define ShaderParserExport __declspec ( dllimport )
#		endif
#	endif
#else
#   define ShaderParserExport
#endif

/** ShaderParser namespace
*/
namespace ShaderParser
{
	namespace qi = boost::spirit::qi;
	namespace karma = boost::spirit::karma;
	
	using TChar = char;
	using String = std::basic_string< TChar >;
	using StringStream = std::basic_stringstream< TChar >;
	using OutputStream = std::basic_ostream< TChar >;
	using InputStream = std::basic_istream< TChar >;
	using Format = boost::basic_format< TChar >;

	using Rule = qi::rule< String::iterator, qi::space_type >;
	using Grammar = qi::grammar< String::iterator, qi::space_type >;

#	define STR( x ) x
#	define tcout std::cout

#if defined( _WIN32 )
	static const TChar * PATH_SEP = STR( "\\" );
#else
	static const TChar * PATH_SEP = STR( "/" );
#endif

	// Logging related classes
	struct SMessageBase;
	class CLogger;
	class CLoggerImpl;
	class CProgramConsole;

	// Plugin related stuff
	class CDynLib;
	class CDynLibManager;
	class CPluginManager;
	class CFactoryShaderParser;
	class CPluginShaderParser;

	/** Base class holding the system error handler
	*/
	class CSystemExceptionHandler {};

	//
	class CShaderParser;
	class CShaderParserException;

	// Pointers
	DECLARE_SMART_PTR( DynLib );
	DECLARE_SMART_PTR( PluginShaderParser );
	DECLARE_SMART_PTR( ShaderParser );

	// Containers
	using StringArray = std::vector< String >;
	using MessageQueue = std::deque< std::unique_ptr< SMessageBase > >;

	// Factory type constants
	static const String FACTORY_SHADER_PARSER_TYPE = STR( "Factory shader parser" );

	static const String INFO_UNKNOWN_ERROR = STR( "Unknown error" );
}

#define COMMON_CATCH( text )\
		catch ( CShaderParserException & exc )\
		{\
			StringStream stream;\
			stream << text << std::endl;\
			stream << exc.GetFullDescription();\
			CLogger::LogError( stream );\
		}\
		catch ( std::exception & exc )\
		{\
			StringStream stream;\
			stream << text << std::endl;\
			stream << STR( "DESCRIPTION: " ) << exc.what();\
			CLogger::LogError( stream );\
		}\
		catch ( ... )\
		{\
			StringStream stream;\
			stream << text << std::endl;\
			stream << STR( "DESCRIPTION: " ) << INFO_UNKNOWN_ERROR;\
			CLogger::LogError( stream );\
		}

#if !PARSER_HAS_MAKE_UNIQUE
namespace std
{
	template< class T >
	unique_ptr< T > make_unique()
	{
		return unique_ptr< T >( new T );
	}
	template< class T, typename Arg1 >
	unique_ptr< T > make_unique( Arg1 && arg1 )
	{
		return unique_ptr< T >( new T( std::forward< Arg1 >( arg1 ) ) );
	}
	template< class T, typename Arg1, typename Arg2 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2 )
	{
		return unique_ptr< T >( new T( std::forward< Arg1 >( arg1 ), std::forward< Arg2 >( arg2 ) ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3 )
	{
		return unique_ptr< T >( new T( std::forward< Arg1 >( arg1 ), std::forward< Arg2 >( arg2 ), std::forward< Arg3 >( arg3 ) ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4 )
	{
		return unique_ptr< T >( new T( std::forward< Arg1 >( arg1 ), std::forward< Arg2 >( arg2 ), std::forward< Arg3 >( arg3 ), std::forward< Arg4 >( arg4 ) ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4, Arg5 && arg5 )
	{
		return unique_ptr< T >( new T( std::forward< Arg1 >( arg1 ), std::forward< Arg2 >( arg2 ), std::forward< Arg3 >( arg3 ), std::forward< Arg4 >( arg4 ), std::forward< Arg5 >( arg5 ) ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4, Arg5 && arg5, Arg6 && arg6 )
	{
		return unique_ptr< T >( new T( std::forward< Arg1 >( arg1 ), std::forward< Arg2 >( arg2 ), std::forward< Arg3 >( arg3 ), std::forward< Arg4 >( arg4 ), std::forward< Arg5 >( arg5 ), std::forward< Arg6 >( arg6 ) ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4, Arg5 && arg5, Arg6 && arg6, Arg7 && arg7 )
	{
		return unique_ptr< T >( new T( std::forward< Arg1 >( arg1 ), std::forward< Arg2 >( arg2 ), std::forward< Arg3 >( arg3 ), std::forward< Arg4 >( arg4 ), std::forward< Arg5 >( arg5 ), std::forward< Arg6 >( arg6 ), std::forward< Arg7 >( arg7 ) ) );
	}
	template< class T, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8 >
	unique_ptr< T > make_unique( Arg1 && arg1, Arg2 && arg2, Arg3 && arg3, Arg4 && arg4, Arg5 && arg5, Arg6 && arg6, Arg7 && arg7, Arg8 && arg8 )
	{
		return unique_ptr< T >( new T( std::forward< Arg1 >( arg1 ), std::forward< Arg2 >( arg2 ), std::forward< Arg3 >( arg3 ), std::forward< Arg4 >( arg4 ), std::forward< Arg5 >( arg5 ), std::forward< Arg6 >( arg6 ), std::forward< Arg7 >( arg7 ), std::forward< Arg8 >( arg8 ) ) );
	}
}
#endif

#endif // ___SHADER_PARSER_PREREQUISITES_H___
