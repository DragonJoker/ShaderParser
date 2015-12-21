/************************************************************************//**
* @file GlslParser.cpp
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
#include "GlslParserKeywords.h"
#include "GlslParserBasicType.h"

#include <ShaderParserLogger.h>

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

BEGIN_NAMESPACE_GLSL_PARSER
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
				p_stream << " " << p_param;
			}

			template< typename ... Params >
			void fill( std::ostream & p_stream, std::string const & p_param, Params ... p_params )
			{
				p_stream << " " << p_param;
				fill( p_stream, p_params... );
			}

			void operator()( boost::spirit::unused_type &
							 , boost::spirit::context<boost::fusion::cons<boost::spirit::unused_type &, boost::fusion::nil_>
							 , boost::fusion::vector0<> > &
							 , bool & )const
			{
				CLogger::LogDebug( m_rule );
			}

			std::string m_rule;
		};

		static const Rule VOID( "void", "VOID" );
		static const Rule FLOAT( "float", "FLOAT" );
		static const Rule DOUBLE( "double", "DOUBLE" );
		static const Rule INT( "int", "INT" );
		static const Rule UINT( "uint", "UINT" );
		static const Rule BOOL( "bool", "BOOL" );
		static const Rule VEC2( "vec2", "VEC2" );
		static const Rule VEC3( "vec3", "VEC3" );
		static const Rule VEC4( "vec4", "VEC4" );
		static const Rule DVEC2( "dvec2", "DVEC2" );
		static const Rule DVEC3( "dvec3", "DVEC3" );
		static const Rule DVEC4( "dvec4", "DVEC4" );
		static const Rule BVEC2( "bvec2", "BVEC2" );
		static const Rule BVEC3( "bvec3", "BVEC3" );
		static const Rule BVEC4( "bvec4", "BVEC4" );
		static const Rule IVEC2( "ivec2", "IVEC2" );
		static const Rule IVEC3( "ivec3", "IVEC3" );
		static const Rule IVEC4( "ivec4", "IVEC4" );
		static const Rule UVEC2( "uvec2", "UVEC2" );
		static const Rule UVEC3( "uvec3", "UVEC3" );
		static const Rule UVEC4( "uvec4", "UVEC4" );
		static const Rule MAT2( "mat2", "MAT2" );
		static const Rule MAT3( "mat3", "MAT3" );
		static const Rule MAT4( "mat4", "MAT4" );
		static const Rule MAT2X2( "mat2x2", "MAT2X2" );
		static const Rule MAT2X3( "mat2x3", "MAT2X3" );
		static const Rule MAT2X4( "mat2x4", "MAT2X4" );
		static const Rule MAT3X2( "mat3x2", "MAT3X2" );
		static const Rule MAT3X3( "mat3x3", "MAT3X3" );
		static const Rule MAT3X4( "mat3x4", "MAT3X4" );
		static const Rule MAT4X2( "mat4x2", "MAT4X2" );
		static const Rule MAT4X3( "mat4x3", "MAT4X3" );
		static const Rule MAT4X4( "mat4x4", "MAT4X4" );
		static const Rule DMAT2( "dmat2", "DMAT2" );
		static const Rule DMAT3( "dmat3", "DMAT3" );
		static const Rule DMAT4( "dmat4", "DMAT4" );
		static const Rule DMAT2X2( "dmat2x2", "DMAT2X2" );
		static const Rule DMAT2X3( "dmat2x3", "DMAT2X3" );
		static const Rule DMAT2X4( "dmat2x4", "DMAT2X4" );
		static const Rule DMAT3X2( "dmat3x2", "DMAT3X2" );
		static const Rule DMAT3X3( "dmat3x3", "DMAT3X3" );
		static const Rule DMAT3X4( "dmat3x4", "DMAT3X4" );
		static const Rule DMAT4X2( "dmat4x2", "DMAT4X2" );
		static const Rule DMAT4X3( "dmat4x3", "DMAT4X3" );
		static const Rule DMAT4X4( "dmat4x4", "DMAT4X4" );
		static const Rule ATOMIC_UINT( "atomic_uint", "ATOMIC_UINT" );
		static const Rule SAMPLER1D( "sampler1d", "SAMPLER1D" );
		static const Rule SAMPLER2D( "sampler2d", "SAMPLER2D" );
		static const Rule SAMPLER3D( "sampler3d", "SAMPLER3D" );
		static const Rule SAMPLERCUBE( "samplercube", "SAMPLERCUBE" );
		static const Rule SAMPLER1DSHADOW( "sampler1dshadow", "SAMPLER1DSHADOW" );
		static const Rule SAMPLER2DSHADOW( "sampler2dshadow", "SAMPLER2DSHADOW" );
		static const Rule SAMPLERCUBESHADOW( "samplercubeshadow", "SAMPLERCUBESHADOW" );
		static const Rule SAMPLER1DARRAY( "sampler1darray", "SAMPLER1DARRAY" );
		static const Rule SAMPLER2DARRAY( "sampler2darray", "SAMPLER2DARRAY" );
		static const Rule SAMPLER1DARRAYSHADOW( "sampler1darrayshadow", "SAMPLER1DARRAYSHADOW" );
		static const Rule SAMPLER2DARRAYSHADOW( "sampler2darrayshadow", "SAMPLER2DARRAYSHADOW" );
		static const Rule SAMPLERCUBEARRAY( "samplercubearray", "SAMPLERCUBEARRAY" );
		static const Rule SAMPLERCUBEARRAYSHADOW( "samplercubearrayshadow", "SAMPLERCUBEARRAYSHADOW" );
		static const Rule ISAMPLER1D( "isampler1d", "ISAMPLER1D" );
		static const Rule ISAMPLER2D( "isampler2d", "ISAMPLER2D" );
		static const Rule ISAMPLER3D( "isampler3d", "ISAMPLER3D" );
		static const Rule ISAMPLERCUBE( "isamplercube", "ISAMPLERCUBE" );
		static const Rule ISAMPLER1DARRAY( "isampler1darray", "ISAMPLER1DARRAY" );
		static const Rule ISAMPLER2DARRAY( "isampler2darray", "ISAMPLER2DARRAY" );
		static const Rule ISAMPLERCUBEARRAY( "isamplercubearray", "ISAMPLERCUBEARRAY" );
		static const Rule USAMPLER1D( "usampler1d", "USAMPLER1D" );
		static const Rule USAMPLER2D( "usampler2d", "USAMPLER2D" );
		static const Rule USAMPLER3D( "usampler3d", "USAMPLER3D" );
		static const Rule USAMPLERCUBE( "usamplercube", "USAMPLERCUBE" );
		static const Rule USAMPLER1DARRAY( "usampler1darray", "USAMPLER1DARRAY" );
		static const Rule USAMPLER2DARRAY( "usampler2darray", "USAMPLER2DARRAY" );
		static const Rule USAMPLERCUBEARRAY( "usamplercubearray", "USAMPLERCUBEARRAY" );
		static const Rule SAMPLER2DRECT( "sampler2drect", "SAMPLER2DRECT" );
		static const Rule SAMPLER2DRECTSHADOW( "sampler2drectshadow", "SAMPLER2DRECTSHADOW" );
		static const Rule ISAMPLER2DRECT( "isampler2drect", "ISAMPLER2DRECT" );
		static const Rule USAMPLER2DRECT( "usampler2drect", "USAMPLER2DRECT" );
		static const Rule SAMPLERBUFFER( "samplerbuffer", "SAMPLERBUFFER" );
		static const Rule ISAMPLERBUFFER( "isamplerbuffer", "ISAMPLERBUFFER" );
		static const Rule USAMPLERBUFFER( "usamplerbuffer", "USAMPLERBUFFER" );
		static const Rule SAMPLER2DMS( "sampler2dms", "SAMPLER2DMS" );
		static const Rule ISAMPLER2DMS( "isampler2dms", "ISAMPLER2DMS" );
		static const Rule USAMPLER2DMS( "usampler2dms", "USAMPLER2DMS" );
		static const Rule SAMPLER2DMSARRAY( "sampler2dmsarray", "SAMPLER2DMSARRAY" );
		static const Rule ISAMPLER2DMSARRAY( "isampler2dmsarray", "ISAMPLER2DMSARRAY" );
		static const Rule USAMPLER2DMSARRAY( "usampler2dmsarray", "USAMPLER2DMSARRAY" );
		static const Rule IMAGE1D( "image1d", "IMAGE1D" );
		static const Rule IIMAGE1D( "iimage1d", "IIMAGE1D" );
		static const Rule UIMAGE1D( "uimage1d", "UIMAGE1D" );
		static const Rule IMAGE2D( "image2d", "IMAGE2D" );
		static const Rule IIMAGE2D( "iimage2d", "IIMAGE2D" );
		static const Rule UIMAGE2D( "uimage2d", "UIMAGE2D" );
		static const Rule IMAGE3D( "image3d", "IMAGE3D" );
		static const Rule IIMAGE3D( "iimage3d", "IIMAGE3D" );
		static const Rule UIMAGE3D( "uimage3d", "UIMAGE3D" );
		static const Rule IMAGE2DRECT( "image2drect", "IMAGE2DRECT" );
		static const Rule IIMAGE2DRECT( "iimage2drect", "IIMAGE2DRECT" );
		static const Rule UIMAGE2DRECT( "uimage2drect", "UIMAGE2DRECT" );
		static const Rule IMAGECUBE( "imagecube", "IMAGECUBE" );
		static const Rule IIMAGECUBE( "iimagecube", "IIMAGECUBE" );
		static const Rule UIMAGECUBE( "uimagecube", "UIMAGECUBE" );
		static const Rule IMAGEBUFFER( "imagebuffer", "IMAGEBUFFER" );
		static const Rule IIMAGEBUFFER( "iimagebuffer", "IIMAGEBUFFER" );
		static const Rule UIMAGEBUFFER( "uimagebuffer", "UIMAGEBUFFER" );
		static const Rule IMAGE1DARRAY( "image1darray", "IMAGE1DARRAY" );
		static const Rule IIMAGE1DARRAY( "iimage1darray", "IIMAGE1DARRAY" );
		static const Rule UIMAGE1DARRAY( "uimage1darray", "UIMAGE1DARRAY" );
		static const Rule IMAGE2DARRAY( "image2darray", "IMAGE2DARRAY" );
		static const Rule IIMAGE2DARRAY( "iimage2darray", "IIMAGE2DARRAY" );
		static const Rule UIMAGE2DARRAY( "uimage2darray", "UIMAGE2DARRAY" );
		static const Rule IMAGECUBEARRAY( "imagecubearray", "IMAGECUBEARRAY" );
		static const Rule IIMAGECUBEARRAY( "iimagecubearray", "IIMAGECUBEARRAY" );
		static const Rule UIMAGECUBEARRAY( "uimagecubearray", "UIMAGECUBEARRAY" );
		static const Rule IMAGE2DMS( "image2dms", "IMAGE2DMS" );
		static const Rule IIMAGE2DMS( "iimage2dms", "IIMAGE2DMS" );
		static const Rule UIMAGE2DMS( "uimage2dms", "UIMAGE2DMS" );
		static const Rule IMAGE2DMSARRAY( "image2dmsarray", "IMAGE2DMSARRAY" );
		static const Rule IIMAGE2DMSARRAY( "iimage2dmsarray", "IIMAGE2DMSARRAY" );
		static const Rule UIMAGE2DMSARRAY( "uimage2dmsarray", "UIMAGE2DMSARRAY" );

		static const Rule STRUCT( "struct", "STRUCT" );
		static const Rule HIGH_PRECISION( "highp", "HIGH_PRECISION" );
		static const Rule MEDIUM_PRECISION( "mediump", "MEDIUM_PRECISION" );
		static const Rule LOW_PRECISION( "lowp", "LOW_PRECISION" );
		static const Rule DISCARD( "discard", "DISCARD" );
		static const Rule CONST( "const", "CONST" );
		static const Rule INOUT( "inout", "INOUT" );
		static const Rule IN( "in", "IN" );
		static const Rule OUT( "out", "OUT" );
		static const Rule CENTROID( "centroid", "CENTROID" );
		static const Rule PATCH( "patch", "PATCH" );
		static const Rule SAMPLE( "sample", "SAMPLE" );
		static const Rule UNIFORM( "uniform", "UNIFORM" );
		static const Rule BUFFER( "buffer", "BUFFER" );
		static const Rule SHARED( "shared", "SHARED" );
		static const Rule COHERENT( "coherent", "COHERENT" );
		static const Rule VOLATILE( "volatile", "VOLATILE" );
		static const Rule RESTRICT( "restrict", "RESTRICT" );
		static const Rule READONLY( "readonly", "READONLY" );
		static const Rule WRITEONLY( "writeonly", "WRITEONLY" );
		static const Rule SUBROUTINE( "subroutine", "SUBROUTINE" );
		static const Rule INVARIANT( "invariant", "INVARIANT" );
		static const Rule SMOOTH( "smooth", "SMOOTH" );
		static const Rule FLAT( "flat", "FLAT" );
		static const Rule NOPERSPECTIVE( "noperspective", "NOPERSPECTIVE" );
		static const Rule LAYOUT( "layout", "LAYOUT" );
		static const Rule PRECISE( "precise", "PRECISE" );
		static const Rule PRECISION( "precision", "PRECISION" );
	}

	CGlslGrammar::CGlslGrammar()
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

		type_qualifier = ( single_type_qualifier.alias() >> -type_qualifier )[on_rule( "type_qualifier", "single_type_qualifier.alias()", "-type_qualifier" )];
		type_qualifier.name( "type_qualifier" );

		fully_specified_type = ( -type_qualifier >> type_specifier.alias() )[on_rule( "fully_specified_type", "-type_qualifier", "type_specifier.alias" )];
		fully_specified_type.name( "fully_specified_type" );

		array_specifier = ( LEFT_BRACKET >> -constant_expression >> RIGHT_BRACKET >> -array_specifier )[on_rule( "array_specifier", "LEFT_BRACKET", "-constant_expression", "RIGHT_BRACKET", "-array_specifier" )];
		array_specifier.name( "array_specifier" );

		function_header = ( fully_specified_type >> identifier >> LEFT_PAREN )[on_rule( "function_header", "identifier", "fully_specified_type", "LEFT_PAREN" )];
		function_header.name( "function_header" );

		parameter_declarator = ( type_specifier.alias() >> identifier >> -array_specifier )[on_rule( "parameter_declarator", "type_specifier", "identifier", "-array_specifier" )];
		parameter_declarator.name( "parameter_declarator" );

		parameter_type_specifier = type_specifier.alias();
		parameter_type_specifier.name( "parameter_type_specifier" );

		parameter_declaration = ( -type_qualifier >> ( parameter_declarator | parameter_type_specifier ) )[on_rule( "parameter_declaration", "-type_qualifier", "( parameter_declarator | parameter_type_specifier )" )];
		parameter_declaration.name( "parameter_declaration" );

		function_header_with_parameters = function_header[on_rule( "function_header_with_parameters", "function_header" )];
		function_header_with_parameters.name( "function_header_with_parameters" );

		function_declarator = ( function_header >> -( parameter_declaration >> *( COMMA >> parameter_declaration ) ) )[on_rule( "function_header_with_parameters", "function_header", "-( parameter_declaration *( COMMA parameter_declaration ) )" )];
		function_declarator.name( "function_declarator" );

		function_prototype = ( function_declarator >> RIGHT_PAREN )[on_rule( "function_prototype", "function_declarator", "RIGHT_PAREN" )];
		function_prototype.name( "function_prototype" );

		identifier_list = ( identifier >> *( COMMA >> identifier ) )[on_rule( "identifier_list", "*( COMMA identifier )" )];
		identifier_list.name( "identifier_list" );

		initializer = assignment_expression[on_rule( "initializer", "assignment_expression" )]
			| ( LEFT_BRACE >> initializer_list.alias() >> -COMMA >> RIGHT_BRACE )[on_rule( "initializer", "LEFT_BRACE", "initializer_list.alias()", "-COMMA", "RIGHT_BRACE" )];
		initializer.name( "initializer" );

		fully_specified_type = ( -type_qualifier >> type_specifier.alias() )[on_rule( "fully_specified_type", "-type_qualifier", "type_specifier.alias()" )];
		fully_specified_type.name( "fully_specified_type" );

		declaration_identifier = ( identifier >> -array_specifier >> -( EQUAL >> initializer ) )[on_rule( "declaration_identifier", "identifier", "-array_specifier", "-( EQUAL initializer )" )];
		declaration_identifier.name( "declaration_identifier" );

		single_declaration = ( fully_specified_type >> -declaration_identifier )[on_rule( "single_declaration", "fully_specified_type", "-declaration_identifier" )];
		single_declaration.name( "single_declaration" );

		init_declarator_list = ( single_declaration >> *( COMMA >> declaration_identifier ) )[on_rule( "init_declarator_list", "single_declaration", "*( COMMA >> declaration_identifier )" )];
		init_declarator_list.name( "init_declarator_list" );

		precision_qualifier = HIGH_PRECISION[on_rule( "precision_qualifier", "HIGH_PRECISION" )]
			| MEDIUM_PRECISION[on_rule( "precision_qualifier", "MEDIUM_PRECISION" )]
			| LOW_PRECISION[on_rule( "precision_qualifier", "LOW_PRECISION" )];
		precision_qualifier.name( "precision_qualifier" );

		declaration = ( function_prototype >> SEMICOLON )[on_rule( "declaration", "function_prototype", "SEMICOLON" )]
			| ( init_declarator_list >> SEMICOLON )[on_rule( "declaration", "init_declarator_list", "SEMICOLON" )]
			| ( PRECISION >> precision_qualifier >> type_specifier.alias() >> SEMICOLON )[on_rule( "declaration", "PRECISION", "precision_qualifier", "type_specifier.alias()", "SEMICOLON" )]
			| ( type_qualifier >> identifier >> LEFT_BRACE >> struct_declaration_list.alias() >> RIGHT_BRACE >> -SEMICOLON )[on_rule( "declaration", "type_qualifier", "identifier", "LEFT_BRACE", "struct_declaration_list.alias()", "RIGHT_BRACE", "-SEMICOLON" )]
			| ( identifier >> -array_specifier >> SEMICOLON )[on_rule( "declaration", "identifier", "-array_specifier", "SEMICOLON" )]
			| ( type_qualifier >> -identifier_list >> SEMICOLON )[on_rule( "declaration", "type_qualifier", "-identifier_list", "SEMICOLON" )];
		declaration.name( "declaration" );

		invariant_qualifier = INVARIANT[on_rule( "invariant_qualifier", "INVARIANT" )];
		invariant_qualifier.name( "invariant_qualifier" );

		interpolation_qualifier = SMOOTH[on_rule( "interpolation_qualifier", "SMOOTH" )]
			| FLAT[on_rule( "interpolation_qualifier", "FLAT" )]
			| NOPERSPECTIVE[on_rule( "interpolation_qualifier", "NOPERSPECTIVE" )];
		interpolation_qualifier.name( "interpolation_qualifier" );

		layout_qualifier_id = ( identifier >> -( EQUAL >> constant_expression ) )[on_rule( "declaration", "identifier", "-( EQUAL  constant_expression )" )]
			| SHARED[on_rule( "layout_qualifier_id", "SHARED" )];
		layout_qualifier_id.name( "layout_qualifier_id" );

		layout_qualifier_id_list = ( layout_qualifier_id >> *( COMMA >> layout_qualifier_id ) )[on_rule( "layout_qualifier_id_list", "layout_qualifier_id", "*( COMMA layout_qualifier_id )" )];
		layout_qualifier_id_list.name( "layout_qualifier_id_list" );

		layout_qualifier = ( LAYOUT >> LEFT_PAREN >> layout_qualifier_id_list >> RIGHT_PAREN )[on_rule( "layout_qualifier", "LAYOUT", "LEFT_PAREN", "layout_qualifier_id_list", "RIGHT_PAREN" )];
		layout_qualifier.name( "layout_qualifier" );

		precise_qualifier = PRECISE[on_rule( "precise_qualifier", "PRECISE" )];
		precise_qualifier.name( "precise_qualifier" );

		type_name_list = ( type_name >> *( COMMA >> type_name ) )[on_rule( "type_name_list", "type_name", "*( COMMA type_name )" )];
		type_name_list.name( "type_name_list" );

		storage_qualifier = CONST[on_rule( "storage_qualifier", "type_specifier_nonarray" )]
			| INOUT[on_rule( "storage_qualifier", "INOUT" )]
			| IN[on_rule( "storage_qualifier", "IN" )]
			| OUT[on_rule( "storage_qualifier", "OUT" )]
			| CENTROID[on_rule( "storage_qualifier", "CENTROID" )]
			| PATCH[on_rule( "storage_qualifier", "PATCH" )]
			| SAMPLE[on_rule( "storage_qualifier", "SAMPLE" )]
			| UNIFORM[on_rule( "storage_qualifier", "UNIFORM" )]
			| BUFFER[on_rule( "storage_qualifier", "BUFFER" )]
			| SHARED[on_rule( "storage_qualifier", "SHARED" )]
			| COHERENT[on_rule( "storage_qualifier", "COHERENT" )]
			| VOLATILE[on_rule( "storage_qualifier", "VOLATILE" )]
			| RESTRICT[on_rule( "storage_qualifier", "RESTRICT" )]
			| READONLY[on_rule( "storage_qualifier", "READONLY" )]
			| WRITEONLY[on_rule( "storage_qualifier", "WRITEONLY" )]
			| ( SUBROUTINE >> -( LEFT_PAREN >> type_name_list >> RIGHT_PAREN ) )[on_rule( "storage_qualifier", "SUBROUTINE", "-( LEFT_PAREN type_name_list RIGHT_PAREN )" )];
		storage_qualifier.name( "storage_qualifier" );

		type_specifier = ( type_specifier_nonarray.alias() >> -array_specifier )[on_rule( "type_specifier", "type_specifier_nonarray.alias()", "-array_specifier" )];
		type_specifier.name( "type_specifier" );

		single_type_qualifier = storage_qualifier[on_rule( "single_type_qualifier", "storage_qualifier" )]
			| layout_qualifier[on_rule( "single_type_qualifier", "layout_qualifier" )]
			| precision_qualifier[on_rule( "single_type_qualifier", "precision_qualifier" )]
			| interpolation_qualifier[on_rule( "single_type_qualifier", "interpolation_qualifier" )]
			| invariant_qualifier[on_rule( "single_type_qualifier", "invariant_qualifier" )]
			| precise_qualifier[on_rule( "single_type_qualifier", "precise_qualifier" )];
		single_type_qualifier.name( "single_type_qualifier" );

		struct_declarator = identifier[on_rule( "struct_declarator", "identifier" )]
			| ( identifier >> array_specifier )[on_rule( "single_type_qualifier", "identifier", "array_specifier" )];
		struct_declarator.name( "struct_declarator" );

		struct_declarator_list = ( struct_declarator >> *( COMMA >> struct_declarator ) )[on_rule( "struct_declarator_list", "struct_declarator", "*( COMMA >> struct_declarator )" )];
		struct_declarator_list.name( "struct_declarator_list" );

		struct_declaration = ( -type_qualifier >> type_specifier >> struct_declarator_list >> SEMICOLON )[on_rule( "struct_declaration", "-type_qualifier", "type_specifier", "struct_declarator_list", "SEMICOLON" )];
		struct_declaration.name( "struct_declaration" );

		struct_declaration_list = ( +struct_declaration )[on_rule( "struct_declaration_list", "+struct_declaration" )];
		struct_declaration_list.name( "struct_declaration_list" );

		struct_specifier = ( STRUCT >> -identifier >> LEFT_BRACE >> struct_declaration_list >> RIGHT_BRACE )[on_rule( "struct_specifier", "STRUCT", "-identifier", "LEFT_BRACE", "struct_declaration_list", "RIGHT_BRACE" )];
		struct_specifier.name( "struct_specifier" );

		base_type_specifier = VOID
			| FLOAT
			| DOUBLE
			| INT
			| UINT
			| BOOL;
		base_type_specifier.name( "base_type_specifier" );

		vec_specifier = VEC2
			| VEC3
			| VEC4
			| DVEC2
			| DVEC3
			| DVEC4
			| BVEC2
			| BVEC3
			| BVEC4
			| IVEC2
			| IVEC3
			| IVEC4
			| UVEC2
			| UVEC3
			| UVEC4;
		vec_specifier.name( "vec_specifier" );

		mat_specifier = MAT2
			| MAT3
			| MAT4
			| MAT2X2
			| MAT2X3
			| MAT2X4
			| MAT3X2
			| MAT3X3
			| MAT3X4
			| MAT4X2
			| MAT4X3
			| MAT4X4
			| DMAT2
			| DMAT3
			| DMAT4
			| DMAT2X2
			| DMAT2X3
			| DMAT2X4
			| DMAT3X2
			| DMAT3X3
			| DMAT3X4
			| DMAT4X2
			| DMAT4X3
			| DMAT4X4;
		mat_specifier.name( "mat_specifier" );

		fsampler_specifier = SAMPLER1D
			| SAMPLER2D
			| SAMPLER3D
			| SAMPLERCUBE
			| SAMPLER1DSHADOW
			| SAMPLER2DSHADOW
			| SAMPLERCUBESHADOW
			| SAMPLER1DARRAY
			| SAMPLER2DARRAY
			| SAMPLER1DARRAYSHADOW
			| SAMPLER2DARRAYSHADOW
			| SAMPLERCUBEARRAY
			| SAMPLERCUBEARRAYSHADOW
			| SAMPLER2DRECT
			| SAMPLER2DRECTSHADOW
			| SAMPLER2DMS;
		fsampler_specifier.name( "fsampler_specifier" );

		isampler_specifier = ISAMPLER1D
			| ISAMPLER2D
			| ISAMPLER3D
			| ISAMPLERCUBE
			| ISAMPLER1DARRAY
			| ISAMPLER2DARRAY
			| ISAMPLERCUBEARRAY
			| ISAMPLER2DRECT
			| ISAMPLERBUFFER
			| ISAMPLER2DMS
			| ISAMPLER2DMSARRAY;
		isampler_specifier.name( "isampler_specifier" );

		usampler_specifier = USAMPLER1D
			| USAMPLER2D
			| USAMPLER3D
			| USAMPLERCUBE
			| USAMPLER1DARRAY
			| USAMPLER2DARRAY
			| USAMPLERCUBEARRAY
			| USAMPLER2DRECT
			| SAMPLERBUFFER
			| USAMPLERBUFFER
			| USAMPLER2DMS
			| SAMPLER2DMSARRAY
			| USAMPLER2DMSARRAY;
		usampler_specifier.name( "usampler_specifier" );

		image_specifier = IMAGE1D
			| IMAGE2D
			| IMAGE3D
			| IMAGE2DRECT
			| IMAGECUBE
			| IMAGEBUFFER
			| IMAGE1DARRAY
			| IMAGE2DARRAY
			| IMAGECUBEARRAY
			| IMAGE2DMS
			| IMAGE2DMSARRAY;
		image_specifier.name( "image_specifier" );

		iimage_specifier = IIMAGE1D
			| IIMAGE2D
			| IIMAGE3D
			| IIMAGE2DRECT
			| IIMAGECUBE
			| IIMAGEBUFFER
			| IIMAGE1DARRAY
			| IIMAGE2DARRAY
			| IIMAGECUBEARRAY
			| IIMAGE2DMS
			| IIMAGE2DMSARRAY;
		iimage_specifier.name( "iimage_specifier" );

		uimage_specifier = UIMAGE1D
			| UIMAGE2D
			| UIMAGE3D
			| UIMAGE2DRECT
			| UIMAGECUBE
			| UIMAGEBUFFER
			| UIMAGE1DARRAY
			| UIMAGE2DARRAY
			| UIMAGECUBEARRAY
			| UIMAGE2DMS
			| UIMAGE2DMSARRAY;
		uimage_specifier.name( "uimage_specifier" );

		type_specifier_nonarray = base_type_specifier
			| vec_specifier
			| mat_specifier
			| ATOMIC_UINT
			| fsampler_specifier
			| isampler_specifier
			| usampler_specifier
			| image_specifier
			| iimage_specifier
			| uimage_specifier
			| struct_specifier
			| type_name;
		type_specifier_nonarray.name( "type_specifier_nonarray" );

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

		statement_list = +statement[on_rule( "statement_list", "+statement" )];
		statement_list.name( "statement_list" );

		expression_statement = ( -expression >> SEMICOLON )[on_rule( "expression_statement", "-expression", "SEMICOLON" )];
		expression_statement.name( "expression_statement" );

		selection_rest_statement = ( statement >> -( ELSE >> statement ) )[on_rule( "selection_rest_statement", "statement", "-( ELSE statement )" )];
		selection_rest_statement.name( "selection_rest_statement" );

		selection_statement = ( IF >> LEFT_PAREN >> expression >> RIGHT_PAREN >> selection_rest_statement )[on_rule( "selection_statement", "IF", "LEFT_PAREN", "expression", "selection_rest_statement )" )];
		selection_statement.name( "selection_statement" );

		condition = expression[on_rule( "condition", "expression" )]
			| ( fully_specified_type >> identifier >> EQUAL >> initializer )[on_rule( "condition", "fully_specified_type", "identifier", "EQUAL", "initializer )" )];
		condition.name( "condition" );

		case_label = ( ( ( CASE >> expression ) | DEFAULT ) >> COLON )[on_rule( "case_label", "( ( CASE >> expression ) | DEFAULT )", "COLON" )];
		case_label.name( "case_label" );

		switch_statement_list = ( -statement_list )[on_rule( "switch_statement_list", "-statement_list" )];
		switch_statement_list.name( "switch_statement_list" );

		switch_statement = ( SWITCH >> LEFT_PAREN >> expression >> RIGHT_PAREN >> LEFT_BRACE >> switch_statement_list >> RIGHT_BRACE )[on_rule( "switch_statement", "SWITCH", "LEFT_PAREN", "expression", "RIGHT_PAREN", "LEFT_BRACE", "switch_statement_list", "RIGHT_BRACE" )];
		switch_statement.name( "switch_statement" );

		for_init_statement = expression_statement[on_rule( "for_init_statement", "expression_statement" )]
			| declaration_statement[on_rule( "for_init_statement", "declaration_statement" )];
		for_init_statement.name( "for_init_statement" );

		for_rest_statement = ( -condition >> SEMICOLON >> -expression )[on_rule( "for_rest_statement", "-condition", "SEMICOLON", "-expression" )];
		for_rest_statement.name( "for_rest_statement" );

		iteration_statement = ( WHILE >> LEFT_PAREN >> condition >> RIGHT_PAREN >> statement_no_new_scope )[on_rule( "iteration_statement", "WHILE", "LEFT_PAREN", "condition", "RIGHT_PAREN", "statement_no_new_scope" )]
			| ( DO >> statement >> WHILE >> LEFT_PAREN >> expression >> RIGHT_PAREN >> SEMICOLON )[on_rule( "iteration_statement", "DO", "statement", "WHILE", "LEFT_PAREN", "expression", "RIGHT_PAREN", "SEMICOLON" )]
			| ( FOR >> LEFT_PAREN >> for_init_statement >> for_rest_statement >> RIGHT_PAREN )[on_rule( "iteration_statement", "FOR", "LEFT_PAREN", "for_init_statement", "for_rest_statement", "RIGHT_PAREN" )]
			| statement_no_new_scope[on_rule( "iteration_statement", "statement_no_new_scope" )];
		iteration_statement.name( "iteration_statement" );

		jump_statement = ( CONTINUE | BREAK | ( RETURN >> -expression ) | DISCARD ) >> SEMICOLON;
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
END_NAMESPACE_GLSL_PARSER
