/************************************************************************//**
* @file PluginGlslParser.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining a generic GLSL parser plugin.
*
* @details Class defining a generic GLSL parser plugin.
*
***************************************************************************/

#include "GlslParserPch.h"

#include "GlslParserKeywords.h"

BEGIN_NAMESPACE_GLSL_PARSER
{
	keywords_::keywords_()
	{
		add
			( "attribute", EKeyword_ATTRIBUTE )
			( "const", EKeyword_CONST )
			( "uniform", EKeyword_UNIFORM )
			( "varying", EKeyword_VARYING )
			( "buffer", EKeyword_BUFFER )
			( "shared", EKeyword_SHARED )
			( "coherent", EKeyword_COHERENT )
			( "volatile", EKeyword_VOLATILE )
			( "restrct", EKeyword_RESTRCT )
			( "readonly", EKeyword_READONLY )
			( "writeonly", EKeyword_WRITEONLY )
			( "atomic_uint", EKeyword_ATOMIC_UINT )
			( "layout", EKeyword_LAYOUT )
			( "centroid", EKeyword_CENTROID )
			( "flat", EKeyword_FLAT )
			( "smooth", EKeyword_SMOOTH )
			( "noperspective", EKeyword_NOPERSPECTIVE )
			( "patch", EKeyword_PATCH )
			( "sample", EKeyword_SAMPLE )
			( "break", EKeyword_BREAK )
			( "continue", EKeyword_CONTINUE )
			( "do", EKeyword_DO )
			( "for", EKeyword_FOR )
			( "while", EKeyword_WHILE )
			( "switch", EKeyword_SWITCH )
			( "case", EKeyword_CASE )
			( "default", EKeyword_DEFAULT )
			( "if", EKeyword_IF )
			( "else", EKeyword_ELSE )
			( "subroutine", EKeyword_SUBROUTINE )
			( "in", EKeyword_IN )
			( "out", EKeyword_OUT )
			( "inout", EKeyword_INOUT )
			( "float", EKeyword_FLOAT )
			( "double", EKeyword_DOUBLE )
			( "int", EKeyword_INT )
			( "void", EKeyword_VOID )
			( "bool", EKeyword_BOOL )
			( "true", EKeyword_TRUE )
			( "false", EKeyword_FALSE )
			( "invariant", EKeyword_INVARIANT )
			( "precise", EKeyword_PRECISE )
			( "discard", EKeyword_DISCARD )
			( "return", EKeyword_RETURN )
			( "mat2", EKeyword_MAT2 )
			( "mat3", EKeyword_MAT3 )
			( "mat4", EKeyword_MAT4 )
			( "dmat2", EKeyword_DMAT2 )
			( "dmat3", EKeyword_DMAT3 )
			( "dmat4", EKeyword_DMAT4 )
			( "mat2x2", EKeyword_MAT2X2 )
			( "mat2x3", EKeyword_MAT2X3 )
			( "mat2x4", EKeyword_MAT2x4 )
			( "mat3x2", EKeyword_MAT3X2 )
			( "mat3x3", EKeyword_MAT3X3 )
			( "mat3x4", EKeyword_MAT3x4 )
			( "mat4x2", EKeyword_MAT4X2 )
			( "mat4x3", EKeyword_MAT4X3 )
			( "mat4x4", EKeyword_MAT4x4 )
			( "dmat2x2", EKeyword_DMAT2X2 )
			( "dmat2x3", EKeyword_DMAT2X3 )
			( "dmat2x4", EKeyword_DMAT2x4 )
			( "dmat3x2", EKeyword_DMAT3X2 )
			( "dmat3x3", EKeyword_DMAT3X3 )
			( "dmat3x4", EKeyword_DMAT3x4 )
			( "dmat4x2", EKeyword_DMAT4X2 )
			( "dmat4x3", EKeyword_DMAT4X3 )
			( "dmat4x4", EKeyword_DMAT4x4 )
			( "vec2", EKeyword_VEC2 )
			( "vec3", EKeyword_VEC3 )
			( "vec4", EKeyword_VEC4 )
			( "ivec2", EKeyword_IVEC2 )
			( "ivec3", EKeyword_IVEC3 )
			( "ivec4", EKeyword_IVEC4 )
			( "bvec2", EKeyword_BVEC2 )
			( "bvec3", EKeyword_BVEC3 )
			( "bvec4", EKeyword_BVEC4 )
			( "dvec2", EKeyword_DVEC2 )
			( "dvec3", EKeyword_DVEC3 )
			( "dvec4", EKeyword_DVEC4 )
			( "uint", EKeyword_UINT )
			( "uvec2", EKeyword_UVEC2 )
			( "uvec3", EKeyword_UVEC3 )
			( "uvec4", EKeyword_UVEC4 )
			( "lowp", EKeyword_LOWP )
			( "mediump", EKeyword_MEDIUMP )
			( "highp", EKeyword_HIGHP )
			( "precision", EKeyword_PRECISION )
			( "sampler1d", EKeyword_SAMPLER1D )
			( "sampler2d", EKeyword_SAMPLER2D )
			( "sampler3d", EKeyword_SAMPLER3D )
			( "samplercube", EKeyword_SAMPLER_CUBE )
			( "sampler1dshadow", EKeyword_SAMPLER1D_SHADOW )
			( "sampler2dshadow", EKeyword_SAMPLER2D_SHADOW )
			( "samplercubeshadow", EKeyword_SAMPLER_CUBE_SHADOW )
			( "sampler1darray", EKeyword_SAMPLER1D_ARRAY )
			( "sampler2darray", EKeyword_SAMPLER2D_ARRAY )
			( "sampler1darray_shadow", EKeyword_SAMPLER1D_ARRAY_SHADOW )
			( "sampler2darrayshadow", EKeyword_SAMPLER2D_ARRAY_SHADOW )
			( "isampler1d", EKeyword_ISAMPLER1D )
			( "isampler2d", EKeyword_ISAMPLER2D )
			( "isampler3d", EKeyword_ISAMPLER3D )
			( "isamplercube", EKeyword_ISAMPLER_CUBE )
			( "isampler1darray", EKeyword_ISAMPLER1D_ARRAY )
			( "isampler2darray", EKeyword_ISAMPLER2D_ARRAY )
			( "usampler1d", EKeyword_USAMPLER1D )
			( "usampler2d", EKeyword_USAMPLER2D )
			( "usampler3d", EKeyword_USAMPLER3D )
			( "usamplercube", EKeyword_USAMPLER_CUBE )
			( "usampler1darray", EKeyword_USAMPLER1D_ARRAY )
			( "usampler2darray", EKeyword_USAMPLER2D_ARRAY )
			( "sampler2drect", EKeyword_SAMPLER2D_RECT )
			( "sampler2drectshadow", EKeyword_SAMPLER2D_RECT_SHADOW )
			( "isampler2drect", EKeyword_ISAMPLER2D_RECT )
			( "usampler2drectshadow", EKeyword_USAMPLER2D_RECT_SHADOW )
			( "samplerbuffer", EKeyword_SAMPLER_BUFFER )
			( "isamplerbuffer", EKeyword_ISAMPLER_BUFFER )
			( "usamplerbuffer", EKeyword_USAMPLER_BUFFER )
			( "sampler2dms", EKeyword_SAMPLER2DMS )
			( "isampler2dms", EKeyword_ISAMPLER2DMS )
			( "usampler2dms", EKeyword_USAMPLER2DMS )
			( "sampler2dmsarray", EKeyword_SAMPLER2DMS_ARRAY )
			( "isampler2dmsarray", EKeyword_ISAMPLER2DMS_ARRAY )
			( "usampler2dmsarray", EKeyword_USAMPLER2DMS_ARRAY )
			( "samplercubearray", EKeyword_SAMPLER_CUBE_ARRAY )
			( "samplercubearrayshadow", EKeyword_SAMPLER_CUBE_ARRAY_SHADOW )
			( "isamplersubearray", EKeyword_ISAMPLER_SUBE_ARRAY )
			( "usamplercubearray", EKeyword_USAMPLER_CUBE_ARRAY )
			( "image1d", EKeyword_IMAGE1D )
			( "iimage1d", EKeyword_IIMAGE1D )
			( "uimage1d", EKeyword_UIMAGE1D )
			( "image2d", EKeyword_IMAGE2D )
			( "iimage2d", EKeyword_IIMAGE2D )
			( "uimage2d", EKeyword_UIMAGE2D )
			( "image3d", EKeyword_IMAGE3D )
			( "iimage3d", EKeyword_IIMAGE3D )
			( "uimage3d", EKeyword_UIMAGE3D )
			( "image2drect", EKeyword_IMAGE2D_RECT )
			( "iimage2drect", EKeyword_IIMAGE2D_RECT )
			( "uimage2drect", EKeyword_UIMAGE2D_RECT )
			( "imagecube", EKeyword_IMAGE_CUBE )
			( "iimagecube", EKeyword_IIMAGE_CUBE )
			( "uimagecube", EKeyword_UIMAGE_CUBE )
			( "imagebuffer", EKeyword_IMAGE_BUFFER )
			( "iimagebuffer", EKeyword_IIMAGE_BUFFER )
			( "uimagebuffer", EKeyword_UIMAGE_BUFFER )
			( "image1darray", EKeyword_IMAGE1D_ARRAY )
			( "iimage1darray", EKeyword_IIMAGE1D_ARRAY )
			( "uimage1darray", EKeyword_UIMAGE1D_ARRAY )
			( "image2darray", EKeyword_IMAGE2D_ARRAY )
			( "iimage2darray", EKeyword_IIMAGE2D_ARRAY )
			( "uimage2darray", EKeyword_UIMAGE2D_ARRAY )
			( "imagecubearray", EKeyword_IMAGE_CUBE_ARRAY )
			( "iimagecubearray", EKeyword_IIMAGE_CUBE_ARRAY )
			( "uimagecubearray", EKeyword_UIMAGE_CUBE_ARRAY )
			( "image2dms", EKeyword_IMAGE2DMS )
			( "iimage2dms", EKeyword_IIMAGE2DMS )
			( "uimage2dms", EKeyword_UIMAGE2DMS )
			( "image2dmsarray", EKeyword_IMAGE2DMS_ARRAY )
			( "iimage2dmsarray", EKeyword_IIMAGE2DMS_ARRAY )
			( "uimage2dmsarray", EKeyword_UIMAGE2DMS_ARRAY )
			( "struct", EKeyword_STRUCT )

			( "asm", EKeyword_ASM )
			( "common", EKeyword_COMMON )
			( "partition", EKeyword_PARTITION )
			( "active", EKeyword_ACTIVE )
			( "class", EKeyword_CLASS )
			( "union", EKeyword_UNION )
			( "enum", EKeyword_ENUM )
			( "typedef", EKeyword_TYPEDEF )
			( "template", EKeyword_TEMPLATE )
			( "this", EKeyword_THIS )
			( "resource", EKeyword_RESOURCE )
			( "goto", EKeyword_GOTO )
			( "inline", EKeyword_INLINE )
			( "noinline", EKeyword_NOINLINE )
			( "public", EKeyword_PUBLIC )
			( "static", EKeyword_STATIC )
			( "extern", EKeyword_EXTERN )
			( "external", EKeyword_EXTERNAL )
			( "interface", EKeyword_INTERFACE )
			( "long", EKeyword_LONG )
			( "short", EKeyword_SHORT )
			( "half", EKeyword_HALF )
			( "fixed", EKeyword_FIXED )
			( "unsigned", EKeyword_UNSIGNED )
			( "superp", EKeyword_SUPERP )
			( "input", EKeyword_INPUT )
			( "output", EKeyword_OUTPUT )
			( "hvec2", EKeyword_HVEC2 )
			( "hvec3", EKeyword_HVEC3 )
			( "hvec4", EKeyword_HVEC4 )
			( "fvec2", EKeyword_FVEC2 )
			( "fvec3", EKeyword_FVEC3 )
			( "fvec4", EKeyword_FVEC4 )
			( "Sampler3dRrect", EKeyword_SAMPLER3D_RECT )
			( "filter", EKeyword_FILTER )
			( "sizeof", EKeyword_SIZEOF )
			( "cast", EKeyword_CAST )
			( "namespace", EKeyword_NAMESPACE )
			( "using", EKeyword_USING )
		;
	}

	keywords_::~keywords_()
	{
	}
}
END_NAMESPACE_GLSL_PARSER










































































































































































































