/************************************************************************//**
* @file DynLibManager.h
* @author spastor
* @version 1.0
* @date 11/23/2015
*
*
* @brief Manager for Dynamic-loading Libraries.
*
* @details Manager for Dynamic-loading Libraries.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_DYNAMIC_LIBRARY_MANAGER_H___
#define ___SHADER_PARSER_DYNAMIC_LIBRARY_MANAGER_H___

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Manager for Dynamic-loading Libraries.
	@remarks
		This manager keeps a track of all the open dynamic-loading libraries,
		opens them and returns references to already-open libraries.
	*/
	class CDynLibManager
	{
	public:
		/** Load the passed library.
		@param filename
			The name of the library.
			The extension can be omitted.
		*/
		ShaderParserExport DynLibSPtr Load( const String & filename );

		/** Unload the passed library.
		@param dynLib
			Library to unload.
		*/
		ShaderParserExport void Unload( CDynLib & dynLib );

		/** Retrieves the unique instance
		*/
		ShaderParserExport static CDynLibManager & Instance()
		{
			static CDynLibManager singleton;
			return singleton;
		}

	protected:
		/** Default constructor.
		@note
			Should never be called as the singleton is automatically
			created during the creation of application.
		*/
		ShaderParserExport CDynLibManager();

		/** Destructor.
		*/
		ShaderParserExport virtual ~CDynLibManager();

	protected:
		//!< Map of CDynLib instances registered.
		std::map< String, DynLibSPtr > m_libList;
	};
}
END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_DYNAMIC_LIBRARY_MANAGER_H___
