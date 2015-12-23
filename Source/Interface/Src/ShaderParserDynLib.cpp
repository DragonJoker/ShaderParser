/************************************************************************//**
* @file DynLib.cpp
* @author spastor
* @version 1.0
* @date 11/23/2015
*
*
* @brief Dynamic library class.
*
* @details Resource holding data about a dynamic library.
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderParserDynLib.h"

#include "ShaderParserStringUtils.h"
#include "ShaderParserException.h"
#include "ShaderParserFileUtils.h"

#include <sys/stat.h>

#if defined( _WIN32 )
#	include <Windows.h>
#	define DYNLIB_LOAD( a ) ::LoadLibraryExA( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#	define DYNLIB_GETSYM( a, b ) ::GetProcAddress( a, b )
#	define DYNLIB_UNLOAD( a ) !::FreeLibrary( a )
#elif defined( __linux__ )
#	include <dlfcn.h>
#	define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL )
#	define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#	define DYNLIB_UNLOAD( a ) dlclose( a )
#endif

namespace ShaderParser
{
	//!@remarks Static members
#	if defined( _WIN32 )
	const String   CDynLib::LIB_EXTENSION( STR( ".dll" ) );
#	elif defined( __linux__ )
	const String   CDynLib::LIB_EXTENSION( STR( ".so" ) );
#	endif

	const String ERROR_DB_TEXT_DYNAMIC_LIB_SYSTEM = STR( "System Error: " );
	const String ERROR_DB_LIB_FILE_NOT_FOUND = STR( "File %s not found!" );
	const String ERROR_DB_LOAD_DYNAMIC_LIB = STR( "Could not load dynamic library %s." );
	const String ERROR_DB_UNLOAD_DYNAMIC_LIB = STR( "Could not unload dynamic library %s." );

	namespace
	{
		bool FindFile( const String & name, const String & extension, String & file )
		{
			bool result = false;

			if ( FileUtils::FileExists( name ) )
			{
				result = true;
				file = name;
			}
			else if ( FileUtils::FileExists( name + extension ) )
			{
				result = true;
				file = name + extension;
			}

			return result;
		}
	}

	CDynLib::CDynLib( const String & name )
		: m_name( name )
		, m_handle( NULL )
	{
	}

	CDynLib::~CDynLib()
	{
	}

	void CDynLib::Load()
	{
		String l_name = m_name;

		//!@remarks Check if file exists.
		if ( FindFile( m_name, LIB_EXTENSION, l_name ) == false )
		{
			PARSER_EXCEPT( EShaderParserExceptionCodes_ItemNotFound, ( Format( ERROR_DB_LIB_FILE_NOT_FOUND ) % l_name ).str() );
		}

		//!@remarks Update name with the complete library path.
		m_name = l_name;

		//!@remarks Load library.
		m_handle = ( DYNLIB_HANDLE )DYNLIB_LOAD( m_name.c_str() );

		if ( !m_handle )
		{
			StringStream l_stream;
			l_stream << ( Format( ERROR_DB_LOAD_DYNAMIC_LIB ) % m_name ).str() << ERROR_DB_TEXT_DYNAMIC_LIB_SYSTEM << DynlibError();
			PARSER_EXCEPT( EShaderParserExceptionCodes_InternalError, l_stream.str() );
		}
	}

	void CDynLib::Unload()
	{
		//CLogManager::Get().LogInfo( "Unloading library " + _name );

		if ( DYNLIB_UNLOAD( m_handle ) )
		{
			StringStream l_stream;
			l_stream << ( Format( ERROR_DB_UNLOAD_DYNAMIC_LIB ) % m_name ).str() << ERROR_DB_TEXT_DYNAMIC_LIB_SYSTEM << DynlibError();
			PARSER_EXCEPT( EShaderParserExceptionCodes_InternalError, l_stream.str() );
		}
	}

	void * CDynLib::GetSymbol( const String & strName ) const throw()
	{
		//!@remarks GetProcAddress doesn't have unicode version. Always use ANSI string.
		return ( void * )DYNLIB_GETSYM( m_handle, strName.c_str() );
	}

	String CDynLib::DynlibError()
	{
		String l_result;

#	if defined( _WIN32 )

		LPVOID l_msgBuf = NULL;
		String l_errorDescription;
		DWORD l_error = ::GetLastError();

		//!@remarks Format a message string
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, // source and processing options
			NULL,                                                                                        // pointer to message source
			l_error,                                                                                     // requested message identifier
			MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),                                                 // Default language
			reinterpret_cast< LPSTR >( &l_msgBuf ),                                                     // pointer to message buffer
			0,                                                                                           // maximum size of message buffer
			NULL );                                                                                      // address of array of message inserts

		if ( l_msgBuf )
		{
			l_errorDescription = reinterpret_cast< LPSTR >( l_msgBuf );
			LocalFree( l_msgBuf );
		}

		l_result = l_errorDescription;

#	elif defined( __linux__ )

		l_result = dlerror();

#	endif

		return l_result;
	}
}
