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
		static const Rule LEFT_ANGLE = '<';
		static const Rule RIGHT_ANGLE = '>';
		static const Rule LEFT_PAREN = '(';
		static const Rule RIGHT_PAREN = ')';
		static const Rule LEFT_BRACKET = '[';
		static const Rule RIGHT_BRACKET = ']';
		static const Rule LEFT_BRACE = '{';
		static const Rule RIGHT_BRACE = '}';
		static const Rule AMPERSAND = '&';
		static const Rule CARET = '^';
		static const Rule VERTICAL_BAR = '|';
		static const Rule QUESTION = '?';
		static const Rule EQUAL = '=';
		static const Rule COLON = ':';
		static const Rule COMMA = ',';
		static const Rule DOT = '.';
		static const Rule SEMICOLON = ';';
		static const Rule BANG = '!';
		static const Rule PLUS = '+';
		static const Rule DASH = '-';
		static const Rule TILDE = '~';
		static const Rule STAR = '*';
		static const Rule SLASH = '/';
		static const Rule PERCENT = '%';

		static const Rule LEFT_OP = "<<";
		static const Rule RIGHT_OP = ">>";
		static const Rule LE_OP = "<=";
		static const Rule GE_OP = ">=";
		static const Rule EQ_OP = "==";
		static const Rule NE_OP = "!=";
		static const Rule AND_OP = "&&";
		static const Rule OR_OP = "||";
		static const Rule XOR_OP = "^^";
		static const Rule MUL_ASSIGN = "*=";
		static const Rule DIV_ASSIGN = "/=";
		static const Rule MOD_ASSIGN = "%=";
		static const Rule ADD_ASSIGN = "+=";
		static const Rule SUB_ASSIGN = "-=";
		static const Rule LEFT_ASSIGN = "<<=";
		static const Rule RIGHT_ASSIGN = ">>=";
		static const Rule AND_ASSIGN = "&=";
		static const Rule XOR_ASSIGN = "^=";
		static const Rule OR_ASSIGN = "|=";
		static const Rule INC_OP = "++";
		static const Rule DEC_OP = "--";

		static const Rule VOID = "void";
		static const Rule FLOAT = "float";
		static const Rule DOUBLE = "double";
		static const Rule INT = "int";
		static const Rule UINT = "uint";
		static const Rule BOOL = "bool";
		static const Rule VEC2 = "vec2";
		static const Rule VEC3 = "vec3";
		static const Rule VEC4 = "vec4";
		static const Rule DVEC2 = "dvec2";
		static const Rule DVEC3 = "dvec3";
		static const Rule DVEC4 = "dvec4";
		static const Rule BVEC2 = "bvec2";
		static const Rule BVEC3 = "bvec3";
		static const Rule BVEC4 = "bvec4";
		static const Rule IVEC2 = "ivec2";
		static const Rule IVEC3 = "ivec3";
		static const Rule IVEC4 = "ivec4";
		static const Rule UVEC2 = "uvec2";
		static const Rule UVEC3 = "uvec3";
		static const Rule UVEC4 = "uvec4";
		static const Rule MAT2 = "mat2";
		static const Rule MAT3 = "mat3";
		static const Rule MAT4 = "mat4";
		static const Rule MAT2X2 = "mat2x2";
		static const Rule MAT2X3 = "mat2x3";
		static const Rule MAT2X4 = "mat2x4";
		static const Rule MAT3X2 = "mat3x2";
		static const Rule MAT3X3 = "mat3x3";
		static const Rule MAT3X4 = "mat3x4";
		static const Rule MAT4X2 = "mat4x2";
		static const Rule MAT4X3 = "mat4x3";
		static const Rule MAT4X4 = "mat4x4";
		static const Rule DMAT2 = "dmat2";
		static const Rule DMAT3 = "dmat3";
		static const Rule DMAT4 = "dmat4";
		static const Rule DMAT2X2 = "dmat2x2";
		static const Rule DMAT2X3 = "dmat2x3";
		static const Rule DMAT2X4 = "dmat2x4";
		static const Rule DMAT3X2 = "dmat3x2";
		static const Rule DMAT3X3 = "dmat3x3";
		static const Rule DMAT3X4 = "dmat3x4";
		static const Rule DMAT4X2 = "dmat4x2";
		static const Rule DMAT4X3 = "dmat4x3";
		static const Rule DMAT4X4 = "dmat4x4";
		static const Rule ATOMIC_UINT = "atomic_uint";
		static const Rule SAMPLER1D = "sampler1d";
		static const Rule SAMPLER2D = "sampler2d";
		static const Rule SAMPLER3D = "sampler3d";
		static const Rule SAMPLERCUBE = "samplercube";
		static const Rule SAMPLER1DSHADOW = "sampler1dshadow";
		static const Rule SAMPLER2DSHADOW = "sampler2dshadow";
		static const Rule SAMPLERCUBESHADOW = "samplercubeshadow";
		static const Rule SAMPLER1DARRAY = "sampler1darray";
		static const Rule SAMPLER2DARRAY = "sampler2darray";
		static const Rule SAMPLER1DARRAYSHADOW = "sampler1darrayshadow";
		static const Rule SAMPLER2DARRAYSHADOW = "sampler2darrayshadow";
		static const Rule SAMPLERCUBEARRAY = "samplercubearray";
		static const Rule SAMPLERCUBEARRAYSHADOW = "samplercubearrayshadow";
		static const Rule ISAMPLER1D = "isampler1d";
		static const Rule ISAMPLER2D = "isampler2d";
		static const Rule ISAMPLER3D = "isampler3d";
		static const Rule ISAMPLERCUBE = "isamplercube";
		static const Rule ISAMPLER1DARRAY = "isampler1darray";
		static const Rule ISAMPLER2DARRAY = "isampler2darray";
		static const Rule ISAMPLERCUBEARRAY = "isamplercubearray";
		static const Rule USAMPLER1D = "usampler1d";
		static const Rule USAMPLER2D = "usampler2d";
		static const Rule USAMPLER3D = "usampler3d";
		static const Rule USAMPLERCUBE = "usamplercube";
		static const Rule USAMPLER1DARRAY = "usampler1darray";
		static const Rule USAMPLER2DARRAY = "usampler2darray";
		static const Rule USAMPLERCUBEARRAY = "usamplercubearray";
		static const Rule SAMPLER2DRECT = "sampler2drect";
		static const Rule SAMPLER2DRECTSHADOW = "sampler2drectshadow";
		static const Rule ISAMPLER2DRECT = "isampler2drect";
		static const Rule USAMPLER2DRECT = "usampler2drect";
		static const Rule SAMPLERBUFFER = "samplerbuffer";
		static const Rule ISAMPLERBUFFER = "isamplerbuffer";
		static const Rule USAMPLERBUFFER = "usamplerbuffer";
		static const Rule SAMPLER2DMS = "sampler2dms";
		static const Rule ISAMPLER2DMS = "isampler2dms";
		static const Rule USAMPLER2DMS = "usampler2dms";
		static const Rule SAMPLER2DMSARRAY = "sampler2dmsarray";
		static const Rule ISAMPLER2DMSARRAY = "isampler2dmsarray";
		static const Rule USAMPLER2DMSARRAY = "usampler2dmsarray";
		static const Rule IMAGE1D = "image1d";
		static const Rule IIMAGE1D = "iimage1d";
		static const Rule UIMAGE1D = "uimage1d";
		static const Rule IMAGE2D = "image2d";
		static const Rule IIMAGE2D = "iimage2d";
		static const Rule UIMAGE2D = "uimage2d";
		static const Rule IMAGE3D = "image3d";
		static const Rule IIMAGE3D = "iimage3d";
		static const Rule UIMAGE3D = "uimage3d";
		static const Rule IMAGE2DRECT = "image2drect";
		static const Rule IIMAGE2DRECT = "iimage2drect";
		static const Rule UIMAGE2DRECT = "uimage2drect";
		static const Rule IMAGECUBE = "imagecube";
		static const Rule IIMAGECUBE = "iimagecube";
		static const Rule UIMAGECUBE = "uimagecube";
		static const Rule IMAGEBUFFER = "imagebuffer";
		static const Rule IIMAGEBUFFER = "iimagebuffer";
		static const Rule UIMAGEBUFFER = "uimagebuffer";
		static const Rule IMAGE1DARRAY = "image1darray";
		static const Rule IIMAGE1DARRAY = "iimage1darray";
		static const Rule UIMAGE1DARRAY = "uimage1darray";
		static const Rule IMAGE2DARRAY = "image2darray";
		static const Rule IIMAGE2DARRAY = "iimage2darray";
		static const Rule UIMAGE2DARRAY = "uimage2darray";
		static const Rule IMAGECUBEARRAY = "imagecubearray";
		static const Rule IIMAGECUBEARRAY = "iimagecubearray";
		static const Rule UIMAGECUBEARRAY = "uimagecubearray";
		static const Rule IMAGE2DMS = "image2dms";
		static const Rule IIMAGE2DMS = "iimage2dms";
		static const Rule UIMAGE2DMS = "uimage2dms";
		static const Rule IMAGE2DMSARRAY = "image2dmsarray";
		static const Rule IIMAGE2DMSARRAY = "iimage2dmsarray";
		static const Rule UIMAGE2DMSARRAY = "uimage2dmsarray";

		static const Rule STRUCT = "struct";
		static const Rule HIGH_PRECISION = "highp";
		static const Rule MEDIUM_PRECISION = "mediump";
		static const Rule LOW_PRECISION = "lowp";
		static const Rule ELSE = "else";
		static const Rule IF = "if";
		static const Rule CASE = "case";
		static const Rule DEFAULT = "default";
		static const Rule SWITCH = "switch";
		static const Rule WHILE = "while";
		static const Rule DO = "do";
		static const Rule FOR = "for";
		static const Rule CONTINUE = "continue";
		static const Rule BREAK = "break";
		static const Rule RETURN = "return";
		static const Rule DISCARD = "discard";
		static const Rule CONST = "const";
		static const Rule INOUT = "inout";
		static const Rule IN = "in";
		static const Rule OUT = "out";
		static const Rule CENTROID = "centroid";
		static const Rule PATCH = "patch";
		static const Rule SAMPLE = "sample";
		static const Rule UNIFORM = "uniform";
		static const Rule BUFFER = "buffer";
		static const Rule SHARED = "shared";
		static const Rule COHERENT = "coherent";
		static const Rule VOLATILE = "volatile";
		static const Rule RESTRICT = "restrict";
		static const Rule READONLY = "readonly";
		static const Rule WRITEONLY = "writeonly";
		static const Rule SUBROUTINE = "subroutine";
		static const Rule INVARIANT = "invariant";
		static const Rule SMOOTH = "smooth";
		static const Rule FLAT = "flat";
		static const Rule NOPERSPECTIVE = "noperspective";
		static const Rule LAYOUT = "layout";
		static const Rule PRECISE = "precise";
		static const Rule PRECISION = "precision";
	}

	CGlslGrammar::CGlslGrammar()
	{
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

		variable_identifier = identifier;

		field_selection = identifier;

		function_call_header = function_identifier >> LEFT_PAREN;

		function_call_header_no_parameters = function_call_header >> VOID
			| function_call_header;

		function_call_header_with_parameters = function_call_header >> assignment_expression
			| function_call_header_with_parameters >> COMMA >> assignment_expression;

		function_call_generic = function_call_header_with_parameters >> RIGHT_PAREN
			| function_call_header_no_parameters >> RIGHT_PAREN;

		function_call_or_method = function_call_generic;

		function_call = function_call_or_method;

		integer_expression = expression;
	
		postfix_expression = primary_expression
			| postfix_expression >> LEFT_BRACKET >> integer_expression >> RIGHT_BRACKET
			| function_call
			| postfix_expression >> DOT >> field_selection
			| postfix_expression >> INC_OP
			| postfix_expression >> DEC_OP;

		function_identifier = type_specifier
			| postfix_expression;

		unary_expression = postfix_expression
			| INC_OP >> unary_expression
			| DEC_OP >> unary_expression
			| unary_operator >> unary_expression;

		unary_operator = PLUS
			| DASH
			| BANG
			| TILDE;

		multiplicative_expression = unary_expression
			| multiplicative_expression >> STAR >> unary_expression
			| multiplicative_expression >> SLASH >> unary_expression
			| multiplicative_expression >> PERCENT >> unary_expression;

		additive_expression = multiplicative_expression
			| additive_expression >> PLUS >> multiplicative_expression
			| additive_expression >> DASH >> multiplicative_expression;

		shift_expression = additive_expression
			| shift_expression >> LEFT_OP >> additive_expression
			| shift_expression >> RIGHT_OP >> additive_expression;

		relational_expression = shift_expression
			| relational_expression >> LEFT_ANGLE >> shift_expression
			| relational_expression >> RIGHT_ANGLE >> shift_expression
			| relational_expression >> LE_OP >> shift_expression
			| relational_expression >> GE_OP >> shift_expression;

		equality_expression = relational_expression
			| equality_expression >> EQ_OP >> relational_expression
			| equality_expression >> NE_OP >> relational_expression;

		and_expression = equality_expression
			| and_expression >> AMPERSAND >> equality_expression;

		exclusive_or_expression = and_expression
			| exclusive_or_expression >> CARET >> and_expression;

		inclusive_or_expression = exclusive_or_expression
			| inclusive_or_expression >> VERTICAL_BAR >> exclusive_or_expression;

		logical_and_expression = inclusive_or_expression
			| logical_and_expression >> AND_OP >> inclusive_or_expression;

		logical_xor_expression = logical_and_expression
			| logical_xor_expression >> XOR_OP >> logical_and_expression;

		logical_or_expression = logical_xor_expression
			| logical_or_expression >> OR_OP >> logical_xor_expression;

		conditional_expression = logical_or_expression
			| logical_or_expression >> QUESTION >> expression >> COLON >> assignment_expression;

		assignment_operator = EQUAL
			| MUL_ASSIGN
			| DIV_ASSIGN
			| MOD_ASSIGN
			| ADD_ASSIGN
			| SUB_ASSIGN
			| LEFT_ASSIGN
			| RIGHT_ASSIGN
			| AND_ASSIGN
			| XOR_ASSIGN
			| OR_ASSIGN;

		assignment_expression = conditional_expression
			| unary_expression >> assignment_operator >> assignment_expression;

		expression = assignment_expression >> *( COMMA >> assignment_expression );

		primary_expression = variable_identifier
			| integer_constant
			| uinteger_constant
			| floating_constant
			| bool_constant
			| double_constant
			| LEFT_PAREN >> expression >> RIGHT_PAREN;
	
		constant_expression = conditional_expression;

		type_qualifier = single_type_qualifier
			| type_qualifier >> single_type_qualifier;

		fully_specified_type = type_specifier
			| type_qualifier >> type_specifier;

		array_specifier = LEFT_BRACKET >> RIGHT_BRACKET
			| LEFT_BRACKET >> constant_expression >> RIGHT_BRACKET
			| array_specifier >> LEFT_BRACKET >> RIGHT_BRACKET
			| array_specifier >> LEFT_BRACKET >> constant_expression >> RIGHT_BRACKET;

		function_header = fully_specified_type >> identifier >> LEFT_PAREN;

		parameter_declarator = type_specifier >> identifier
			| type_specifier >> identifier >> array_specifier;

		parameter_type_specifier = type_specifier;

		parameter_declaration = type_qualifier >> parameter_declarator
			| parameter_declarator
			| type_qualifier >> parameter_type_specifier
			| parameter_type_specifier;

		function_header_with_parameters = function_header >> parameter_declaration
			| function_header_with_parameters >> COMMA >> parameter_declaration;

		function_declarator = function_header
			| function_header_with_parameters;

		function_prototype = function_declarator >> RIGHT_PAREN;

		identifier_list = COMMA >> identifier
			| identifier_list >> COMMA >> identifier;

		initializer = assignment_expression
			| LEFT_BRACE >> initializer_list >> RIGHT_BRACE
			| LEFT_BRACE >> initializer_list >> COMMA >> RIGHT_BRACE;

		fully_specified_type = type_specifier
			| type_qualifier >> type_specifier;

		single_declaration = fully_specified_type
			| fully_specified_type >> identifier
			| fully_specified_type >> identifier >> array_specifier
			| fully_specified_type >> identifier >> array_specifier >> EQUAL >> initializer
			| fully_specified_type >> identifier >> EQUAL >> initializer;

		init_declarator_list = single_declaration
			| init_declarator_list >> COMMA >> identifier
			| init_declarator_list >> COMMA >> identifier >> array_specifier
			| init_declarator_list >> COMMA >> identifier >> array_specifier >> EQUAL >> initializer
			| init_declarator_list >> COMMA >> identifier >> EQUAL >> initializer;

		precision_qualifier = HIGH_PRECISION
			| MEDIUM_PRECISION
			| LOW_PRECISION;

		declaration = function_prototype >> SEMICOLON
			| init_declarator_list >> SEMICOLON
			| PRECISION >> precision_qualifier >> type_specifier >> SEMICOLON
			| type_qualifier >> identifier >> LEFT_BRACE >> struct_declaration_list >> RIGHT_BRACE >> SEMICOLON
			| type_qualifier >> identifier >> LEFT_BRACE >> struct_declaration_list >> RIGHT_BRACE
			| identifier >> SEMICOLON
			| type_qualifier >> identifier >> LEFT_BRACE >> struct_declaration_list >> RIGHT_BRACE
			| identifier >> array_specifier >> SEMICOLON
			| type_qualifier >> SEMICOLON
			| type_qualifier >> identifier >> SEMICOLON
			| type_qualifier >> identifier >> identifier_list >> SEMICOLON;

		invariant_qualifier = INVARIANT;

		interpolation_qualifier = SMOOTH
			| FLAT
			| NOPERSPECTIVE;

		layout_qualifier_id = identifier
			| identifier >> EQUAL >> constant_expression
			| SHARED;

		layout_qualifier_id_list = layout_qualifier_id >> *( COMMA >> layout_qualifier_id );

		layout_qualifier = LAYOUT >> LEFT_PAREN >> layout_qualifier_id_list >> RIGHT_PAREN;

		precise_qualifier = PRECISE;

		type_name_list = type_name
			| type_name_list >> COMMA >> type_name;

		storage_qualifier = CONST
			| INOUT
			| IN
			| OUT
			| CENTROID
			| PATCH
			| SAMPLE
			| UNIFORM
			| BUFFER
			| SHARED
			| COHERENT
			| VOLATILE
			| RESTRICT
			| READONLY
			| WRITEONLY
			| SUBROUTINE
			| SUBROUTINE >> LEFT_PAREN >> type_name_list >> RIGHT_PAREN;

		type_specifier = type_specifier_nonarray
			| type_specifier_nonarray >> array_specifier;

		single_type_qualifier = storage_qualifier
			| layout_qualifier
			| precision_qualifier
			| interpolation_qualifier
			| invariant_qualifier
			| precise_qualifier;

		struct_declarator = identifier
			| identifier >> array_specifier;

		struct_declarator_list = struct_declarator
			| struct_declarator_list >> COMMA >> struct_declarator;

		struct_declaration = type_specifier >> struct_declarator_list >> SEMICOLON
			| type_qualifier >> type_specifier >> struct_declarator_list >> SEMICOLON;

		struct_declaration_list = struct_declaration
			| struct_declaration_list >> struct_declaration;

		struct_specifier = STRUCT >> identifier >> LEFT_BRACE >> struct_declaration_list >> RIGHT_BRACE
			| STRUCT >> LEFT_BRACE >> struct_declaration_list >> RIGHT_BRACE;

		Rule base_type_specifier = VOID
			| FLOAT
			| DOUBLE
			| INT
			| UINT
			| BOOL;

		Rule vec_specifier = VEC2
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

		Rule mat_specifier = MAT2
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

		Rule fsampler_specifier = SAMPLER1D
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

		Rule isampler_specifier = ISAMPLER1D
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

		Rule usampler_specifier = USAMPLER1D
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

		Rule image_specifier = IMAGE1D
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

		Rule iimage_specifier = IIMAGE1D
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

		Rule uimage_specifier = UIMAGE1D
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

		initializer_list = initializer
			| initializer_list >> COMMA >> initializer;

		declaration_statement = declaration;

		compound_statement_no_new_scope = LEFT_BRACE >> RIGHT_BRACE
			| LEFT_BRACE >> statement_list >> RIGHT_BRACE;

		statement_no_new_scope = compound_statement_no_new_scope
			| simple_statement;

		compound_statement = LEFT_BRACE >> -statement_list >> RIGHT_BRACE;

		statement = compound_statement
			| simple_statement;

		statement_list = statement
			| statement_list >> statement;

		expression_statement = SEMICOLON
			| expression >> SEMICOLON;

		selection_rest_statement = statement >> ELSE >> statement
			| statement;

		selection_statement = IF >> LEFT_PAREN >> expression >> RIGHT_PAREN >> selection_rest_statement;

		condition = expression
			| fully_specified_type >> identifier >> EQUAL >> initializer;

		case_label = CASE >> expression >> COLON
			| DEFAULT >> COLON;

		switch_statement_list = -statement_list;

		switch_statement = SWITCH >> LEFT_PAREN >> expression >> RIGHT_PAREN >> LEFT_BRACE >> switch_statement_list
			| RIGHT_BRACE;

		for_init_statement = expression_statement
			| declaration_statement;

		conditionopt = -condition;

		for_rest_statement = conditionopt >> SEMICOLON
			| conditionopt >> SEMICOLON >> expression;

		iteration_statement = WHILE >> LEFT_PAREN >> condition >> RIGHT_PAREN >> statement_no_new_scope
			| DO >> statement >> WHILE >> LEFT_PAREN >> expression >> RIGHT_PAREN >> SEMICOLON
			| FOR >> LEFT_PAREN >> for_init_statement >> for_rest_statement >> RIGHT_PAREN
			| statement_no_new_scope;

		jump_statement = CONTINUE >> SEMICOLON
			| BREAK >> SEMICOLON
			| RETURN >> SEMICOLON
			| RETURN >> expression >> SEMICOLON
			| DISCARD >> SEMICOLON;

		simple_statement = declaration_statement
			| expression_statement
			| selection_statement
			| switch_statement
			| case_label
			| iteration_statement
			| jump_statement;

		function_definition = function_prototype >> compound_statement_no_new_scope;

		external_declaration = function_definition
			| declaration;

		translation_unit = external_declaration
			| translation_unit >> external_declaration;
	}

	CGlslGrammar::~CGlslGrammar()
	{
	}
}
END_NAMESPACE_GLSL_PARSER
