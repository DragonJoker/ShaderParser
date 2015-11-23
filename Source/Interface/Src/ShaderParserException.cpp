/************************************************************************//**
* @file ExceptionShaderParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief CShaderParserException class declaration and definition.
*
* @details Should be thrown when a problem occured in the database interface.
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderParserException.h"
#include "ShaderParserStringUtils.h"
#include "ShaderParserLogger.h"

#if !defined( NDEBUG )
#	if !defined( _WIN32 )
#		include <execinfo.h>
#		include <stdlib.h>
#	else
#		include <Windows.h>
#		pragma warning( disable:4091 )
#		include <Dbghelp.h>
#	endif
#endif

#if !defined( _WIN32 )
#	include <signal.h>
#endif

#if defined( __GNUG__ )
#include <cxxabi.h>
#else
#endif

BEGIN_NAMESPACE_SHADER_PARSER
{
	namespace
	{
#if defined( NDEBUG )

		static void ShowBacktrace( std::stringstream & p_stream )
		{
		}

#else
	const int CALLS_TO_CAPTURE( 20 );
	const int CALLS_TO_SKIP( 2 );

#	if defined( __GNUG__ )

	std::string Demangle( const std::string & p_mangled )
	{
		std::string l_return( p_mangled );
		std::string sub;
		size_t l_lindex = p_mangled.find( "(" );
		size_t l_rindex = p_mangled.find( "+" );

		if ( l_lindex != std::string::npos && l_rindex != std::string::npos )
		{
			l_return = p_mangled.substr( l_lindex + 1, l_rindex - 1 - l_lindex );
		}

		int l_status = 0;
		auto l_demangled = abi::__cxa_demangle( l_return.c_str(), 0, 0, &l_status );

		if ( !l_status )
		{
			l_return = p_mangled.substr( 0, l_lindex + 1 ) + l_demangled + p_mangled.substr( l_rindex );
		}
		else
		{
			l_return = p_mangled;
		}

		return l_return;
	}

#	elif defined( _MSC_VER )

	std::string Demangle( const std::string & p_mangled )
	{
		char l_demangled[1024] = { 0 };
		std::string l_return;

		if ( UnDecorateSymbolName( p_mangled.c_str(), l_demangled, sizeof( l_demangled ), UNDNAME_COMPLETE ) )
		{
			l_return = l_demangled;
		}
		else
		{
			l_return = p_mangled;
		}

		return l_return;
	}

#	else

	std::string Demangle( const std::string & name )
	{
		return name;
	}

#	endif
#	if !defined( _WIN32 )

		void ShowBacktrace( std::stringstream & p_stream )
		{
			p_stream << "CALL STACK:" << std::endl;
			void * backTrace[CALLS_TO_CAPTURE];
			unsigned int num( ::backtrace( backTrace, CALLS_TO_CAPTURE ) );
			char ** fnStrings( ::backtrace_symbols( backTrace, num ) );

			for ( unsigned i = CALLS_TO_SKIP; i < num; ++i )
			{
				p_stream << "== " << Demangle( fnStrings[i] ) << std::endl;
			}

			free( fnStrings );
		}

#	else

		void ShowBacktrace( std::stringstream & p_stream )
		{
			static bool SymbolsInitialised = false;
			const int MaxFnNameLen( 255 );

			void * backTrace[CALLS_TO_CAPTURE - CALLS_TO_SKIP];
			unsigned int num( ::CaptureStackBackTrace( CALLS_TO_SKIP, CALLS_TO_CAPTURE - CALLS_TO_SKIP, backTrace, NULL ) );

			::HANDLE process( ::GetCurrentProcess() );
			p_stream << "CALL STACK:" << std::endl;

			// symbol->Name type is char [1] so there is space for \0 already
			SYMBOL_INFO * symbol( ( SYMBOL_INFO * ) malloc( sizeof( SYMBOL_INFO ) + ( MaxFnNameLen * sizeof( char ) ) ) );
			symbol->MaxNameLen = MaxFnNameLen;
			symbol->SizeOfStruct = sizeof( SYMBOL_INFO );

			if ( !SymbolsInitialised )
			{
				SymbolsInitialised = SymInitialize( process, NULL, TRUE ) == TRUE;
			}

			if ( SymbolsInitialised )
			{
				// For now we just print out a message on sterr.
				for ( unsigned int i = 0; i < num; ++i )
				{
					if ( SymFromAddr( process, reinterpret_cast< DWORD64 >( backTrace[i] ), 0, symbol ) )
					{
						p_stream << "== " << std::string( symbol->Name, symbol->Name + symbol->NameLen ) << std::endl;
					}
				}

				free( symbol );
			}
			else
			{
				p_stream << "== Unable to retrieve the call stack" << std::endl;
			}
		}

#	endif
#endif

	}

	static const String ERROR_DB_SYSTEM = STR( "System error: " );

#if defined( _WIN32 )
	static const String ERROR_DB_ACCESS_VIOLATION = STR( "The thread tried to read from or write to a virtual address for which it does not have the appropriate access." );
	static const String ERROR_DB_ARRAY_BOUNDS_EXCEEDED = STR( "The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking." );
	static const String ERROR_DB_BREAKPOINT = STR( "A breakpoint was encountered." );
	static const String ERROR_DB_DATATYPE_MISALIGNMENT = STR( "The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on." );
	static const String ERROR_DB_FLT_DENORMAL_OPERAND = STR( "One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value." );
	static const String ERROR_DB_FLT_DIVIDE_BY_ZERO = STR( "The thread tried to divide a floating-point value by a floating-point divisor of zero." );
	static const String ERROR_DB_FLT_INEXACT_RESULT = STR( "The result of a floating-point operation cannot be represented exactly as a decimal fraction." );
	static const String ERROR_DB_FLT_INVALID_OPERATION = STR( "This exception represents any floating-point exception not included in this list." );
	static const String ERROR_DB_FLT_OVERFLOW = STR( "The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type." );
	static const String ERROR_DB_FLT_STACK_CHECK = STR( "The stack overflowed or underflowed as the result of a floating-point operation." );
	static const String ERROR_DB_FLT_UNDERFLOW = STR( "The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type." );
	static const String ERROR_DB_ILLEGAL_INSTRUCTION = STR( "The thread tried to execute an invalid instruction." );
	static const String ERROR_DB_IN_PAGE_ERROR = STR( "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network." );
	static const String ERROR_DB_INT_DIVIDE_BY_ZERO = STR( "The thread tried to divide an integer value by an integer divisor of zero." );
	static const String ERROR_DB_INT_OVERFLOW = STR( "The result of an integer operation caused a carry out of the most significant bit of the result." );
	static const String ERROR_DB_INVALID_DISPOSITION = STR( "An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception." );
	static const String ERROR_DB_NONCONTINUABLE_EXCEPTION = STR( "The thread tried to continue execution after a noncontinuable exception occurred." );
	static const String ERROR_DB_PRIV_INSTRUCTION = STR( "The thread tried to execute an instruction whose operation is not allowed in the current machine mode." );
	static const String ERROR_DB_SINGLE_STEP = STR( "A trace trap or other single-instruction mechanism signaled that one instruction has been executed." );
	static const String ERROR_DB_STACK_OVERFLOW = STR( "The thread used up its stack." );
	static const String ERROR_DB_READ_ATTEMPT = STR( "The thread attempted to read the inaccessible data at address 0x" );
	static const String ERROR_DB_WRITE_ATTEMPT = STR( "The thread attempted to write to an inaccessible address 0x" );
	static const String ERROR_DB_DEP_VIOLATION = STR( "The thread causes a user-mode data execution prevention (DEP) violation at address 0x" );

	void OsToShaderParserException( unsigned int code, EXCEPTION_POINTERS * pointers )
	{
		StringStream error;
		std::hex( error );
		error << ERROR_DB_SYSTEM << STR( "(0x" ) << code << STR( ") " );
		bool continuable = false;

		if ( pointers )
		{
			if ( pointers->ExceptionRecord )
			{
				switch ( pointers->ExceptionRecord->ExceptionCode )
				{
				case EXCEPTION_ACCESS_VIOLATION:
					error << ERROR_DB_ACCESS_VIOLATION << std::endl;

					if ( pointers->ExceptionRecord->NumberParameters >= 2 )
					{
						switch ( *pointers->ExceptionRecord->ExceptionInformation )
						{
						case 0:
							error << ERROR_DB_READ_ATTEMPT;
							break;

						case 1:
							error << ERROR_DB_WRITE_ATTEMPT;
							break;

						case 8:
							error << ERROR_DB_DEP_VIOLATION;
							break;

						default:
							break;
						}

						std::hex( error );
						error << *( pointers->ExceptionRecord->ExceptionInformation + 1 );
					}

					break;

				case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
					error << ERROR_DB_ARRAY_BOUNDS_EXCEEDED << std::endl;
					break;

				case EXCEPTION_BREAKPOINT:
					error << ERROR_DB_BREAKPOINT;
					break;

				case EXCEPTION_DATATYPE_MISALIGNMENT:
					error << ERROR_DB_DATATYPE_MISALIGNMENT << std::endl;
					break;

				case EXCEPTION_FLT_DENORMAL_OPERAND:
					error << ERROR_DB_FLT_DENORMAL_OPERAND << std::endl;
					break;

				case EXCEPTION_FLT_DIVIDE_BY_ZERO:
					error << ERROR_DB_FLT_DIVIDE_BY_ZERO << std::endl;
					break;

				case EXCEPTION_FLT_INEXACT_RESULT:
					error << ERROR_DB_FLT_INEXACT_RESULT << std::endl;
					break;

				case EXCEPTION_FLT_INVALID_OPERATION:
					error << ERROR_DB_FLT_INVALID_OPERATION << std::endl;
					break;

				case EXCEPTION_FLT_OVERFLOW:
					error << ERROR_DB_FLT_OVERFLOW << std::endl;
					break;

				case EXCEPTION_FLT_STACK_CHECK:
					error << ERROR_DB_FLT_STACK_CHECK << std::endl;
					break;

				case EXCEPTION_FLT_UNDERFLOW:
					error << ERROR_DB_FLT_UNDERFLOW << std::endl;
					break;

				case EXCEPTION_ILLEGAL_INSTRUCTION:
					error << ERROR_DB_ILLEGAL_INSTRUCTION << std::endl;
					break;

				case EXCEPTION_IN_PAGE_ERROR:
					error << ERROR_DB_IN_PAGE_ERROR << std::endl;

					if ( pointers->ExceptionRecord->NumberParameters >= 3 )
					{
						switch ( *pointers->ExceptionRecord->ExceptionInformation )
						{
						case 0:
							error << ERROR_DB_READ_ATTEMPT;
							break;

						case 1:
							error << ERROR_DB_WRITE_ATTEMPT;
							break;

						case 8:
							error << ERROR_DB_DEP_VIOLATION;
							break;

						default:
							break;
						}

						std::hex( error );
						error << *( pointers->ExceptionRecord->ExceptionInformation + 1 );
					}

					break;

				case EXCEPTION_INT_DIVIDE_BY_ZERO:
					error << ERROR_DB_INT_DIVIDE_BY_ZERO << std::endl;
					break;

				case EXCEPTION_INT_OVERFLOW:
					error << ERROR_DB_INT_OVERFLOW << std::endl;
					break;

				case EXCEPTION_INVALID_DISPOSITION:
					error << ERROR_DB_INVALID_DISPOSITION << std::endl;
					break;

				case EXCEPTION_NONCONTINUABLE_EXCEPTION:
					error << ERROR_DB_NONCONTINUABLE_EXCEPTION << std::endl;
					break;

				case EXCEPTION_PRIV_INSTRUCTION:
					error << ERROR_DB_PRIV_INSTRUCTION << std::endl;
					break;

				case EXCEPTION_SINGLE_STEP:
					error << ERROR_DB_SINGLE_STEP << std::endl;
					break;

				case EXCEPTION_STACK_OVERFLOW:
					error << ERROR_DB_STACK_OVERFLOW << std::endl;
					break;
				}

				if ( pointers->ExceptionRecord->ExceptionFlags == 0 )
				{
					continuable = true;
				}

				std::hex( error );
				error << STR( "At address: 0x" ) << pointers->ExceptionRecord->ExceptionAddress;
			}
		}

		PARSER_EXCEPT( EShaderParserExceptionCodes_SystemError, error.str() );
	}

	class CSehExceptionHandler
		: public CSystemExceptionHandler
	{
	public:
		CSehExceptionHandler()
			: _function( _set_se_translator( OsToShaderParserException ) )
		{
			// Empty
		}

		~CSehExceptionHandler()
		{
			_set_se_translator( _function );
		}

	private:
		_se_translator_function _function;
	};

#else
	static const String ERROR_DB_ACCESS_VIOLATION = STR( "The thread tried to read from or write to a virtual address for which it does not have the appropriate access." );
	static const String ERROR_DB_DIVIDE_BY_ZERO = STR( "The thread tried to divide a value by a divisor of zero." );

	void OsToShaderParserException( int signal )
	{
		StringStream error;
		std::hex( error );
		error << ERROR_DB_SYSTEM << STR( "(0x" ) << signal << STR( ") " );

		switch ( signal )
		{
		case SIGSEGV:
			error << ERROR_DB_ACCESS_VIOLATION << std::endl;
			break;

		case SIGFPE:
			error << ERROR_DB_DIVIDE_BY_ZERO << std::endl;
			break;
		}

		PARSER_EXCEPT( EShaderParserExceptionCodes_SystemError, error.str() );
	}

	typedef void ( *SignalHandlerPointer )( int );

	class CSignalHandler
		: public CSystemExceptionHandler
	{
	public:
		CSignalHandler()
			: _segvfunction( signal( SIGSEGV, OsToShaderParserException ) )
			, _fpefunction( signal( SIGFPE, OsToShaderParserException ) )
		{
			// Empty
		}

		~CSignalHandler()
		{
			signal( SIGSEGV, _segvfunction );
			signal( SIGFPE, _fpefunction );
		}

	private:
		SignalHandlerPointer _segvfunction;
		SignalHandlerPointer _fpefunction;
	};

#endif

	CShaderParserException::CShaderParserException( int number, const String & description, const std::string & source, const std::string & file, long line )
		: m_number( number )
		, m_description( description )
		, m_source( source )
		, m_typeName( STR( "CShaderParserException" ) )
		, m_file( file )
		, m_line( line )
	{
		std::stringstream l_stream;
		ShowBacktrace( l_stream );
		m_callstack = l_stream.str();
	}

	CShaderParserException::CShaderParserException( const String & type, int number, const String & description, const std::string & source, const std::string & file, long line )
		: m_number( number )
		, m_description( description )
		, m_source( source )
		, m_typeName( type )
		, m_file( file )
		, m_line( line )
	{
		std::stringstream l_stream;
		ShowBacktrace( l_stream );
		m_callstack = l_stream.str();
	}

	const String & CShaderParserException::GetNumberName() const throw()
	{
		static String NumberNames[EShaderParserExceptionCodes_LastCode] =
		{
			STR( "Generic" ),
			STR( "Unknown" ),
			STR( "Unimplemented" ),
			STR( "DuplicateItem" ),
			STR( "NullPointer" ),
			STR( "ItemNotFound" ),
			STR( "Internal" ),
			STR( "System" ),
		};

		return NumberNames[m_number];
	}

	const String & CShaderParserException::GetFullDescription() const
	{
		if ( m_fullDesc.empty() )
		{
			StringStream desc;
			desc <<  STR( "SHADER_PARSER EXCEPTION [name: " ) << m_typeName << STR( ", type: " ) << GetNumberName() << STR( "(" ) << m_number << STR( ")]" ) << std::endl;

			if ( !m_source.empty() )
			{
				desc << STR( "FUNCTION: " ) << m_source << std::endl;
			}

			if ( m_line > 0 )
			{
				desc << STR( "FILE: " ) << m_file << STR( " (line " ) << m_line << STR( ")" ) << std::endl;
			}

			desc << STR( "DESCRIPTION: " ) << m_description << std::endl;
			desc << m_callstack;
			m_fullDesc = desc.str();
			m_what = m_fullDesc;
		}

		return m_fullDesc;
	}

	const char * CShaderParserException::what()const throw()
	{
		GetFullDescription();
		return m_what.c_str();
	}
}
END_NAMESPACE_SHADER_PARSER
