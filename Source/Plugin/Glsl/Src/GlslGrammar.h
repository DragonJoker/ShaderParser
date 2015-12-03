/************************************************************************//**
* @file GlslParser.h
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

BEGIN_NAMESPACE_GLSL_PARSER
{
	/** Class defining a GLSL parser.
	*/
	class CGlslGrammar
		: public CShaderGrammar
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
		Rule variable_identifier;
		Rule field_selection;
		Rule function_identifier;
		Rule function_call_or_method;
		Rule function_call_generic;
		Rule function_call_header_no_parameters;
		Rule function_call_header_with_parameters;
		Rule function_call_header;
		Rule function_call;
		Rule integer_expression;
		Rule postfix_expression_start;
		Rule postfix_expression_rest;
		Rule postfix_expression;
		Rule unary_expression;
		Rule unary_operator;
		Rule multiplicative_expression;
		Rule additive_expression;
		Rule shift_expression;
		Rule relational_expression;
		Rule equality_expression;
		Rule and_expression;
		Rule exclusive_or_expression;
		Rule inclusive_or_expression;
		Rule inclusive_or_expression_helper;
		Rule logical_and_expression;
		Rule logical_xor_expression;
		Rule logical_or_expression;
		Rule conditional_expression;
		Rule assignment_operator;
		Rule assignment_expression;
		Rule expression;
		Rule primary_expression;
		Rule type_name;
		Rule constant_expression;
		Rule type_qualifier;
		Rule fully_specified_type;
		Rule array_specifier;
		Rule function_header;
		Rule parameter_declarator;
		Rule parameter_type_specifier;
		Rule parameter_declaration;
		Rule function_header_with_parameters;
		Rule function_declarator;
		Rule function_prototype;
		Rule identifier_list;
		Rule initializer;
		Rule declaration_identifier;
		Rule single_declaration;
		Rule init_declarator_list;
		Rule precision_qualifier;
		Rule declaration;
		Rule invariant_qualifier;
		Rule interpolation_qualifier;
		Rule layout_qualifier_id;
		Rule layout_qualifier_id_list;
		Rule layout_qualifier;
		Rule precise_qualifier;
		Rule type_name_list;
		Rule storage_qualifier;
		Rule type_specifier;
		Rule single_type_qualifier;
		Rule struct_declarator;
		Rule struct_declarator_list;
		Rule struct_declaration;
		Rule struct_declaration_list;
		Rule struct_specifier;
		Rule base_type_specifier;
		Rule vec_specifier;
		Rule mat_specifier;
		Rule fsampler_specifier;
		Rule isampler_specifier;
		Rule usampler_specifier;
		Rule image_specifier;
		Rule iimage_specifier;
		Rule uimage_specifier;
		Rule type_specifier_nonarray;
		Rule initializer_list;
		Rule declaration_statement;
		Rule compound_statement_no_new_scope;
		Rule statement_no_new_scope;
		Rule compound_statement;
		Rule statement;
		Rule statement_list;
		Rule expression_statement;
		Rule selection_rest_statement;
		Rule selection_statement;
		Rule for_init_statement;
		Rule condition;
		Rule case_label;
		Rule switch_statement_list;
		Rule switch_statement;
		Rule conditionopt;
		Rule for_rest_statement;
		Rule iteration_statement;
		Rule jump_statement;
		Rule simple_statement;
		Rule function_definition;
		Rule external_declaration;
	};
}
END_NAMESPACE_GLSL_PARSER

#endif // ___PLUGIN_GLSL_PARSER_H___
