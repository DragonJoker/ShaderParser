/************************************************************************//**
 * @file ShaderParserTestUtils.cpp
 * @author Sylvain Doremus
 * @version 1.0
 * @date 11/23/2015
 *
 *
 * @brief Utils for ShaderParser tests.
 *
 * @details Utils for ShaderParser tests.
 *
 ***************************************************************************/

#include "ShaderParserTestPch.h"

#include "ShaderParserTestUtils.h"

#include "ShaderParserTestUtilities.h"

#include <ShaderParserFileUtils.h>
#include <ShaderParserException.h>

#if defined( _WIN32 )
#   include <windows.h>
#   include <process.h>
#else
#   include <unistd.h>
#   include <sys/wait.h>
#endif

BEGIN_NAMESPACE_SHADER_PARSER_TEST
{
	namespace
	{
		const String ERROR_UNABLE_TO_SPAWN_PROCESS      = STR( "Unable to spawn the process in asynchronous mode! System Error: " );
		const String ERROR_UNABLE_TO_FORK_CHILD_PROCESS = STR( "Unable to fork a child process in asynchronous mode! System Error: " );
#if defined( _WIN32 )
		typedef PROCESS_INFORMATION spawn_pid_t;
		const DWORD INVALID_ID = 0xFFFFFFFF;
		static const PROCESS_INFORMATION INVALID_PROCESS_ID = { INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_ID, INVALID_ID };
#else
		typedef pid_t spawn_pid_t;
		static const pid_t INVALID_PROCESS_ID = -1;
#endif
		/** Executes a script with a single argument in a CProcess.
		@param path
		    Directory path to the script.
		@param script
		    Name of the script to execute.
		@param argument
		    Argument of the script.
		@return
		    Exit code of the CProcess executing the batch file.
		*/
		int ExecuteScript( const String & path, const String & script, const StringArray & arguments )
		{
			// Command path
			StringStream commandStream;
			commandStream << path << PATH_SEP << script;
			std::string commandString = commandStream.str();

			// Execute
			spawn_pid_t processId = INVALID_PROCESS_ID;

			if ( !FileUtils::FileExists( commandString ) )
			{
				StringStream ss;
				ss << ERROR_UNABLE_TO_SPAWN_PROCESS << STR( "File does not exist\n" );
				PARSER_EXCEPT( EShaderParserExceptionCodes_InternalError, ss.str() );
			}

#if defined( _WIN32 )

			String commandLine = STR( "\"" ) + commandString + STR( "\"" );
			String sep;

			for ( auto && argument : arguments )
			{
				commandLine += STR( " " ) + argument;
			}

			TChar * szCommandLine = new TChar[commandLine.size() + 1];
			memset( szCommandLine, 0, commandLine.size() + 1 );
			strcpy_s( szCommandLine, commandLine.size() + 1, commandLine.c_str() );

			//!@remarks Create and execute a new process.
			STARTUPINFOA si = { 0 };
			BOOL result = ::CreateProcessA( NULL,
											szCommandLine,
											NULL,
											NULL,
											FALSE,
											0,
											NULL,
											NULL,
											&si,
											&processId );

			delete [] szCommandLine;
			szCommandLine = NULL;

			if ( !result )
			{
				TChar szBuffer[1000];
				::GetCurrentDirectoryA( 1000, szBuffer );
				StringStream ss;
				ss << ERROR_UNABLE_TO_SPAWN_PROCESS << ::GetLastError() << "\nWorking directory : " << szBuffer << STR( "\n" );
				PARSER_EXCEPT( EShaderParserExceptionCodes_InternalError, ss.str() );
			}

			int nChildResult = 0;
			::WaitForSingleObject( processId.hProcess, INFINITE );
			DWORD code;
			::GetExitCodeProcess( processId.hProcess, &code );
			::CloseHandle( processId.hThread );
			::CloseHandle( processId.hProcess );
			nChildResult = int( code );

#else

			// Command arguments
			std::vector< const char * > args;
			args.push_back( commandString.c_str() );

			for ( auto && argument : arguments )
			{
				args.push_back( argument.c_str() );
			}

			//!@remarks Create new process.
			processId = vfork();

			if ( !processId )
			{
				//!@remarks Execute child process.
				execv( commandString.c_str(), const_cast< char * const * >( args.data() ) );
				exit( 0 );
			}
			else
			{
				//!@remarks Parent process
				if ( processId == -1 )
				{
					StringStream ss;
					ss << ERROR_UNABLE_TO_FORK_CHILD_PROCESS;
					PARSER_EXCEPT( EShaderParserExceptionCodes_InternalError, ss.str() );
				}
			}

			int nChildResult = 0;
			waitpid( processId, &nChildResult, 0 );

			if ( WIFEXITED( nChildResult ) )
			{
				nChildResult = WEXITSTATUS( nChildResult );
			}
			else
			{
				nChildResult = -1;
			}

#endif
			return nChildResult;
		}
	}

#if defined( WIN32 )
	static const String SCRIPT_EXT = STR( ".bat" );
#else
	static const String SCRIPT_EXT = STR( ".sh" );
#endif

	static const String GLSL = STR( "GLSL" );
	static const String HLSL = STR( "HLSL" );
}
END_NAMESPACE_SHADER_PARSER_TEST
