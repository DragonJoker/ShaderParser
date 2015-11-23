/************************************************************************//**
* @file DynLib.h
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

#ifndef ___SHADER_PARSER_DYNAMIC_LIBRARY_H___
#define ___SHADER_PARSER_DYNAMIC_LIBRARY_H___

#include "ShaderParserPrerequisites.h"

#if defined( _WIN32 )
#	define DYNLIB_HANDLE hInstance

struct HINSTANCE__;
typedef struct HINSTANCE__ * hInstance;

#elif defined( __linux__ )
#	define DYNLIB_HANDLE void *
#endif

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Resource holding data about a dynamic library.
	@remarks
		This class holds the data required to get symbols from
		libraries loaded at run-time (i.e. from DLL's for so's).
	*/
	class CDynLib
	{
	public:
		/** Default constructor.
		*/
		ShaderParserExport CDynLib( const String & name );

		/** Destructor.
		*/
		ShaderParserExport virtual ~CDynLib();

		/** Load the library.
		*/
		ShaderParserExport void Load();

		/** Unload the library.
		*/
		ShaderParserExport void Unload();

		/** Get the name of the library.
		@return
			Return the library name.
		*/
		inline const String & GetName() const
		{
			return m_name;
		}

		/** Return the address of the given symbol from the loaded library.
		@param
			strName The name of the symbol to search for.
		@return
			If the function succeeds, the returned value is a handle to the symbol.
		@par
			If the function fails, the returned value is <b>NULL</b>.
		*/
		ShaderParserExport void * GetSymbol( const String & strName ) const throw();

		/** File extension used for plugin files (platform specific)
		*/
		static const String LIB_EXTENSION;

	protected:
		/** Get the last loading error.
		*/
		String DynlibError();

		//! Library name.
		String m_name;
		//! Handle to the loaded library.
		DYNLIB_HANDLE m_handle;
	};
}
END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_DYNAMIC_LIBRARY_H___
