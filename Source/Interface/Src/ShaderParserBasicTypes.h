/************************************************************************//**
* @file ShaderParserBasicTypes.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class listing Parser basic types.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_BASIC_TYPES_H___
#define ___SHADER_PARSER_BASIC_TYPES_H___

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** Class listing Parser basic types
	*/
	template< typename KeywordType >
	class CParserBasicTypes
		: public qi::symbols< char, KeywordType >
	{
	public:
		/**
		@brief
			Constructor
		*/
		CParserBasicTypes()
		{
		}
		/**
		@brief
			Destructor
		*/
		~CParserBasicTypes()
		{
		}
	};

} END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_BASIC_TYPES_H___
