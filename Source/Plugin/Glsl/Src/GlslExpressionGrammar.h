/************************************************************************//**
* @file GlslExpressionGrammar.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief The grammar used to parse expressions.
*
***************************************************************************/

#ifndef ___GLSL_EXPRESSION_GRAMMAR_H___
#define ___GLSL_EXPRESSION_GRAMMAR_H___

#include "GlslParserPrerequisites.h"

#include <ShaderGrammar.h>

namespace GlslParser
{
	/** Class defining a GLSL parser.
	*/
	class CGlslExpressionGrammar
		: public ShaderParser::CShaderGrammar
	{
	public:
		/** Default constructor.
		*/
		CGlslExpressionGrammar( ShaderParser::Rule const & type_specifier );

		/** Destructor.
		*/
		virtual ~CGlslExpressionGrammar();

	private:
		ShaderParser::Rule variable_identifier;
		ShaderParser::Rule field_selection;
		ShaderParser::Rule function_identifier;
		ShaderParser::Rule function_call_or_method;
		ShaderParser::Rule function_call_generic;
		ShaderParser::Rule function_call_header_no_parameters;
		ShaderParser::Rule function_call_header_with_parameters;
		ShaderParser::Rule function_call_header;
		ShaderParser::Rule function_call;
		ShaderParser::Rule integer_expression;
		ShaderParser::Rule postfix_expression_start;
		ShaderParser::Rule postfix_expression_rest;
		ShaderParser::Rule postfix_expression;
		ShaderParser::Rule unary_expression;
		ShaderParser::Rule unary_operator;
		ShaderParser::Rule multiplicative_expression;
		ShaderParser::Rule additive_expression;
		ShaderParser::Rule shift_expression;
		ShaderParser::Rule relational_expression;
		ShaderParser::Rule equality_expression;
		ShaderParser::Rule and_expression;
		ShaderParser::Rule exclusive_or_expression;
		ShaderParser::Rule inclusive_or_expression;
		ShaderParser::Rule inclusive_or_expression_helper;
		ShaderParser::Rule logical_and_expression;
		ShaderParser::Rule logical_xor_expression;
		ShaderParser::Rule logical_or_expression;
		ShaderParser::Rule conditional_expression;
		ShaderParser::Rule assignment_operator;
		ShaderParser::Rule expression;
		ShaderParser::Rule primary_expression;

	public:
		ShaderParser::Rule assignment_expression;
		ShaderParser::Rule constant_expression;

		//ShaderParser::Rule type_name;
		//ShaderParser::Rule type_qualifier;
		//ShaderParser::Rule fully_specified_type;
		//ShaderParser::Rule array_specifier;
		//ShaderParser::Rule function_header;
		//ShaderParser::Rule parameter_declarator;
		//ShaderParser::Rule parameter_type_specifier;
		//ShaderParser::Rule parameter_declaration;
		//ShaderParser::Rule function_header_with_parameters;
		//ShaderParser::Rule function_declarator;
		//ShaderParser::Rule function_prototype;
		//ShaderParser::Rule identifier_list;
		//ShaderParser::Rule initializer;
		//ShaderParser::Rule declaration_identifier;
		//ShaderParser::Rule single_declaration;
		//ShaderParser::Rule init_declarator_list;
		//ShaderParser::Rule precision_qualifier;
		//ShaderParser::Rule declaration;
		//ShaderParser::Rule invariant_qualifier;
		//ShaderParser::Rule interpolation_qualifier;
		//ShaderParser::Rule layout_qualifier_id;
		//ShaderParser::Rule layout_qualifier_id_list;
		//ShaderParser::Rule layout_qualifier;
		//ShaderParser::Rule precise_qualifier;
		//ShaderParser::Rule type_name_list;
		//ShaderParser::Rule storage_qualifier;
		//ShaderParser::Rule single_type_qualifier;
		//ShaderParser::Rule struct_declarator;
		//ShaderParser::Rule struct_declarator_list;
		//ShaderParser::Rule struct_declaration;
		//ShaderParser::Rule struct_declaration_list;
		//ShaderParser::Rule struct_specifier;
		//ShaderParser::Rule base_type_specifier;
		//ShaderParser::Rule vec_specifier;
		//ShaderParser::Rule mat_specifier;
		//ShaderParser::Rule fsampler_specifier;
		//ShaderParser::Rule isampler_specifier;
		//ShaderParser::Rule usampler_specifier;
		//ShaderParser::Rule image_specifier;
		//ShaderParser::Rule iimage_specifier;
		//ShaderParser::Rule uimage_specifier;
		//ShaderParser::Rule type_specifier_nonarray;
		//ShaderParser::Rule initializer_list;
		//ShaderParser::Rule declaration_statement;
		//ShaderParser::Rule compound_statement_no_new_scope;
		//ShaderParser::Rule statement_no_new_scope;
		//ShaderParser::Rule compound_statement;
		//ShaderParser::Rule statement;
		//ShaderParser::Rule statement_list;
		//ShaderParser::Rule expression_statement;
		//ShaderParser::Rule selection_rest_statement;
		//ShaderParser::Rule selection_statement;
		//ShaderParser::Rule for_init_statement;
		//ShaderParser::Rule condition;
		//ShaderParser::Rule case_label;
		//ShaderParser::Rule switch_statement_list;
		//ShaderParser::Rule switch_statement;
		//ShaderParser::Rule conditionopt;
		//ShaderParser::Rule for_rest_statement;
		//ShaderParser::Rule iteration_statement;
		//ShaderParser::Rule jump_statement;
		//ShaderParser::Rule simple_statement;
		//ShaderParser::Rule function_definition;
		//ShaderParser::Rule external_declaration;
	};
}

#endif // ___PLUGIN_GLSL_PARSER_H___
