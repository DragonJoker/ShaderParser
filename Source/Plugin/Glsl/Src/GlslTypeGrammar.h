/************************************************************************//**
* @file GlslTypeGrammar.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a GLSL parser for types.
*
***************************************************************************/

#ifndef ___GLSL_TYPE_GRAMMAR_H___
#define ___GLSL_TYPE_GRAMMAR_H___

#include "GlslParserPrerequisites.h"

#include <ShaderGrammar.h>

namespace GlslParser
{
	/** Class defining a GLSL parser for types.
	*/
	class CGlslTypeGrammar
		: public ShaderParser::CShaderGrammar
	{
	public:
		/** Default constructor.
		*/
		CGlslTypeGrammar( ShaderParser::Rule & type_specifier, CGlslExpressionGrammar const & expression );

		/** Destructor.
		*/
		virtual ~CGlslTypeGrammar();

	public:
		ShaderParser::Rule fully_specified_type;
		ShaderParser::Rule array_specifier;
		ShaderParser::Rule type_qualifier;
		ShaderParser::Rule precision_qualifier;
		ShaderParser::Rule struct_declaration_list;

	private:
		ShaderParser::Rule type_name;
		ShaderParser::Rule invariant_qualifier;
		ShaderParser::Rule interpolation_qualifier;
		ShaderParser::Rule layout_qualifier_id;
		ShaderParser::Rule layout_qualifier_id_list;
		ShaderParser::Rule layout_qualifier;
		ShaderParser::Rule precise_qualifier;
		ShaderParser::Rule type_name_list;
		ShaderParser::Rule storage_qualifier;
		ShaderParser::Rule single_type_qualifier;
		ShaderParser::Rule struct_declarator;
		ShaderParser::Rule struct_declarator_list;
		ShaderParser::Rule struct_declaration;
		ShaderParser::Rule struct_specifier;
		ShaderParser::Rule base_type_specifier;
		ShaderParser::Rule vec_specifier;
		ShaderParser::Rule mat_specifier;
		ShaderParser::Rule dmat_specifier;
		ShaderParser::Rule fsampler_specifier;
		ShaderParser::Rule isampler_specifier;
		ShaderParser::Rule usampler_specifier;
		ShaderParser::Rule image_specifier;
		ShaderParser::Rule iimage_specifier;
		ShaderParser::Rule uimage_specifier;
		ShaderParser::Rule type_specifier_nonarray;
	};
}

#endif // ___PLUGIN_GLSL_PARSER_H___
