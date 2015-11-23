/************************************************************************//**
* @file FactoryHlslParser.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Hlsl Parser factory class.
*
* @details CObject factory used to manage Hlsl Parser creation.
*
***************************************************************************/

#ifndef ___FACTORY_HLSL_PARSER_H___
#define ___FACTORY_HLSL_PARSER_H___

#include "HlslParserPrerequisites.h"

#include <ShaderParserFactory.h>

BEGIN_NAMESPACE_HLSL_PARSER
{
	/** Hlsl Parser factory class.
		CObject factory used to manage Hlsl Parser creation.
	*/
	class CFactoryHlslParser
		: public CFactoryShaderParser
	{
	public:
		/** Default constructor.
		*/
		CFactoryHlslParser();

		/** Destructor.
		*/
		virtual ~CFactoryHlslParser();

		/** Get the type of the factory.
		@returns
			String describing the factory type.
		*/
		inline const String GetType() const
		{
			return HLSL::FACTORY_HLSL_PARSER;
		}

	protected:
		/** Register creation functions to create new HLSL parser objects.
		*/
		void RegisterServices();

		/** Registred the HLSL parser object types that the factory can create.
		*/
		void RegisterObjectTypes();
	};
}
END_NAMESPACE_HLSL_PARSER

#endif // ___FACTORY_HLSL_PARSER_H___
