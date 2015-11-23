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

BEGIN_NAMESPACE_GLSL_PARSER
{
	CGlslParser::CGlslParser()
	{ 
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

		Rule non_digit =  qi::ascii::alpha
			| qi::char_( '_' );

		Rule identifier = non_digit
			| (identifier >> non_digit)
			| (identifier >> digit);

		Rule ope =  qi::char_( '+' )
			| qi::char_( '-' )
			| qi::char_( '*' )
			| qi::char_( '/' );

		Rule integer_suffix = qi::char_( 'u' )
			| qi::char_( 'U' );

		Rule opt_integer_suffix = qi::char_( '\0' )
			| integer_suffix;

		Rule decimal_constant = nonzero_digit
			| ( decimal_constant >> digit );

		Rule octal_constant = qi::char_( '0' )
			| ( octal_constant >> octal_digit );

		Rule hexadecimal_constant =  qi::string( "0x" ) >> hexadecimal_digit
			| qi::string( "0X" ) >> hexadecimal_digit
			| hexadecimal_constant >> hexadecimal_digit;

		Rule integer_constant = decimal_constant >> opt_integer_suffix
			| octal_constant >> opt_integer_suffix
			| hexadecimal_constant >> opt_integer_suffix;

		Rule sign = qi::char_( '-' )
			| qi::char_( '+' );

		Rule opt_sign = qi::char_( '\0' )
			| sign;

		Rule digit_sequence = digit
			| digit_sequence >> digit;

		Rule floating_suffix = qi::char_( 'f' )
			| qi::char_( 'F' )
			| qi::string( "lf" )
			| qi::string( "LF" );

		Rule opt_floating_suffix = qi::char_( '\0' )
			| floating_suffix;

		Rule exponent_part = qi::char_( 'e' ) >> opt_sign >> digit_sequence
			| qi::char_( 'E' ) >> opt_sign >> digit_sequence;

		Rule opt_exponent_part = qi::char_( '\0' )
			| exponent_part;

		Rule fractional_constant = digit_sequence >> '.' >> digit_sequence
			| digit_sequence >> '.'
			| '.' >> digit_sequence;

		Rule floating_constant = fractional_constant >> opt_exponent_part >> opt_floating_suffix
			| digit_sequence >> exponent_part >> opt_floating_suffix;

		Rule token = keyword
			| identifier
			| integer_constant
			| floating_constant
			| ope
			| qi::char_( ';' )
			| qi::char_( '{' )
			| qi::char_( '}' );

		Rule basic_type = qi::string( "void" )
			| qi::string( "bool" )
			| qi::string( "int" )
			| qi::string( "uint" )
			| qi::string( "float" )
			| qi::string( "double" )
			| qi::string( "vec2" )
			| qi::string( "vec3" )
			| qi::string( "vec4" )
			| qi::string( "dvec2" )
			| qi::string( "dvec3" )
			| qi::string( "dvec4" )
			| qi::string( "bvec2" )
			| qi::string( "bvec3" )
			| qi::string( "bvec4" )
			| qi::string( "ivec2" )
			| qi::string( "ivec3" )
			| qi::string( "ivec4" )
			| qi::string( "uvec2" )
			| qi::string( "uvec3" )
			| qi::string( "uvec4" )
			| qi::string( "mat2" )
			| qi::string( "mat3" )
			| qi::string( "mat4" )
			| qi::string( "mat2x2" )
			| qi::string( "mat2x3" )
			| qi::string( "mat2x4" )
			| qi::string( "mat3x2" )
			| qi::string( "mat3x3" )
			| qi::string( "mat3x4" )
			| qi::string( "mat4x2" )
			| qi::string( "mat4x3" )
			| qi::string( "mat4x4" )
			| qi::string( "dmat2" )
			| qi::string( "dmat3" )
			| qi::string( "dmat4" )
			| qi::string( "dmat2x2" )
			| qi::string( "dmat2x3" )
			| qi::string( "dmat2x4" )
			| qi::string( "dmat3x2" )
			| qi::string( "dmat3x3" )
			| qi::string( "dmat3x4" )
			| qi::string( "dmat4x2" )
			| qi::string( "dmat4x3" )
			| qi::string( "dmat4x4" )
			| qi::string( "sampler1D" )
			| qi::string( "image1D" )
			| qi::string( "sampler2D" )
			| qi::string( "image2D" )
			| qi::string( "sampler3D" )
			| qi::string( "image3D" )
			| qi::string( "samplerCube" )
			| qi::string( "imageCube" )
			| qi::string( "sampler2DRect" )
			| qi::string( "image2DRect" )
			| qi::string( "sampler1DArray" )
			| qi::string( "image1DArray" )
			| qi::string( "sampler2DArray" )
			| qi::string( "image2DArray" )
			| qi::string( "samplerBuffer" )
			| qi::string( "imageBuffer" )
			| qi::string( "sampler2DMS" )
			| qi::string( "image2DMS" )
			| qi::string( "sampler2DMSArray" )
			| qi::string( "image2DMSArray" )
			| qi::string( "samplerCubeArray" )
			| qi::string( "imageCubeArray" )
			| qi::string( "sampler1DShadow" )
			| qi::string( "sampler2DShadow" )
			| qi::string( "sampler2DRectShadow" )
			| qi::string( "sampler1DArrayShadow" )
			| qi::string( "sampler2DArrayShadow" )
			| qi::string( "samplerCubeShadow" )
			| qi::string( "samplerCubeArrayShadow" )
			| qi::string( "isampler1D" )
			| qi::string( "iimage1D" )
			| qi::string( "isampler2D" )
			| qi::string( "iimage2D" )
			| qi::string( "isampler3D" )
			| qi::string( "iimage3D" )
			| qi::string( "isamplerCube" )
			| qi::string( "iimageCube" )
			| qi::string( "isampler2DRect" )
			| qi::string( "iimage2DRect" )
			| qi::string( "isampler1DArray" )
			| qi::string( "iimage1DArray" )
			| qi::string( "isampler2DArray" )
			| qi::string( "iimage2DArray" )
			| qi::string( "isamplerBuffer" )
			| qi::string( "iimageBuffer" )
			| qi::string( "isampler2DMS" )
			| qi::string( "iimage2DMS" )
			| qi::string( "isampler2DMSArray" )
			| qi::string( "iimage2DMSArray" )
			| qi::string( "isamplerCubeArray" )
			| qi::string( "iimageCubeArray" )
			| qi::string( "atomic_uint" )
			| qi::string( "usampler1D" )
			| qi::string( "uimage1D" )
			| qi::string( "usampler2D" )
			| qi::string( "uimage2D" )
			| qi::string( "usampler3D" )
			| qi::string( "uimage3D" )
			| qi::string( "usamplerCube" )
			| qi::string( "uimageCube" )
			| qi::string( "usampler2DRect" )
			| qi::string( "uimage2DRect" )
			| qi::string( "usampler1DArray" )
			| qi::string( "uimage1DArray" )
			| qi::string( "usampler2DArray" )
			| qi::string( "uimage2DArray" )
			| qi::string( "usamplerBuffer" )
			| qi::string( "uimageBuffer" )
			| qi::string( "usampler2DMS" )
			| qi::string( "uimage2DMS" )
			| qi::string( "usampler2DMSArray" )
			| qi::string( "uimage2DMSArray" )
			| qi::string( "usamplerCubeArray" )
			| qi::string( "uimageCubeArray" );

		Rule member_declaration = basic_type >> declarators;

		Rule member_list = member_declaration
			| member_declaration >> member_list;

		Rule struct_definition = opt_qualifier >> qi::string( "string" ) >> opt_name >> { member_list } >> opt_declarators;
	}

	CGlslParser::~CGlslParser()
	{
	}
}
END_NAMESPACE_GLSL_PARSER
