/************************************************************************//**
* @file ELogType.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief ELogType enumerator
*
* @details Defines the various log types
*
***************************************************************************/

#ifndef ___SHADER_PARSER_LOG_TYPE_H___
#define ___SHADER_PARSER_LOG_TYPE_H___

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Defines the various log types
	*/
	typedef enum ELogType
		: uint8_t
	{
		ELogType_DEBUG,		//!< Debug type log
		ELogType_INFO,		//!< Info type log
		ELogType_WARNING,	//!< Warning type log
		ELogType_ERROR,		//!< Error type log
		ELogType_COUNT,		//!< Number of log types
	}	ELogType;
}
END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_LOG_TYPE_H___
