/************************************************************************//**
* @file ShaderParserKeywords.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class listing Parser keywords.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_KEYWORDS_H___
#define ___SHADER_PARSER_KEYWORDS_H___

#include "EToken.h"

namespace ShaderParser
{
	/** Class listing Parser keywords
	*/
	template< typename TokenType >
	class CParserKeywords
		: public qi::symbols< char, TokenType >
	{
	public:
		/**
		@brief
			Constructor
		*/
		CParserKeywords()
		{
		}
		/**
		@brief
			Destructor
		*/
		~CParserKeywords()
		{
		}
	};
}

#endif // ___SHADER_PARSER_KEYWORDS_H___
