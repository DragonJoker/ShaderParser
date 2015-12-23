/************************************************************************//**
* @file ShaderParserLoggerImpl.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief CLoggerImpl class
*
* @details Helper class for Logger, used to share one instance across multiple DLLs
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderParserLoggerImpl.h"

#include "ShaderParserLoggerConsole.h"
#include "ShaderParserLogger.h"
#include "ShaderParserStringUtils.h"
#include "ShaderParserFileUtils.h"

namespace ShaderParser
{
	class CLoggerImpl;

	CLoggerImpl::CLoggerImpl()
	{
#if defined( NDEBUG )
		_console = std::make_unique< CDefaultConsole >();
#else
		_console = std::make_unique< CDebugConsole >();
#endif
	}

	CLoggerImpl::~CLoggerImpl()
	{
		_console.reset();
	}

	void CLoggerImpl::Initialise( CLogger const & logger )
	{
		for ( int i = 0; i < ELogType_COUNT; i++ )
		{
			_headers[i] = logger._headers[i];
		}
	}

	void CLoggerImpl::Cleanup()
	{
	}

	void CLoggerImpl::SetFileName( String const & logFilePath, ELogType logLevel )
	{
		if ( logLevel == ELogType_COUNT )
		{
			for ( auto & path : _logFilePath )
			{
				path = logFilePath;
			}
		}
		else
		{
			_logFilePath[logLevel] = logFilePath;
		}

		FILE * file;
		FileUtils::FOpen( file, logFilePath.c_str(), "w" );

		if ( file )
		{
			fclose( file );
		}
	}

	void CLoggerImpl::PrintMessage( ELogType logLevel, std::string const & message )
	{
		DoPrintMessage( logLevel, message );
	}

	void CLoggerImpl::PrintMessage( ELogType logLevel, std::wstring const & message )
	{
		DoPrintMessage( logLevel, StringUtils::ToStr( message ) );
	}

	void CLoggerImpl::LogMessageQueue( MessageQueue const & p_queue, bool display )
	{
		static const String LOG_TIMESTAMP = STR( "%Y-%m-%d %H:%M:%S" );
		std::tm l_dtToday = { 0 };
		time_t l_tTime;
		time( &l_tTime );
		l_dtToday = *localtime( &l_tTime );
		char l_buffer[33] = { 0 };
		strftime( l_buffer, 32, LOG_TIMESTAMP.c_str(), &l_dtToday );
		String l_timeStamp( l_buffer );

		FILE * logFiles[ELogType_COUNT] = { NULL };
		std::map< String, FILE * > opened;

		try
		{
			for ( auto && message : p_queue )
			{
				FILE * file = logFiles[message->m_type];

				if ( !file )
				{
					auto && l_it = opened.find( _logFilePath[message->m_type] );

					if ( l_it == opened.end() )
					{
						FileUtils::FOpen( file, _logFilePath[message->m_type].c_str(), "a" );

						if ( file )
						{
							opened.insert( std::make_pair( _logFilePath[message->m_type], file ) );
						}
					}
					else
					{
						file = l_it->second;
					}

					logFiles[message->m_type] = file;
				}

				if ( file )
				{
					String toLog = message->GetMessage();

					if ( toLog.find( STR( '\n' ) ) != String::npos )
					{
						StringArray array = StringUtils::Split( toLog, STR( "\n" ), uint32_t( std::count( toLog.begin(), toLog.end(), STR( '\n' ) ) + 1 ) );

						for ( auto && line : array )
						{
							DoLogLine( l_timeStamp, line, file, message->m_type, display );
						}
					}
					else
					{
						DoLogLine( l_timeStamp, toLog, file, message->m_type, display );
					}
				}
			}

			for ( auto && it : opened )
			{
				fclose( it.second );
			}

			opened.clear();
		}
		catch ( std::exception & )
		{
			//m_pConsole->Print( STR( "Couldn't open log file : " ) + String( exc.what() ), true );
		}
	}

	void CLoggerImpl::DoPrintMessage( ELogType logLevel, String const & message )
	{
		if ( message.find( STR( '\n' ) ) != String::npos )
		{
			StringArray array = StringUtils::Split( message, STR( "\n" ), uint32_t( std::count( message.begin(), message.end(), STR( '\n' ) ) + 1 ) );

			for ( auto && line : array )
			{
				DoPrintLine( line, logLevel );
			}
		}
		else
		{
			DoPrintLine( message, logLevel );
		}
	}

	void CLoggerImpl::DoPrintLine( String const & line, ELogType logLevel )
	{
		_console->BeginLog( logLevel );
		_console->Print( line, true );
	}

	void CLoggerImpl::DoLogLine( String const & timestamp, String const & line, FILE * logFile, ELogType logLevel, bool display )
	{
#if defined( NDEBUG )

		if ( display )
		{
			DoPrintLine( line, logLevel );
		}

#endif

		if ( logFile )
		{
			std::string logLine = timestamp + STR( " - " ) + _headers[logLevel] + line;
			fwrite( logLine.c_str(), 1, logLine.size(), logFile );
			fwrite( "\n", 1, 1, logFile );
		}
	}
}
