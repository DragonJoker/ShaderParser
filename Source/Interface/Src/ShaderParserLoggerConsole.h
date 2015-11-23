/************************************************************************//**
* @file ShaderParserLoggerConsole.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
* @brief IConsoleInfo interface
*
* @details Console info class, platform dependant
*
***************************************************************************/

#ifndef ___SHADER_PARSER_CONSOLE_H___
#define ___SHADER_PARSER_CONSOLE_H___

#include "ShaderParserPrerequisites.h"

#include "ELogType.h"

#pragma warning( push )
#pragma warning( disable:4290 )

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Console info class, Platform dependent
	*/
	class IConsole
	{
	public:
		/** Constructor
		*/
		IConsole()
		{
		}

		/** Destructor
		*/
		virtual ~IConsole()
		{
		}

		/** Configures console info for the given log type
		@param[in] logLevel
		 	The log level
		*/
		virtual void BeginLog( ELogType logLevel ) = 0;

		/** Prints a text in the console, adds the line end character if asked
		@param[in] toLog
			The text to log
		@param[in] newLine
		 	Tells if the line end character must be added
		*/
		virtual void Print( String const & toLog, bool newLine ) = 0;
	};

	/* Console base class
	*/
	class CProgramConsole
	{
	public:
		/** Constructor
		*/
		CProgramConsole()
		{
		}

		/** Destructor
		*/
		virtual ~CProgramConsole()
		{
		}

		/** Configures console info for the given log type
		@param[in] logLevel
			The log type
		*/
		virtual void BeginLog( ELogType logLevel ) = 0;

		/** Prints a text in the console, adds the line end character if asked
		@param[in] toLog
			The text to log
		@param[in] newLine
			Tells if the line end character must be added
		*/
		virtual void Print( String const & toLog, bool newLine ) = 0;

	protected:
		//! The console
		std::unique_ptr< IConsole > _console;
	};

	/* Traditional consol class
	*/
	class CDefaultConsole
		: public CProgramConsole
	{
	public:
		/** Constructor
		*/
		CDefaultConsole();

		/** Destructor
		*/
		virtual ~CDefaultConsole();

		/** @copydoc ShaderParser::CProgramConsole::BeginLog
		*/
		virtual void BeginLog( ELogType logLevel );

		/** @copydoc ShaderParser::CProgramConsole::Print
		*/
		virtual void Print( String const & toLog, bool newLine );
	};

	/** Debug console class, adds colour on MSW
	*/
	class CDebugConsole
		: public CProgramConsole
	{
	public:
		/** Constructor
		*/
		CDebugConsole();

		/** Destructor
		*/
		virtual ~CDebugConsole();

		/** @copydoc ShaderParser::CProgramConsole::BeginLog
		*/
		virtual void BeginLog( ELogType logLevel );

		/** @copydoc ShaderParser::CProgramConsole::Print
		*/
		virtual void Print( String const & toLog, bool newLine );
	};
}
END_NAMESPACE_SHADER_PARSER

#pragma warning( pop)

#endif
