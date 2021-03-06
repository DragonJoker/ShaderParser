/************************************************************************//**
* @file ErrorType.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief EKeyword enumeration declaration.
*
* @details Enumeration of supported GLSL keywords.
*
***************************************************************************/

#ifndef ___GLSL_KEYWORD_H___
#define ___GLSL_KEYWORD_H___

#include "GlslParserPrerequisites.h"

#include <EToken.h>

BEGIN_NAMESPACE_GLSL_PARSER
{
	/** Enumeration of supported GLSL keywords.
	*/
	typedef enum EKeyword
	{
		EKeyword_ATTRIBUTE = EToken_COUNT,
		EKeyword_CONST,
		EKeyword_UNIFORM,
		EKeyword_VARYING,
		EKeyword_BUFFER,
		EKeyword_SHARED,
		EKeyword_COHERENT,
		EKeyword_VOLATILE,
		EKeyword_RESTRICT,
		EKeyword_READONLY,
		EKeyword_WRITEONLY,
		EKeyword_ATOMIC_UINT,
		EKeyword_LAYOUT,
		EKeyword_CENTROID,
		EKeyword_FLAT,
		EKeyword_SMOOTH,
		EKeyword_NOPERSPECTIVE,
		EKeyword_PATCH,
		EKeyword_SAMPLE,
		EKeyword_BREAK,
		EKeyword_CONTINUE,
		EKeyword_DO,
		EKeyword_FOR,
		EKeyword_WHILE,
		EKeyword_SWITCH,
		EKeyword_CASE,
		EKeyword_DEFAULT,
		EKeyword_IF,
		EKeyword_ELSE,
		EKeyword_SUBROUTINE,
		EKeyword_IN,
		EKeyword_OUT,
		EKeyword_INOUT,
		EKeyword_FLOAT,
		EKeyword_DOUBLE,
		EKeyword_INT,
		EKeyword_VOID,
		EKeyword_BOOL,
		EKeyword_TRUE,
		EKeyword_FALSE,
		EKeyword_INVARIANT,
		EKeyword_PRECISE,
		EKeyword_DISCARD,
		EKeyword_RETURN,
		EKeyword_MAT2,
		EKeyword_MAT3,
		EKeyword_MAT4,
		EKeyword_DMAT2,
		EKeyword_DMAT3,
		EKeyword_DMAT4,
		EKeyword_MAT2X2,
		EKeyword_MAT2X3,
		EKeyword_MAT2x4,
		EKeyword_MAT3X2,
		EKeyword_MAT3X3,
		EKeyword_MAT3x4,
		EKeyword_MAT4X2,
		EKeyword_MAT4X3,
		EKeyword_MAT4x4,
		EKeyword_DMAT2X2,
		EKeyword_DMAT2X3,
		EKeyword_DMAT2x4,
		EKeyword_DMAT3X2,
		EKeyword_DMAT3X3,
		EKeyword_DMAT3x4,
		EKeyword_DMAT4X2,
		EKeyword_DMAT4X3,
		EKeyword_DMAT4x4,
		EKeyword_VEC2,
		EKeyword_VEC3,
		EKeyword_VEC4,
		EKeyword_IVEC2,
		EKeyword_IVEC3,
		EKeyword_IVEC4,
		EKeyword_BVEC2,
		EKeyword_BVEC3,
		EKeyword_BVEC4,
		EKeyword_DVEC2,
		EKeyword_DVEC3,
		EKeyword_DVEC4,
		EKeyword_UINT,
		EKeyword_UVEC2,
		EKeyword_UVEC3,
		EKeyword_UVEC4,
		EKeyword_LOWP,
		EKeyword_MEDIUMP,
		EKeyword_HIGHP,
		EKeyword_PRECISION,
		EKeyword_SAMPLER1D,
		EKeyword_SAMPLER2D,
		EKeyword_SAMPLER3D,
		EKeyword_SAMPLER_CUBE,
		EKeyword_SAMPLER1D_SHADOW,
		EKeyword_SAMPLER2D_SHADOW,
		EKeyword_SAMPLER_CUBE_SHADOW,
		EKeyword_SAMPLER1D_ARRAY,
		EKeyword_SAMPLER2D_ARRAY,
		EKeyword_SAMPLER1D_ARRAY_SHADOW,
		EKeyword_SAMPLER2D_ARRAY_SHADOW,
		EKeyword_ISAMPLER1D,
		EKeyword_ISAMPLER2D,
		EKeyword_ISAMPLER3D,
		EKeyword_ISAMPLER_CUBE,
		EKeyword_ISAMPLER1D_ARRAY,
		EKeyword_ISAMPLER2D_ARRAY,
		EKeyword_USAMPLER1D,
		EKeyword_USAMPLER2D,
		EKeyword_USAMPLER3D,
		EKeyword_USAMPLER_CUBE,
		EKeyword_USAMPLER1D_ARRAY,
		EKeyword_USAMPLER2D_ARRAY,
		EKeyword_SAMPLER2D_RECT,
		EKeyword_SAMPLER2D_RECT_SHADOW,
		EKeyword_ISAMPLER2D_RECT,
		EKeyword_USAMPLER2D_RECT_SHADOW,
		EKeyword_SAMPLER_BUFFER,
		EKeyword_ISAMPLER_BUFFER,
		EKeyword_USAMPLER_BUFFER,
		EKeyword_SAMPLER2DMS,
		EKeyword_ISAMPLER2DMS,
		EKeyword_USAMPLER2DMS,
		EKeyword_SAMPLER2DMS_ARRAY,
		EKeyword_ISAMPLER2DMS_ARRAY,
		EKeyword_USAMPLER2DMS_ARRAY,
		EKeyword_SAMPLER_CUBE_ARRAY,
		EKeyword_SAMPLER_CUBE_ARRAY_SHADOW,
		EKeyword_ISAMPLER_SUBE_ARRAY,
		EKeyword_USAMPLER_CUBE_ARRAY,
		EKeyword_IMAGE1D,
		EKeyword_IIMAGE1D,
		EKeyword_UIMAGE1D,
		EKeyword_IMAGE2D,
		EKeyword_IIMAGE2D,
		EKeyword_UIMAGE2D,
		EKeyword_IMAGE3D,
		EKeyword_IIMAGE3D,
		EKeyword_UIMAGE3D,
		EKeyword_IMAGE2D_RECT,
		EKeyword_IIMAGE2D_RECT,
		EKeyword_UIMAGE2D_RECT,
		EKeyword_IMAGE_CUBE,
		EKeyword_IIMAGE_CUBE,
		EKeyword_UIMAGE_CUBE,
		EKeyword_IMAGE_BUFFER,
		EKeyword_IIMAGE_BUFFER,
		EKeyword_UIMAGE_BUFFER,
		EKeyword_IMAGE1D_ARRAY,
		EKeyword_IIMAGE1D_ARRAY,
		EKeyword_UIMAGE1D_ARRAY,
		EKeyword_IMAGE2D_ARRAY,
		EKeyword_IIMAGE2D_ARRAY,
		EKeyword_UIMAGE2D_ARRAY,
		EKeyword_IMAGE_CUBE_ARRAY,
		EKeyword_IIMAGE_CUBE_ARRAY,
		EKeyword_UIMAGE_CUBE_ARRAY,
		EKeyword_IMAGE2DMS,
		EKeyword_IIMAGE2DMS,
		EKeyword_UIMAGE2DMS,
		EKeyword_IMAGE2DMS_ARRAY,
		EKeyword_IIMAGE2DMS_ARRAY,
		EKeyword_UIMAGE2DMS_ARRAY,
		EKeyword_STRUCT,
		EKeyword_HIGH_PRECISION,
		EKeyword_MEDIUM_PRECISION,
		EKeyword_LOW_PRECISION,
	}	EKeyword;
}
END_NAMESPACE_GLSL_PARSER

#endif // ___GLSL_KEYWORD_H___
