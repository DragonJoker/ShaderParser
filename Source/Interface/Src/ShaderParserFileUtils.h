/************************************************************************//**
* @file ShaderParserFileUtils.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief File helper functions
*
***************************************************************************/

#ifndef ___SHADER_PARSER_FILE_UTILS_H___
#define ___SHADER_PARSER_FILE_UTILS_H___

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	namespace FileUtils
	{
		/** Opens a file
		*\param[out] p_pFile
			Receives the file descriptor
		*\param[in] p_pszPath
			The file path
		*\param[in] p_pszMode
			The opening mode
		*\return
			true on success
		*/
		ShaderParserExport bool FOpen( FILE *& p_pFile, char const * p_pszPath, char const * p_pszMode );

		/** Checks the file existence
		@param name
			The file name
		@return true if the file exists
		*/
		ShaderParserExport bool FileExists( const String & name );

		/** Checks the folder existence
		@param name
			The folder name
		@return true if the folder exists
		*/
		ShaderParserExport bool FolderExists( String const & p_filename );

		/** Creates a folder
		@param name
			The folder name
		@return true if the folder was correctly created
		*/
		ShaderParserExport bool CreateFolder( String const & pathFolder );
	}
}
END_NAMESPACE_SHADER_PARSER

#endif //___SHADER_PARSER_FILE_UTILS_H___
