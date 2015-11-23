/************************************************************************//**
* @file ExceptionShaderParser.h
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

#ifndef ___SHADER_PARSER_EXCEPTION_SHADER_PARSER_H___
#define ___SHADER_PARSER_EXCEPTION_SHADER_PARSER_H___

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Static definitions of database error codes.
	*/
	enum EShaderParserExceptionCodes
	{
		EShaderParserExceptionCodes_GenericError = 0,
		EShaderParserExceptionCodes_UnknownError,
		EShaderParserExceptionCodes_Unimplemented,
		EShaderParserExceptionCodes_DuplicateItem,
		EShaderParserExceptionCodes_NullPointer,
		EShaderParserExceptionCodes_ItemNotFound,
		EShaderParserExceptionCodes_InternalError,
		EShaderParserExceptionCodes_FormatError,
		EShaderParserExceptionCodes_SystemError,

		EShaderParserExceptionCodes_LastCode //!< Represent the maximum number of exception code. Must be always the last.
	};

	/** Should be thrown when a problem occured in the database interface.
	*/
	class CShaderParserException
		: public std::exception
	{
	public:
		/** Create a exception for the database.
		@param number
			Error code.
		@param description
			Error description.
		@param source
			Error source function.
		@param file
			Source file name.
		@param line
			Source file line number.
		*/
		ShaderParserExport CShaderParserException( int number, const String & description, const std::string & source, const std::string & file, long line );

		/** Create a exception for the database.
		@param number
			Error code.
		@param description
			Error description.
		@param source
			Error source function.
		@param type
			Error type.
		@param file
			Source file name.
		@param line
			Source file line number.
		*/
		ShaderParserExport CShaderParserException( const String & type, int number, const String & description, const std::string & source, const std::string & file, long line );

		/** Get the error code.
		@return
			Return the error code.
		*/
		ShaderParserExport virtual int GetNumber() const throw()
		{
			return m_number;
		}

		/** Get the error code.
		@return
			Return the error code.
		*/
		ShaderParserExport virtual const String & GetNumberName() const throw();

		/** Get the source function.
		@return
			Return the error source function.
		*/
		ShaderParserExport virtual const String & GetSource() const
		{
			return m_source;
		}

		/** Get the source file name.
		@return
			Return error source file name.
		*/
		ShaderParserExport virtual const String & GetFile() const
		{
			return m_file;
		}

		/** Get the line number.
		@return
			Return error line number.
		*/
		ShaderParserExport virtual long GetLine() const
		{
			return m_line;
		}

		/** Return a string with only the 'description' field of this exception.
			@remarks
				Use GetFullDescriptionton to get a full description of the error including
				line number, error number and what function threw the exception.
		*/
		ShaderParserExport virtual const String & GetDescription() const
		{
			return m_description;
		}

		/** Return a string with the full description of this error.
			@remarks
				The description contains the error number, the description
				supplied by the thrower, what routine threw the exception,
				and will also supply extra platform-specific information if applicable.
		*/
		ShaderParserExport virtual const String & GetFullDescription() const;

		/** Override std::exception::what */
		ShaderParserExport const char * what() const throw();

	private:
		//! The exception number
		int m_number;
		//! The exception description
		String m_description;
		//! The exception source
		String m_source;
		//! Th type name
		String m_typeName;
		//! The source file
		String m_file;
		//! The source line
		long m_line;
		//!< Full String error description.
		mutable String m_fullDesc;
		//!< Full std::string error description.
		mutable std::string m_what;
		//! The stack trace
		std::string m_callstack;
	};

#	define PARSER_EXCEPT( number, description ) throw CShaderParserException( number, description, __FUNCTION__, __FILE__, __LINE__ )
}
END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_EXCEPTION_SHADER_PARSER_H___
