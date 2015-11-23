/************************************************************************//**
* @file FactoryGlslParser.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Glsl Parser factory class.
*
* @details CObject factory used to manage Glsl Parser creation.
*
***************************************************************************/

#ifndef ___FACTORY_GLSL_PARSER_H___
#define ___FACTORY_GLSL_PARSER_H___

#include "GlslParserPrerequisites.h"

#include <ShaderParserFactory.h>

BEGIN_NAMESPACE_GLSL_PARSER
{
	/** Glsl Parser factory class.
		CObject factory used to manage Glsl Parser creation.
	*/
	class CFactoryGlslParser
		: public CFactoryShaderParser
	{
	public:
		/** Default constructor.
		*/
		CFactoryGlslParser();

		/** Destructor.
		*/
		virtual ~CFactoryGlslParser();

		/** Get the type of the factory.
		@returns
			String describing the factory type.
		*/
		inline const String GetType() const
		{
			return GLSL::FACTORY_GLSL_PARSER;
		}

	protected:
		/** Register creation functions to create new GLSL parser objects.
		*/
		void RegisterServices();

		/** Registred the GLSL parser object types that the factory can create.
		*/
		void RegisterObjectTypes();
	};
}
END_NAMESPACE_GLSL_PARSER

#endif // ___FACTORY_GLSL_PARSER_H___
