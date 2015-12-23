/************************************************************************//**
* @file GlslExpressionGrammar.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief The expression parser grammar.
*
***************************************************************************/

#include "GlslParserPch.h"

#include "GlslExpressionGrammar.h"
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

	CGlslExpressionGrammar::CGlslExpressionGrammar( Rule const & type_specifier )
		: CShaderGrammar( expression )
	{
		variable_identifier = identifier[on_rule( "variable_identifier", "identifier" )];
		variable_identifier.name( "variable_identifier" );

		field_selection = identifier[on_rule( "field_selection", "identifier" )];
		field_selection.name( "field_selection" );

		function_call_header = ( function_identifier.alias() >> LEFT_PAREN )[on_rule( "function_call_header", "function_identifier", "LEFT_PAREN" )];
		function_call_header.name( "function_call_header" );

		function_call_header_no_parameters = ( function_call_header >> -VOID )[on_rule( "function_call_header", "-VOID" )];
		function_call_header_no_parameters.name( "function_call_header_no_parameters" );

		function_call_header_with_parameters = ( function_call_header >> assignment_expression.alias() >> *( COMMA >> assignment_expression.alias() ) )[on_rule( "function_call_header_with_parameters", "function_call_header", "assignment_expression.alias()", "*( COMMA assignment_expression.alias() )" )];
		function_call_header_with_parameters.name( "function_call_header_with_parameters" );

		function_call_generic = ( function_call_header_with_parameters[on_rule( "function_call_generic", "function_call_header_with_parameters" )]
								  | ( function_call_header_no_parameters >> RIGHT_PAREN )[on_rule( "function_call_generic", "function_call_header_no_parameters", "RIGHT_PAREN" )] );
		function_call_generic.name( "function_call_generic" );

		function_call_or_method = function_call_generic[on_rule( "function_call_or_method", "function_call_generic" )];
		function_call_or_method.name( "function_call_or_method" );

		function_call = function_call_or_method[on_rule( "function_call", "function_call_or_method" )];
		function_call.name( "function_call" );

		integer_expression = expression.alias();
		integer_expression.name( "integer_expression" );

		postfix_expression_start = primary_expression.alias()
								   | function_call[on_rule( "postfix_expression_start", "function_call" )];
		postfix_expression_start.name( "postfix_expression_start" );

		postfix_expression_rest = ( LEFT_BRACKET >> integer_expression >> RIGHT_BRACKET )[on_rule( "postfix_expression_rest", "LEFT_BRACKET", "integer_expression", "RIGHT_BRACKET" )]
								  | ( ( DOT >> field_selection ) | INC_OP | DEC_OP )[on_rule( "postfix_expression_rest", "( DOT >> field_selection ) | INC_OP | DEC_OP" )];
		postfix_expression_rest.name( "postfix_expression_rest" );

		postfix_expression = ( postfix_expression_start >> *postfix_expression_rest )[on_rule( "postfix_expression", "*postfix_expression_rest" )];
		postfix_expression.name( "postfix_expression" );

		function_identifier = type_specifier.alias()
							  | postfix_expression[on_rule( "function_identifier", "*postfix_expression" )];
		function_identifier.name( "function_identifier" );

		unary_operator = PLUS[on_rule( "unary_operator", "PLUS" )]
						 | DASH[on_rule( "unary_operator", "DASH" )]
						 | BANG[on_rule( "unary_operator", "BANG" )]
						 | TILDE[on_rule( "unary_operator", "TILDE" )];
		unary_operator.name( "unary_operator" );

		unary_expression = postfix_expression[on_rule( "unary_expression", "*postfix_expression" )]
						   | ( ( INC_OP | DEC_OP | unary_operator ) >> unary_expression )[on_rule( "unary_expression", "( INC_OP | DEC_OP | unary_operator )", "unary_expression" )];
		unary_expression.name( "unary_expression" );

		multiplicative_expression = ( unary_expression >> -( ( STAR | SLASH | PERCENT ) >> multiplicative_expression ) )[on_rule( "multiplicative_expression", "unary_expression", "-( ( STAR | SLASH | PERCENT ) multiplicative_expression )" )];
		multiplicative_expression.name( "multiplicative_expression" );

		additive_expression = multiplicative_expression >> -( ( PLUS | DASH ) >> additive_expression )[on_rule( "additive_expression", "multiplicative_expression", "-( ( PLUS | DASH ) additive_expression )" )];
		additive_expression.name( "additive_expression" );

		shift_expression = additive_expression >> -( ( LEFT_OP | RIGHT_OP ) >> shift_expression )[on_rule( "shift_expression", "additive_expression", "-( ( LEFT_OP | RIGHT_OP ) shift_expression )" )];
		shift_expression.name( "shift_expression" );

		relational_expression = shift_expression >> -( ( LEFT_ANGLE | RIGHT_ANGLE | LE_OP | GE_OP ) >> relational_expression )[on_rule( "relational_expression", "shift_expression", "-( ( LEFT_ANGLE | RIGHT_ANGLE | LE_OP | GE_OP ) relational_expression )" )];
		relational_expression.name( "relational_expression" );

		equality_expression = relational_expression >> -( ( EQ_OP | NE_OP ) >> equality_expression )[on_rule( "equality_expression", "relational_expression", "-( ( EQ_OP | NE_OP ) equality_expression )" )];
		equality_expression.name( "equality_expression" );

		and_expression = equality_expression >> -( AMPERSAND >> and_expression )[on_rule( "and_expression", "equality_expression", "-( AMPERSAND and_expression )" )];
		and_expression.name( "and_expression" );

		exclusive_or_expression = and_expression >> -( CARET >> exclusive_or_expression )[on_rule( "exclusive_or_expression", "and_expression", "-( CARET exclusive_or_expression )" )];
		exclusive_or_expression.name( "exclusive_or_expression" );

		inclusive_or_expression = exclusive_or_expression >> -( VERTICAL_BAR >> inclusive_or_expression )[on_rule( "inclusive_or_expression", "exclusive_or_expression", "-( VERTICAL_BAR inclusive_or_expression )" )];
		inclusive_or_expression.name( "inclusive_or_expression" );

		logical_and_expression = inclusive_or_expression >> -( AND_OP >> logical_and_expression )[on_rule( "logical_and_expression", "inclusive_or_expression", "-( AND_OP logical_and_expression )" )];
		logical_and_expression.name( "logical_and_expression" );

		logical_xor_expression = logical_and_expression >> -( XOR_OP >> logical_xor_expression )[on_rule( "logical_xor_expression", "logical_and_expression", "-( XOR_OP logical_xor_expression )" )];
		logical_xor_expression.name( "logical_xor_expression" );

		logical_or_expression = logical_xor_expression >> -( OR_OP >> logical_or_expression )[on_rule( "logical_or_expression", "logical_xor_expression", "-( OR_OP logical_or_expression )" )];
		logical_or_expression.name( "logical_or_expression" );

		conditional_expression = ( logical_or_expression >> -( QUESTION >> expression.alias() >> COLON >> assignment_expression.alias() ) )[on_rule( "conditional_expression", "logical_or_expression", "-( QUESTION expression.alias() COLON assignment_expression.alias() )" )];
		conditional_expression.name( "conditional_expression" );

		assignment_operator = EQUAL[on_rule( "assignment_operator", "TILDE" )]
							  | MUL_ASSIGN[on_rule( "assignment_operator", "MUL_ASSIGN" )]
							  | DIV_ASSIGN[on_rule( "assignment_operator", "DIV_ASSIGN" )]
							  | MOD_ASSIGN[on_rule( "assignment_operator", "MOD_ASSIGN" )]
							  | ADD_ASSIGN[on_rule( "assignment_operator", "ADD_ASSIGN" )]
							  | SUB_ASSIGN[on_rule( "assignment_operator", "SUB_ASSIGN" )]
							  | LEFT_ASSIGN[on_rule( "assignment_operator", "LEFT_ASSIGN" )]
							  | RIGHT_ASSIGN[on_rule( "assignment_operator", "RIGHT_ASSIGN" )]
							  | AND_ASSIGN[on_rule( "assignment_operator", "AND_ASSIGN" )]
							  | XOR_ASSIGN[on_rule( "assignment_operator", "XOR_ASSIGN" )]
							  | OR_ASSIGN[on_rule( "assignment_operator", "OR_ASSIGN" )];
		assignment_operator.name( "assignment_operator" );

		assignment_expression = conditional_expression[on_rule( "assignment_expression", "conditional_expression" )]
								| ( unary_expression >> assignment_operator >> assignment_expression )[on_rule( "assignment_expression", "unary_expression", "assignment_operator", "assignment_expression" )];
		assignment_expression.name( "assignment_expression" );

		expression = ( assignment_expression >> *( COMMA >> assignment_expression ) )[on_rule( "assignment_expression", "logical_xor_expression", "*( COMMA assignment_expression )" )];
		expression.name( "expression" );

		primary_expression = variable_identifier[on_rule( "primary_expression", "variable_identifier" )]
							 | integer_constant[on_rule( "primary_expression", "integer_constant" )]
							 | uinteger_constant[on_rule( "primary_expression", "uinteger_constant" )]
							 | floating_constant[on_rule( "primary_expression", "floating_constant" )]
							 | bool_constant[on_rule( "primary_expression", "bool_constant" )]
							 | double_constant[on_rule( "primary_expression", "conditional_expression" )]
							 | ( LEFT_PAREN >> expression >> RIGHT_PAREN )[on_rule( "primary_expression", "double_constant" )];
		primary_expression.name( "primary_expression" );

		constant_expression = conditional_expression[on_rule( "constant_expression", "conditional_expression" )];
		constant_expression.name( "constant_expression" );
	}

	CGlslExpressionGrammar::~CGlslExpressionGrammar()
	{
	}
}
