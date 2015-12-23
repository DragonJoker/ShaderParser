/************************************************************************//**
* @file GlslGrammar.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a GLSL parser.
*
***************************************************************************/

#ifndef ___GLSL_PARSER_H___
#define ___GLSL_PARSER_H___

#include "GlslParserPrerequisites.h"

#include <ShaderGrammar.h>

namespace GlslParser
{
	/** Class defining a GLSL parser.
	*/
	class CGlslGrammar
		: public ShaderParser::CShaderGrammar
	{
	public:
		/** Default constructor.
		*/
		CGlslGrammar();

		/** Destructor.
		*/
		virtual ~CGlslGrammar();

		/** Creates the grammar
		*/
		static CShaderGrammar * Create();

	private:
		ShaderParser::Rule type_specifier;
		ShaderParser::Rule function_header;
		ShaderParser::Rule parameter_declarator;
		ShaderParser::Rule parameter_type_specifier;
		ShaderParser::Rule parameter_declaration;
		ShaderParser::Rule function_header_with_parameters;
		ShaderParser::Rule function_declarator;
		ShaderParser::Rule function_prototype;
		ShaderParser::Rule identifier_list;
		ShaderParser::Rule initializer;
		ShaderParser::Rule declaration_identifier;
		ShaderParser::Rule single_declaration;
		ShaderParser::Rule init_declarator_list;
		ShaderParser::Rule declaration;
		ShaderParser::Rule initializer_list;
		ShaderParser::Rule declaration_statement;
		ShaderParser::Rule compound_statement_no_new_scope;
		ShaderParser::Rule statement_no_new_scope;
		ShaderParser::Rule compound_statement;
		ShaderParser::Rule statement;
		ShaderParser::Rule statement_list;
		ShaderParser::Rule expression_statement;
		ShaderParser::Rule selection_rest_statement;
		ShaderParser::Rule selection_statement;
		ShaderParser::Rule for_init_statement;
		ShaderParser::Rule condition;
		ShaderParser::Rule case_label;
		ShaderParser::Rule switch_statement_list;
		ShaderParser::Rule switch_statement;
		ShaderParser::Rule conditionopt;
		ShaderParser::Rule for_rest_statement;
		ShaderParser::Rule iteration_statement;
		ShaderParser::Rule jump_statement;
		ShaderParser::Rule simple_statement;
		ShaderParser::Rule function_definition;
		ShaderParser::Rule external_declaration;
		ShaderParser::Rule translation_unit;

		std::unique_ptr< CGlslExpressionGrammar > m_expression;
		std::unique_ptr< CGlslTypeGrammar > m_type;
	};
}

#endif // ___PLUGIN_GLSL_PARSER_H___
