/************************************************************************//**
* @file GlslGrammar.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining the GLSL parser.
*
***************************************************************************/

#include "GlslParserPch.h"

#include "GlslGrammar.h"
#include "GlslExpressionGrammar.h"
#include "GlslTypeGrammar.h"
#include "GlslParserKeywords.h"
#include "GlslParserBasicType.h"

#include <ShaderParserLogger.h>

using namespace ShaderParser;

#if defined( VOID )
#	undef VOID
#endif

#if defined( CONST)
#	undef CONST
#endif

#if defined( IN)
#	undef IN
#endif

#if defined( OUT)
#	undef OUT
#endif

namespace GlslParser
{
	namespace
	{
		struct on_rule
		{
			using string_array = std::vector< std::string >;

			template< typename ... Params >
			on_rule( std::string const & p_lhs, Params ... p_rhs )
			{
				std::stringstream l_stream;
				l_stream << p_lhs << " -->";
				fill( l_stream, p_rhs... );
				m_rule = l_stream.str();
			}

			void fill( std::ostream & p_stream, std::string const & p_param )
			{
				p_stream << "\n\t" << p_param;
			}

			template< typename ... Params >
			void fill( std::ostream & p_stream, std::string const & p_param, Params ... p_params )
			{
				p_stream << "\n\t" << p_param;
				fill( p_stream, p_params... );
			}

			void operator()( boost::spirit::unused_type &
							 , boost::spirit::context< boost::fusion::cons< boost::spirit::unused_type &, boost::fusion::nil_ >
							 , boost::fusion::vector0<> > &
							 , bool & )const
			{
				CLogger::LogDebug( m_rule );
			}

			std::string m_rule;
		};
	}

	static const Rule PRECISION( "precision", "PRECISION" );
	static const Rule DISCARD( "discard", "DISCARD" );

	CGlslGrammar::CGlslGrammar()
		: CShaderGrammar( translation_unit )
	{
		m_expression = std::make_unique< CGlslExpressionGrammar >( type_specifier );
		m_type = std::make_unique< CGlslTypeGrammar >( type_specifier, *m_expression );

		function_header = ( *m_type >> identifier >> LEFT_PAREN )[on_rule( "function_header", "identifier", "fully_specified_type", "LEFT_PAREN" )];
		function_header.name( "function_header" );

		parameter_declarator = ( type_specifier >> identifier >> -m_type->array_specifier )[on_rule( "parameter_declarator", "type_specifier", "identifier", "-array_specifier" )];
		parameter_declarator.name( "parameter_declarator" );

		parameter_type_specifier = type_specifier;
		parameter_type_specifier.name( "parameter_type_specifier" );

		parameter_declaration = ( -m_type->type_qualifier >> ( parameter_declarator | parameter_type_specifier ) )[on_rule( "parameter_declaration", "-type_qualifier", "( parameter_declarator | parameter_type_specifier )" )];
		parameter_declaration.name( "parameter_declaration" );

		function_header_with_parameters = function_header[on_rule( "function_header_with_parameters", "function_header" )];
		function_header_with_parameters.name( "function_header_with_parameters" );

		function_declarator = ( function_header >> -( parameter_declaration >> *( COMMA >> parameter_declaration ) ) )[on_rule( "function_header_with_parameters", "function_header", "-( parameter_declaration *( COMMA parameter_declaration ) )" )];
		function_declarator.name( "function_declarator" );

		function_prototype = ( function_declarator >> RIGHT_PAREN )[on_rule( "function_prototype", "function_declarator", "RIGHT_PAREN" )];
		function_prototype.name( "function_prototype" );

		identifier_list = ( identifier >> *( COMMA >> identifier ) )[on_rule( "identifier_list", "*( COMMA identifier )" )];
		identifier_list.name( "identifier_list" );

		initializer = m_expression->assignment_expression[on_rule( "initializer", "assignment_expression" )]
					  | ( LEFT_BRACE >> initializer_list.alias() >> -COMMA >> RIGHT_BRACE )[on_rule( "initializer", "LEFT_BRACE", "initializer_list.alias()", "-COMMA", "RIGHT_BRACE" )];
		initializer.name( "initializer" );

		declaration_identifier = ( identifier >> -m_type->array_specifier >> -( EQUAL >> initializer ) )[on_rule( "declaration_identifier", "identifier", "-array_specifier", "-( EQUAL initializer )" )];
		declaration_identifier.name( "declaration_identifier" );

		single_declaration = ( *m_type >> -declaration_identifier )[on_rule( "single_declaration", "fully_specified_type", "-declaration_identifier" )];
		single_declaration.name( "single_declaration" );

		init_declarator_list = ( single_declaration >> *( COMMA >> declaration_identifier ) )[on_rule( "init_declarator_list", "single_declaration", "*( COMMA >> declaration_identifier )" )];
		init_declarator_list.name( "init_declarator_list" );

		declaration = ( function_prototype >> SEMICOLON )[on_rule( "declaration", "function_prototype", "SEMICOLON" )]
					  | ( init_declarator_list >> SEMICOLON )[on_rule( "declaration", "init_declarator_list", "SEMICOLON" )]
					  | ( PRECISION >> m_type->precision_qualifier >> type_specifier.alias() >> SEMICOLON )[on_rule( "declaration", "PRECISION", "precision_qualifier", "type_specifier.alias()", "SEMICOLON" )]
					  | ( m_type->type_qualifier >> identifier >> LEFT_BRACE >> m_type->struct_declaration_list.alias() >> RIGHT_BRACE >> -SEMICOLON )[on_rule( "declaration", "type_qualifier", "identifier", "LEFT_BRACE", "struct_declaration_list.alias()", "RIGHT_BRACE", "-SEMICOLON" )]
					  | ( identifier >> -m_type->array_specifier >> SEMICOLON )[on_rule( "declaration", "identifier", "-array_specifier", "SEMICOLON" )]
					  | ( m_type->type_qualifier >> -identifier_list >> SEMICOLON )[on_rule( "declaration", "type_qualifier", "-identifier_list", "SEMICOLON" )];
		declaration.name( "declaration" );

		initializer_list = initializer >> *( COMMA >> initializer );
		initializer_list.name( "initializer_list" );

		declaration_statement = declaration;
		declaration_statement.name( "declaration_statement" );

		compound_statement_no_new_scope = ( LEFT_BRACE >> RIGHT_BRACE )
										  | ( LEFT_BRACE >> statement_list.alias() >> RIGHT_BRACE );
		compound_statement_no_new_scope.name( "compound_statement_no_new_scope" );

		statement_no_new_scope = compound_statement_no_new_scope
								 | simple_statement.alias();
		statement_no_new_scope.name( "statement_no_new_scope" );

		compound_statement = ( LEFT_BRACE >> RIGHT_BRACE )[on_rule( "compound_statement", "LEFT_BRACE", "RIGHT_BRACE" )]
							 | ( LEFT_BRACE >> statement_list.alias() >> RIGHT_BRACE )[on_rule( "compound_statement", "LEFT_BRACE", "statement_list.alias()", "RIGHT_BRACE" )];
		compound_statement.name( "compound_statement" );

		statement = compound_statement[on_rule( "statement", "compound_statement" )]
					| simple_statement.alias();
		statement.name( "statement" );

		statement_list = statement[on_rule( "statement_list", "statement" )]
						 | ( statement >> *statement_list )[on_rule( "statement_list", "statement", "*statement_list" )];
		statement_list.name( "statement_list" );

		expression_statement = ( -( *m_expression ) >> SEMICOLON )[on_rule( "expression_statement", "-expression", "SEMICOLON" )];
		expression_statement.name( "expression_statement" );

		selection_rest_statement = ( statement >> -( ELSE >> statement ) )[on_rule( "selection_rest_statement", "statement", "-( ELSE statement )" )];
		selection_rest_statement.name( "selection_rest_statement" );

		selection_statement = ( IF >> LEFT_PAREN >> ( *m_expression ) >> RIGHT_PAREN >> selection_rest_statement )[on_rule( "selection_statement", "IF", "LEFT_PAREN", "expression", "selection_rest_statement )" )];
		selection_statement.name( "selection_statement" );

		condition = ( *m_expression )[on_rule( "condition", "expression" )]
					| ( *m_type >> identifier >> EQUAL >> initializer )[on_rule( "condition", "fully_specified_type", "identifier", "EQUAL", "initializer )" )];
		condition.name( "condition" );

		case_label = ( ( ( CASE >> ( *m_expression ) ) | DEFAULT ) >> COLON )[on_rule( "case_label", "( ( CASE >> expression ) | DEFAULT )", "COLON" )];
		case_label.name( "case_label" );

		switch_statement_list = ( -statement_list )[on_rule( "switch_statement_list", "-statement_list" )];
		switch_statement_list.name( "switch_statement_list" );

		switch_statement = ( SWITCH >> LEFT_PAREN >> ( *m_expression ) >> RIGHT_PAREN >> LEFT_BRACE >> switch_statement_list >> RIGHT_BRACE )[on_rule( "switch_statement", "SWITCH", "LEFT_PAREN", "expression", "RIGHT_PAREN", "LEFT_BRACE", "switch_statement_list", "RIGHT_BRACE" )];
		switch_statement.name( "switch_statement" );

		for_init_statement = expression_statement[on_rule( "for_init_statement", "expression_statement" )]
							 | declaration_statement[on_rule( "for_init_statement", "declaration_statement" )];
		for_init_statement.name( "for_init_statement" );

		for_rest_statement = ( -condition >> SEMICOLON >> -( *m_expression ) )[on_rule( "for_rest_statement", "-condition", "SEMICOLON", "-expression" )];
		for_rest_statement.name( "for_rest_statement" );

		iteration_statement = ( WHILE >> LEFT_PAREN >> condition >> RIGHT_PAREN >> statement_no_new_scope )[on_rule( "iteration_statement", "WHILE", "LEFT_PAREN", "condition", "RIGHT_PAREN", "statement_no_new_scope" )]
							  | ( DO >> statement >> WHILE >> LEFT_PAREN >> ( *m_expression ) >> RIGHT_PAREN >> SEMICOLON )[on_rule( "iteration_statement", "DO", "statement", "WHILE", "LEFT_PAREN", "expression", "RIGHT_PAREN", "SEMICOLON" )]
							  | ( FOR >> LEFT_PAREN >> for_init_statement >> for_rest_statement >> RIGHT_PAREN )[on_rule( "iteration_statement", "FOR", "LEFT_PAREN", "for_init_statement", "for_rest_statement", "RIGHT_PAREN" )]
							  | statement_no_new_scope[on_rule( "iteration_statement", "statement_no_new_scope" )];
		iteration_statement.name( "iteration_statement" );

		jump_statement = ( CONTINUE | BREAK | ( RETURN >> -( *m_expression ) ) | DISCARD ) >> SEMICOLON;
		jump_statement.name( "jump_statement" );

		simple_statement = declaration_statement[on_rule( "simple_statement", "declaration_statement" )]
						   | expression_statement[on_rule( "simple_statement", "expression_statement" )]
						   | selection_statement[on_rule( "simple_statement", "selection_statement" )]
						   | switch_statement[on_rule( "simple_statement", "switch_statement" )]
						   | case_label[on_rule( "simple_statement", "case_label" )]
						   | jump_statement[on_rule( "simple_statement", "jump_statement" )]
						   | iteration_statement[on_rule( "simple_statement", "iteration_statement" )];
		simple_statement.name( "simple_statement" );

		function_definition = ( function_prototype >> compound_statement_no_new_scope )[on_rule( "function_definition", "function_prototype", "compound_statement_no_new_scope" )];
		function_definition.name( "function_definition" );

		external_declaration = function_definition[on_rule( "external_declaration", "function_definition" )]
							   | declaration[on_rule( "external_declaration", "declaration" )];
		external_declaration.name( "external_declaration" );

		translation_unit = +external_declaration[on_rule( "translation_unit", "+external_declaration" )];
		//translation_unit = VOID >> "main" >> LEFT_PAREN >> -VOID >> RIGHT_PAREN >> LEFT_BRACE >> RIGHT_BRACE;
		translation_unit.name( "translation_unit" );
	}

	CGlslGrammar::~CGlslGrammar()
	{
	}

	CShaderGrammar * CGlslGrammar::Create()
	{
		return new CGlslGrammar;
	}
}
