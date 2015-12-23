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

#include "ShaderParserPch.h"

#include "ShaderParserFileUtils.h"

#include "ShaderParserStringUtils.h"

#if defined( _WIN32 )
#   include <direct.h>
#endif

#include <boost/filesystem.hpp>

namespace ShaderParser
{
	namespace FileUtils
	{
#if defined( _MSC_VER)

		bool FOpen( FILE *& p_pFile, char const * p_pszPath, char const * p_pszMode )
		{
			return fopen_s( &p_pFile, p_pszPath, p_pszMode ) == 0;
		}

#else

		bool FOpen( FILE *& p_pFile, char const * p_pszPath, char const * p_pszMode )
		{
			p_pFile = fopen( p_pszPath, p_pszMode );
			return p_pFile != NULL;
		}

#endif

		bool FileExists( const String & name )
		{
			bool result = false;
			struct stat buffer;
			std::string strname = name;

			if ( stat( strname.c_str(), &buffer ) == 0 )
			{
				result = true;
			}

			return result;
		}

		bool CreateFolder( String const & pathFolder )
		{
			bool bReturn = false;

			if ( !pathFolder.empty() )
			{
				String pathParentFolder = pathFolder.substr( 0, pathFolder.find_last_of( PATH_SEP[0] ) );
				bReturn = FileUtils::FolderExists( pathParentFolder );

				if ( !bReturn )
				{
					bReturn = CreateFolder( pathParentFolder );
				}

				if ( bReturn )
				{
#if defined( _MSC_VER )

					bReturn = _mkdir( pathFolder.c_str() ) == 0;

#else

					bReturn = mkdir( pathFolder.c_str(), 777 ) == 0;

#endif
				}
			}

			return bReturn;
		}

		bool FolderExists( String const & p_filename )
		{
			try
			{
				return boost::filesystem::exists( p_filename ) && boost::filesystem::is_directory( p_filename );
			}
			catch ( std::exception & )
			{
				return false;
			}
		}
	}
}
