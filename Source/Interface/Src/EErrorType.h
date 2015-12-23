/************************************************************************//**
* @file ErrorType.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief EErrorType enumeration declaration.
*
* @details Enumeration of supported error types.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_ERROR_TYPE_H___
#define ___SHADER_PARSER_ERROR_TYPE_H___

#include "ShaderParserPrerequisites.h"

namespace ShaderParser
{
	/** Enumeration of supported error types.
	*/
	typedef enum EErrorType
	{
		EErrorType_NONE,        //!< No error.
		EErrorType_RETRY,       //!< Retry current action.
		EErrorType_ERROR,       //!< True error.
		EErrorType_RECONNECT    //!< Reconnection request.
	}	EErrorType;
}

#endif // ___SHADER_PARSER_ERROR_TYPE_H___
