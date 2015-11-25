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

#include "GlslParser.h"
#include "GlslParserKeywords.h"
#include "GlslParserBasicType.h"

BEGIN_NAMESPACE_GLSL_PARSER
{
	CGlslParser::CGlslParser()
	{
	}

	CGlslParser::~CGlslParser()
	{
	}

	bool CGlslParser::Parse( String const & p_shader )
	{
		CBasicTypes basic_type;
		CKeywords keyword;
		Rule digit = qi::standard::digit;

		Rule nonzero_digit = qi::char_( '1' )
			| qi::char_( '2' )
			| qi::char_( '3' )
			| qi::char_( '4' )
			| qi::char_( '5' )
			| qi::char_( '6' )
			| qi::char_( '7' )
			| qi::char_( '8' )
			| qi::char_( '9' );

		Rule octal_digit = qi::int_parser< int, 8 >();

		Rule hexadecimal_digit = qi::standard::xdigit;

		Rule non_digit = qi::ascii::alpha
			| qi::char_( '_' );

		Rule identifier = non_digit
			| ( identifier >> non_digit )
			| ( identifier >> digit );

		Rule ope = qi::char_( '+' )
			| qi::char_( '-' )
			| qi::char_( '*' )
			| qi::char_( '/' );

		Rule integer_suffix = qi::char_( 'u' )
			| qi::char_( 'U' );

		Rule decimal_constant = nonzero_digit
			| ( decimal_constant >> digit );

		Rule octal_constant = qi::char_( '0' )
			| ( octal_constant >> octal_digit );

		Rule hexadecimal_constant = qi::string( "0x" ) >> hexadecimal_digit
			| qi::string( "0X" ) >> hexadecimal_digit
			| hexadecimal_constant >> hexadecimal_digit;

		Rule integer_constant = decimal_constant >> -integer_suffix
			| octal_constant >> -integer_suffix
			| hexadecimal_constant >> -integer_suffix;

		Rule sign = qi::char_( '-' )
			| qi::char_( '+' );

		Rule digit_sequence = digit >> *digit;

		Rule floating_suffix = qi::char_( 'f' )
			| qi::char_( 'F' )
			| qi::string( "lf" )
			| qi::string( "LF" );

		Rule exponent_part = qi::char_( 'e' ) >> -sign >> digit_sequence
			| qi::char_( 'E' ) >> -sign >> digit_sequence;

		Rule fractional_constant = digit_sequence >> qi::char_( '.' ) >> digit_sequence
			| digit_sequence >> qi::char_( '.' )
			| qi::char_( '.' ) >> digit_sequence;

		Rule floating_constant = fractional_constant >> -exponent_part >> -floating_suffix
			| digit_sequence >> exponent_part >> -floating_suffix;

		Rule token = keyword
			| identifier
			| integer_constant
			| floating_constant
			| ope
			| qi::char_( ';' )
			| qi::char_( '{' )
			| qi::char_( '}' );

		Rule declaration;
		Rule struct_definition;

		Rule precision_qualifier = qi::string( "lowp" )
			| qi::string( "mediump" )
			| qi::string( "highp" );

		Rule auxiliary_storage_qualifier = qi::string( "centroid" )
			| qi::string( "sample" )
			| qi::string( "patch" );

		Rule storage_qualifier = qi::string( "const" )
			| qi::string( "in" )
			| qi::string( "out" )
			| qi::string( "attribute" )
			| qi::string( "uniform" )
			| qi::string( "varying" )
			| qi::string( "buffer" )
			| qi::string( "shared" );

		Rule interface_qualifier = qi::string( "in" )
			| qi::string( "out" )
			| qi::string( "patch in" )
			| qi::string( "patch out" )
			| qi::string( "uniform" )
			| qi::string( "buffer" );

		Rule layout_qualifier_name = identifier;

		Rule layout_qualifier_value = integer_constant;

		Rule tess_input_layout_qualifier_id = qi::string( "triangles" )
			| qi::string( "quads" )
			| qi::string( "isolines" )
			| qi::string( "equal_spacing" )
			| qi::string( "fractional_even_spacing" )
			| qi::string( "frational_odd_spacing" )
			| qi::string( "cw" )
			| qi::string( "ccw" )
			| qi::string( "point_mode" );

		Rule geom_input_layout_qualifier_id = qi::string( "triangles" )
			| qi::string( "points" )
			| qi::string( "lines" )
			| qi::string( "lines_adjacency" )
			| qi::string( "triangles" )
			| qi::string( "triangles_adjacency" )
			| qi::string( "invocations" ) >> integer_constant;

		Rule frag_input_layout_qualifier_id = qi::string( "origin_upper_left" )
			| qi::string( "pixel_center_integer" );

		Rule comp_input_layout_qualifier_id = ( qi::string( "local_size_x" ) | qi::string( "local_size_y" ) | qi::string( "local_size_z" ) ) >> qi::char_( '=' ) >> integer_constant;

		Rule input_layout_qualifier_id = ( qi::string( "location" ) | qi::string( "component" ) ) >> qi::char_( '=' ) >> integer_constant
			| tess_input_layout_qualifier_id
			| geom_input_layout_qualifier_id
			| frag_input_layout_qualifier_id
			| comp_input_layout_qualifier_id;

		Rule xfbk_output_layout_qualifier_id = ( qi::string( "xfb_buffer" ) | qi::string( "xfb_offset" ) | qi::string( "xfb_stride" ) ) >> qi::char_( '=' ) >> integer_constant;

    Rule tess_output_layout_qualifier_id = qi::string( "vertices" ) >> qi::char_( '=' ) >> integer_constant;

		Rule geom_output_layout_qualifier_id = qi::string( "points" )
			| qi::string( "line_strip" )
			| qi::string( "triangle_strip" )
			| qi::string( "max_vertices" ) >> integer_constant
			| qi::string( "stream" ) >> integer_constant;

		Rule frag_output_layout_qualifier_id = qi::string( "index" ) >> qi::char_( '=' ) >> integer_constant
			| qi::string( "depth_any" )
			| qi::string( "depth_greater" )
			| qi::string( "depth_less" )
			| qi::string( "depth_unchanged" );

		Rule output_layout_qualifier_id = ( qi::string( "location" ) | qi::string( "component" ) ) >> qi::char_( '=' ) >> integer_constant
			| tess_output_layout_qualifier_id
			| geom_output_layout_qualifier_id
			| frag_output_layout_qualifier_id
			| xfbk_output_layout_qualifier_id;

		Rule uniform_layout_qualifier_id = qi::string( "location" ) >> qi::char_( '=' ) >> integer_constant;

		Rule subroutine_layout_qualifier_id = qi::string( "index" ) >> qi::char_( '=' ) >> integer_constant;

		Rule uniform_and_shader_storage_block_layout_qualifier_id = ( qi::string( "binding" ) | qi::string( "offset" ) | qi::string( "align" ) ) >> qi::char_( '=' ) >> integer_constant
			| qi::string( "shared" )
			| qi::string( "packed" )
			| qi::string( "std140" )
			| qi::string( "std130" )
			| qi::string( "row_major" )
			| qi::string( "column_major" );

		Rule opaque_uniform_layout_qualifier_id = qi::string( "binding" ) >> qi::char_( '=' ) >> integer_constant;

    Rule atomic_counter_layout_qualifier_id = ( qi::string( "binding" ) | qi::string( "offset" ) ) >> qi::char_( '=' ) >> integer_constant;

		Rule float_image_format_qualifier = qi::string( "rgba32f" )
			| qi::string( "rgba16f" )
			| qi::string( "rg32f" )
			| qi::string( "rg16f" )
			| qi::string( "r11f_g11f_b10f" )
			| qi::string( "r32f" )
			| qi::string( "r16f" )
			| qi::string( "rgba16" )
			| qi::string( "rgb10_a2" )
			| qi::string( "rgba8" )
			| qi::string( "rg16" )
			| qi::string( "rg8" )
			| qi::string( "r16" )
			| qi::string( "r8" )
			| qi::string( "rgba16_snorm" )
			| qi::string( "rgba8_snorm" )
			| qi::string( "rg16_snorm" )
			| qi::string( "rg8_snorm" )
			| qi::string( "r16_snorm" )
			| qi::string( "r8_snorm" );

		Rule int_image_format_qualifier = qi::string( "rgba32i" )
			| qi::string( "rgba16i" )
			| qi::string( "rgba8i" )
			| qi::string( "rg32i" )
			| qi::string( "rg16i" )
			| qi::string( "rg8i" )
			| qi::string( "r32i" )
			| qi::string( "r16i" )
			| qi::string( "r8i" );

		Rule uint_image_format_qualifier = qi::string( "rgba32ui" )
			| qi::string( "rgba16ui" )
			| qi::string( "rgb10_a2ui" )
			| qi::string( "rgba8ui" )
			| qi::string( "rg32ui" )
			| qi::string( "rg16ui" )
			| qi::string( "rg8ui" )
			| qi::string( "r32ui" )
			| qi::string( "r16ui" )
			| qi::string( "r8ui" );

		Rule format_qualifier_id = qi::string( "binding" ) >> qi::char_( '=' ) >> integer_constant
			| float_image_format_qualifier
			| int_image_format_qualifier
			| uint_image_format_qualifier;

		Rule layout_qualifier_id = input_layout_qualifier_id
			| output_layout_qualifier_id
			| uniform_layout_qualifier_id
			| subroutine_layout_qualifier_id
			| uniform_and_shader_storage_block_layout_qualifier_id
			| opaque_uniform_layout_qualifier_id
			| atomic_counter_layout_qualifier_id
			| format_qualifier_id;

		Rule layout_qualifier_id_list = layout_qualifier_id >> *( qi::char_( ',' ) >> layout_qualifier_id );

		Rule layout_qualifier = interface_qualifier >> qi::char_( ';' )
			| interface_qualifier >> declaration
			| qi::string( "layout" ) >> qi::char_( '(' ) >> layout_qualifier_id_list >> qi::char_( ')' );

		Rule interpolation_qualifier = qi::string( "smooth" )
			| qi::string( "flat" )
			| qi::string( "noperspective" );

		Rule parameter_qualifier = qi::string( "const" )
			| qi::string( "in" )
			| qi::string( "out" )
			| qi::string( "inout" );

		Rule variance_qualifier = qi::string( "variant" )
			| qi::string( "invariant" );

		Rule precise_qualifier = qi::string( "precise" );

		Rule memory_qualifier = qi::string( "coherent" )
			| qi::string( "volatile" )
			| qi::string( "restrict" )
			| qi::string( "readonly" )
			| qi::string( "writeonly" );

		Rule type_qualifier = precision_qualifier
			| storage_qualifier
			| layout_qualifier
			| interpolation_qualifier
			| parameter_qualifier
			| variance_qualifier
			| precise_qualifier
			| memory_qualifier
			| auxiliary_storage_qualifier >> storage_qualifier;

		Rule type_name = identifier;

		Rule type_specifier = basic_type
			| struct_definition
			| type_name;

		Rule initialiser;

		Rule declarator_specifiers = type_specifier
			| type_specifier >> declarator_specifiers
			| type_qualifier
			| type_qualifier >> declarator_specifiers;

		Rule init_declarator = declaration
			| declaration >> qi::char_( '=' ) >> initialiser;

		Rule init_declarator_list = init_declarator >> *( qi::char_( ',' ) >> init_declarator );

		Rule name = identifier;

    Rule struct_member_declarator = basic_type >> declaration;

		Rule struct_member_list = struct_member_declarator
			| struct_member_declarator >> struct_member_list;

		declaration = declarator_specifiers >> qi::char_( ';' )
			| declarator_specifiers >> init_declarator_list >> qi::char_( ';' );

		struct_definition = -type_qualifier >> qi::string( "struct" ) >> -name >> *struct_member_list >> -declaration;

		Rule interface_member_declarator = -layout_qualifier >> *type_qualifier >> type_specifier >> +declaration;

		Rule interface_member_list = interface_member_declarator
			| interface_member_declarator >> interface_member_list;

		Rule instance_name = identifier
			| identifier >> qi::char_( '[' ) >> qi::char_( ']' )
			| identifier >> qi::char_( '[' ) >> integer_constant >> qi::char_( ']' );

		Rule interface_block = -layout_qualifier >> interface_qualifier >> name >> qi::char_( '{' ) >> *interface_member_list >> qi::char_( '}' ) >> -instance_name;

    Rule statement_list;

		Rule compound_statement = qi::char_( '{' ) >> statement_list >> qi::char_( '}' );

		Rule simple_statement = declaration_statement
			| expression_statement
			| selection_statement
			| iteration_statement
			| jump_statement;

		Rule statement = compound_statement
			| simple_statement;

		Rule statement_list = statement
			| statement_list >> statement;

		Rule function_definition = function_prototype >> qi::char_( '{' ) >> statement_list >> qi::char_( '}' );

		Rule global_declaration = function_definition
			| declaration;

		Rule translation_unit = global_declaration
			| translation_unit >> global_declaration;

		bool l_return = false;

		return l_return;
	}
}
END_NAMESPACE_GLSL_PARSER
