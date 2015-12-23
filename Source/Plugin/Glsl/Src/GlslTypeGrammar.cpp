/************************************************************************//**
* @file GlslTypeGrammar.cpp
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief Class defining the GLSL parser for types.
*
***************************************************************************/

#include "GlslParserPch.h"

#include "GlslTypeGrammar.h"
#include "GlslExpressionGrammar.h"
#include "GlslParserKeywords.h"
#include "GlslParserBasicType.h"

#include <ShaderParserLogger.h>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>

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
	}

	typedef enum EStorageQualifier
	{
		EStorageQualifier_NONE,
		EStorageQualifier_CONST,
		EStorageQualifier_INOUT,
		EStorageQualifier_IN,
		EStorageQualifier_OUT,
		EStorageQualifier_CENTROID,
		EStorageQualifier_PATCH,
		EStorageQualifier_SAMPLE,
		EStorageQualifier_UNIFORM,
		EStorageQualifier_BUFFER,
		EStorageQualifier_SHARED,
		EStorageQualifier_COHERENT,
		EStorageQualifier_VOLATILE,
		EStorageQualifier_RESTRICT,
		EStorageQualifier_READONLY,
		EStorageQualifier_WRITEONLY,
	}	EStorageQualifier;

	typedef enum EPrecisionQualifier
	{
		EPrecisionQualifier_NONE,
		EPrecisionQualifier_HIGH,
		EPrecisionQualifier_MEDIUM,
		EPrecisionQualifier_LOW,
	}	EPrecisionQualifier;

	typedef enum EInterpolationQualifier
	{
		EInterpolationQualifier_NONE,
		EInterpolationQualifier_SMOOTH,
		EInterpolationQualifier_FLAT,
		EInterpolationQualifier_NOPERSPECTIVE,
	}	EInterpolationQualifier;

	typedef enum ETypeSpecifier
	{
		ETypeSpecifier_NONE,
		ETypeSpecifier_FLOAT,
		ETypeSpecifier_DOUBLE,
		ETypeSpecifier_INT,
		ETypeSpecifier_VOID,
		ETypeSpecifier_BOOL,
		ETypeSpecifier_TRUE,
		ETypeSpecifier_FALSE,
		ETypeSpecifier_INVARIANT,
		ETypeSpecifier_PRECISE,
		ETypeSpecifier_DISCARD,
		ETypeSpecifier_RETURN,
		ETypeSpecifier_MAT2,
		ETypeSpecifier_MAT3,
		ETypeSpecifier_MAT4,
		ETypeSpecifier_DMAT2,
		ETypeSpecifier_DMAT3,
		ETypeSpecifier_DMAT4,
		ETypeSpecifier_MAT2X2,
		ETypeSpecifier_MAT2X3,
		ETypeSpecifier_MAT2x4,
		ETypeSpecifier_MAT3X2,
		ETypeSpecifier_MAT3X3,
		ETypeSpecifier_MAT3x4,
		ETypeSpecifier_MAT4X2,
		ETypeSpecifier_MAT4X3,
		ETypeSpecifier_MAT4x4,
		ETypeSpecifier_DMAT2X2,
		ETypeSpecifier_DMAT2X3,
		ETypeSpecifier_DMAT2x4,
		ETypeSpecifier_DMAT3X2,
		ETypeSpecifier_DMAT3X3,
		ETypeSpecifier_DMAT3x4,
		ETypeSpecifier_DMAT4X2,
		ETypeSpecifier_DMAT4X3,
		ETypeSpecifier_DMAT4x4,
		ETypeSpecifier_VEC2,
		ETypeSpecifier_VEC3,
		ETypeSpecifier_VEC4,
		ETypeSpecifier_IVEC2,
		ETypeSpecifier_IVEC3,
		ETypeSpecifier_IVEC4,
		ETypeSpecifier_BVEC2,
		ETypeSpecifier_BVEC3,
		ETypeSpecifier_BVEC4,
		ETypeSpecifier_DVEC2,
		ETypeSpecifier_DVEC3,
		ETypeSpecifier_DVEC4,
		ETypeSpecifier_UINT,
		ETypeSpecifier_UVEC2,
		ETypeSpecifier_UVEC3,
		ETypeSpecifier_UVEC4,
		ETypeSpecifier_LOWP,
		ETypeSpecifier_MEDIUMP,
		ETypeSpecifier_HIGHP,
		ETypeSpecifier_PRECISION,
		ETypeSpecifier_SAMPLER1D,
		ETypeSpecifier_SAMPLER2D,
		ETypeSpecifier_SAMPLER3D,
		ETypeSpecifier_SAMPLER_CUBE,
		ETypeSpecifier_SAMPLER1D_SHADOW,
		ETypeSpecifier_SAMPLER2D_SHADOW,
		ETypeSpecifier_SAMPLER_CUBE_SHADOW,
		ETypeSpecifier_SAMPLER1D_ARRAY,
		ETypeSpecifier_SAMPLER2D_ARRAY,
		ETypeSpecifier_SAMPLER1D_ARRAY_SHADOW,
		ETypeSpecifier_SAMPLER2D_ARRAY_SHADOW,
		ETypeSpecifier_ISAMPLER1D,
		ETypeSpecifier_ISAMPLER2D,
		ETypeSpecifier_ISAMPLER3D,
		ETypeSpecifier_ISAMPLER_CUBE,
		ETypeSpecifier_ISAMPLER1D_ARRAY,
		ETypeSpecifier_ISAMPLER2D_ARRAY,
		ETypeSpecifier_USAMPLER1D,
		ETypeSpecifier_USAMPLER2D,
		ETypeSpecifier_USAMPLER3D,
		ETypeSpecifier_USAMPLER_CUBE,
		ETypeSpecifier_USAMPLER1D_ARRAY,
		ETypeSpecifier_USAMPLER2D_ARRAY,
		ETypeSpecifier_SAMPLER2D_RECT,
		ETypeSpecifier_SAMPLER2D_RECT_SHADOW,
		ETypeSpecifier_ISAMPLER2D_RECT,
		ETypeSpecifier_USAMPLER2D_RECT_SHADOW,
		ETypeSpecifier_SAMPLER_BUFFER,
		ETypeSpecifier_ISAMPLER_BUFFER,
		ETypeSpecifier_USAMPLER_BUFFER,
		ETypeSpecifier_SAMPLER2DMS,
		ETypeSpecifier_ISAMPLER2DMS,
		ETypeSpecifier_USAMPLER2DMS,
		ETypeSpecifier_SAMPLER2DMS_ARRAY,
		ETypeSpecifier_ISAMPLER2DMS_ARRAY,
		ETypeSpecifier_USAMPLER2DMS_ARRAY,
		ETypeSpecifier_SAMPLER_CUBE_ARRAY,
		ETypeSpecifier_SAMPLER_CUBE_ARRAY_SHADOW,
		ETypeSpecifier_ISAMPLER_SUBE_ARRAY,
		ETypeSpecifier_USAMPLER_CUBE_ARRAY,
		ETypeSpecifier_IMAGE1D,
		ETypeSpecifier_IIMAGE1D,
		ETypeSpecifier_UIMAGE1D,
		ETypeSpecifier_IMAGE2D,
		ETypeSpecifier_IIMAGE2D,
		ETypeSpecifier_UIMAGE2D,
		ETypeSpecifier_IMAGE3D,
		ETypeSpecifier_IIMAGE3D,
		ETypeSpecifier_UIMAGE3D,
		ETypeSpecifier_IMAGE2D_RECT,
		ETypeSpecifier_IIMAGE2D_RECT,
		ETypeSpecifier_UIMAGE2D_RECT,
		ETypeSpecifier_IMAGE_CUBE,
		ETypeSpecifier_IIMAGE_CUBE,
		ETypeSpecifier_UIMAGE_CUBE,
		ETypeSpecifier_IMAGE_BUFFER,
		ETypeSpecifier_IIMAGE_BUFFER,
		ETypeSpecifier_UIMAGE_BUFFER,
		ETypeSpecifier_IMAGE1D_ARRAY,
		ETypeSpecifier_IIMAGE1D_ARRAY,
		ETypeSpecifier_UIMAGE1D_ARRAY,
		ETypeSpecifier_IMAGE2D_ARRAY,
		ETypeSpecifier_IIMAGE2D_ARRAY,
		ETypeSpecifier_UIMAGE2D_ARRAY,
		ETypeSpecifier_IMAGE_CUBE_ARRAY,
		ETypeSpecifier_IIMAGE_CUBE_ARRAY,
		ETypeSpecifier_UIMAGE_CUBE_ARRAY,
		ETypeSpecifier_IMAGE2DMS,
		ETypeSpecifier_IIMAGE2DMS,
		ETypeSpecifier_UIMAGE2DMS,
		ETypeSpecifier_IMAGE2DMS_ARRAY,
		ETypeSpecifier_IIMAGE2DMS_ARRAY,
		ETypeSpecifier_UIMAGE2DMS_ARRAY,
	}	ETypeSpecifier;

	struct LayoutQualifierId
	{
		String m_identifier;
		String m_constantExpression;
	};

	struct TypeQualifier
	{
		std::vector< EStorageQualifier > m_storages;
		std::vector< LayoutQualifierId > m_layouts;
		EPrecisionQualifier m_precision;
		EInterpolationQualifier m_interpolation;
		bool m_invariant;
		bool m_precise;
	};

	struct ArraySpecifier
	{
		String m_constantExpression;
	};

	struct FullySpecifiedType
	{
		std::vector< TypeQualifier > m_qualifiers;
		ETypeSpecifier m_specifier;
		boost::optional< ArraySpecifier > m_array;
	};
}
	
//BOOST_FUSION_ADAPT_STRUCT( LayoutQualifierId,
//	( String, m_identifier )
//	( String, m_constantExpression )
//	)
//
//BOOST_FUSION_ADAPT_STRUCT( TypeQualifier,
//	( std::vector< EStorageQualifier >, m_storages )
//	( std::vector< LayoutQualifierId >, m_layouts )
//	( EPrecisionQualifier, m_precision )
//	( EInterpolationQualifier, m_interpolation )
//	( bool, m_invariant )
//	( bool, m_precise )
//	)
//
//BOOST_FUSION_ADAPT_STRUCT( ArraySpecifier,
//	( String, m_constantExpression )
//	)
//
//BOOST_FUSION_ADAPT_STRUCT( ArraySpecifier,
//	( std::vector< TypeQualifier >, m_qualifiers )
//	( ETypeSpecifier, m_specifier )
//	( boost::optional< ArraySpecifier >, m_array )
//	)

namespace GlslParser
{
	CGlslTypeGrammar::CGlslTypeGrammar( Rule & type_specifier, CGlslExpressionGrammar const & expression )
		: CShaderGrammar( fully_specified_type )
	{
		type_qualifier = ( single_type_qualifier.alias() >> -type_qualifier )[on_rule( "type_qualifier", "single_type_qualifier.alias()", "-type_qualifier" )];
		type_qualifier.name( "type_qualifier" );

		fully_specified_type = ( -type_qualifier >> type_specifier.alias() )[on_rule( "fully_specified_type", "-type_qualifier", "type_specifier.alias" )];
		fully_specified_type.name( "fully_specified_type" );

		array_specifier = ( LEFT_BRACKET >> -expression.constant_expression >> RIGHT_BRACKET >> -array_specifier )[on_rule( "array_specifier", "LEFT_BRACKET", "-constant_expression", "RIGHT_BRACKET", "-array_specifier" )];
		array_specifier.name( "array_specifier" );

		precision_qualifier = HIGH_PRECISION[on_rule( "precision_qualifier", "HIGH_PRECISION" )]
			| MEDIUM_PRECISION[on_rule( "precision_qualifier", "MEDIUM_PRECISION" )]
			| LOW_PRECISION[on_rule( "precision_qualifier", "LOW_PRECISION" )];
		precision_qualifier.name( "precision_qualifier" );

		invariant_qualifier = INVARIANT[on_rule( "invariant_qualifier", "INVARIANT" )];
		invariant_qualifier.name( "invariant_qualifier" );

		interpolation_qualifier = SMOOTH[on_rule( "interpolation_qualifier", "SMOOTH" )]
			| FLAT[on_rule( "interpolation_qualifier", "FLAT" )]
			| NOPERSPECTIVE[on_rule( "interpolation_qualifier", "NOPERSPECTIVE" )];
		interpolation_qualifier.name( "interpolation_qualifier" );

		layout_qualifier_id = ( identifier >> -( EQUAL >> expression.constant_expression ) )[on_rule( "declaration", "identifier", "-( EQUAL  constant_expression )" )]
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

		type_name = identifier[on_rule( "type_name", "identifier" )];

		base_type_specifier = VOID[on_rule( "base_type_specifier", "VOID" )]
			| FLOAT[on_rule( "base_type_specifier", "FLOAT" )]
			| DOUBLE[on_rule( "base_type_specifier", "DOUBLE" )]
			| INT[on_rule( "base_type_specifier", "INT" )]
			| UINT[on_rule( "base_type_specifier", "UINT" )]
			| BOOL[on_rule( "base_type_specifier", "BOOL" )];
		base_type_specifier.name( "base_type_specifier" );

		vec_specifier = VEC2[on_rule( "vec_specifier", "VEC2" )]
			| VEC3[on_rule( "vec_specifier", "VEC3" )]
			| VEC4[on_rule( "vec_specifier", "VEC4" )]
			| DVEC2[on_rule( "vec_specifier", "DVEC2" )]
			| DVEC3[on_rule( "vec_specifier", "DVEC3" )]
			| DVEC4[on_rule( "vec_specifier", "DVEC4" )]
			| BVEC2[on_rule( "vec_specifier", "BVEC2" )]
			| BVEC3[on_rule( "vec_specifier", "BVEC3" )]
			| BVEC4[on_rule( "vec_specifier", "BVEC4" )]
			| IVEC2[on_rule( "vec_specifier", "IVEC2" )]
			| IVEC3[on_rule( "vec_specifier", "IVEC3" )]
			| IVEC4[on_rule( "vec_specifier", "IVEC4" )]
			| UVEC2[on_rule( "vec_specifier", "UVEC2" )]
			| UVEC3[on_rule( "vec_specifier", "UVEC3" )]
			| UVEC4[on_rule( "vec_specifier", "UVEC4" )];
		vec_specifier.name( "vec_specifier" );

		mat_specifier = MAT2[on_rule( "mat_specifier", "MAT2" )]
			| MAT3[on_rule( "mat_specifier", "MAT3" )]
			| MAT4[on_rule( "mat_specifier", "MAT4" )]
			| MAT2X2[on_rule( "mat_specifier", "MAT2X2" )]
			| MAT2X3[on_rule( "mat_specifier", "MAT2X3" )]
			| MAT2X4[on_rule( "mat_specifier", "MAT2X4" )]
			| MAT3X2[on_rule( "mat_specifier", "MAT3X2" )]
			| MAT3X3[on_rule( "mat_specifier", "MAT3X3" )]
			| MAT3X4[on_rule( "mat_specifier", "MAT3X4" )]
			| MAT4X2[on_rule( "mat_specifier", "MAT4X2" )]
			| MAT4X3[on_rule( "mat_specifier", "MAT4X3" )]
			| MAT4X4[on_rule( "mat_specifier", "MAT4X4" )];
		mat_specifier.name( "mat_specifier" );

		dmat_specifier = DMAT2[on_rule( "mat_specifier", "DMAT2" )]
			| DMAT3[on_rule( "mat_specifier", "DMAT3" )]
			| DMAT4[on_rule( "mat_specifier", "DMAT4" )]
			| DMAT2X2[on_rule( "mat_specifier", "DMAT2X2" )]
			| DMAT2X3[on_rule( "mat_specifier", "DMAT2X3" )]
			| DMAT2X4[on_rule( "mat_specifier", "DMAT2X4" )]
			| DMAT3X2[on_rule( "mat_specifier", "DMAT3X2" )]
			| DMAT3X3[on_rule( "mat_specifier", "DMAT3X3" )]
			| DMAT3X4[on_rule( "mat_specifier", "DMAT3X4" )]
			| DMAT4X2[on_rule( "mat_specifier", "DMAT4X2" )]
			| DMAT4X3[on_rule( "mat_specifier", "DMAT4X3" )]
			| DMAT4X4[on_rule( "mat_specifier", "DMAT4X4" )];
		dmat_specifier.name( "mat_specifier" );

		fsampler_specifier = SAMPLER1D[on_rule( "fsampler_specifier", "SAMPLER1D" )]
			| SAMPLER2D[on_rule( "fsampler_specifier", "SAMPLER2D" )]
			| SAMPLER3D[on_rule( "fsampler_specifier", "SAMPLER3D" )]
			| SAMPLERCUBE[on_rule( "fsampler_specifier", "SAMPLERCUBE" )]
			| SAMPLER1DSHADOW[on_rule( "fsampler_specifier", "SAMPLER1DSHADOW" )]
			| SAMPLER2DSHADOW[on_rule( "fsampler_specifier", "SAMPLER2DSHADOW" )]
			| SAMPLERCUBESHADOW[on_rule( "fsampler_specifier", "SAMPLERCUBESHADOW" )]
			| SAMPLER1DARRAY[on_rule( "fsampler_specifier", "SAMPLER1DARRAY" )]
			| SAMPLER2DARRAY[on_rule( "fsampler_specifier", "SAMPLER2DARRAY" )]
			| SAMPLER1DARRAYSHADOW[on_rule( "fsampler_specifier", "SAMPLER1DARRAYSHADOW" )]
			| SAMPLER2DARRAYSHADOW[on_rule( "fsampler_specifier", "SAMPLER2DARRAYSHADOW" )]
			| SAMPLERCUBEARRAY[on_rule( "fsampler_specifier", "SAMPLERCUBEARRAY" )]
			| SAMPLERCUBEARRAYSHADOW[on_rule( "fsampler_specifier", "SAMPLERCUBEARRAYSHADOW" )]
			| SAMPLER2DRECT[on_rule( "fsampler_specifier", "SAMPLER2DRECT" )]
			| SAMPLER2DRECTSHADOW[on_rule( "fsampler_specifier", "SAMPLER2DRECTSHADOW" )]
			| SAMPLER2DMS[on_rule( "fsampler_specifier", "SAMPLER2DMS" )];
		fsampler_specifier.name( "fsampler_specifier" );

		isampler_specifier = ISAMPLER1D[on_rule( "isampler_specifier", "ISAMPLER1D" )]
			| ISAMPLER2D[on_rule( "isampler_specifier", "ISAMPLER2D" )]
			| ISAMPLER3D[on_rule( "isampler_specifier", "ISAMPLER3D" )]
			| ISAMPLERCUBE[on_rule( "isampler_specifier", "ISAMPLERCUBE" )]
			| ISAMPLER1DARRAY[on_rule( "isampler_specifier", "ISAMPLER1DARRAY" )]
			| ISAMPLER2DARRAY[on_rule( "isampler_specifier", "ISAMPLER2DARRAY" )]
			| ISAMPLERCUBEARRAY[on_rule( "isampler_specifier", "ISAMPLERCUBEARRAY" )]
			| ISAMPLER2DRECT[on_rule( "isampler_specifier", "ISAMPLER2DRECT" )]
			| ISAMPLERBUFFER[on_rule( "isampler_specifier", "ISAMPLERBUFFER" )]
			| ISAMPLER2DMS[on_rule( "isampler_specifier", "ISAMPLER2DMS" )]
			| ISAMPLER2DMSARRAY[on_rule( "isampler_specifier", "ISAMPLER2DMSARRAY" )];
		isampler_specifier.name( "isampler_specifier" );

		usampler_specifier = USAMPLER1D[on_rule( "usampler_specifier", "USAMPLER1D" )]
			| USAMPLER2D[on_rule( "usampler_specifier", "USAMPLER2D" )]
			| USAMPLER3D[on_rule( "usampler_specifier", "USAMPLER3D" )]
			| USAMPLERCUBE[on_rule( "usampler_specifier", "USAMPLERCUBE" )]
			| USAMPLER1DARRAY[on_rule( "usampler_specifier", "USAMPLER1DARRAY" )]
			| USAMPLER2DARRAY[on_rule( "usampler_specifier", "USAMPLER2DARRAY" )]
			| USAMPLERCUBEARRAY[on_rule( "usampler_specifier", "USAMPLERCUBEARRAY" )]
			| USAMPLER2DRECT[on_rule( "usampler_specifier", "USAMPLER2DRECT" )]
			| SAMPLERBUFFER[on_rule( "usampler_specifier", "SAMPLERBUFFER" )]
			| USAMPLERBUFFER[on_rule( "usampler_specifier", "USAMPLERBUFFER" )]
			| USAMPLER2DMS[on_rule( "usampler_specifier", "USAMPLER2DMS" )]
			| SAMPLER2DMSARRAY[on_rule( "usampler_specifier", "SAMPLER2DMSARRAY" )]
			| USAMPLER2DMSARRAY[on_rule( "usampler_specifier", "USAMPLER2DMSARRAY" )];
		usampler_specifier.name( "usampler_specifier" );

		image_specifier = IMAGE1D[on_rule( "image_specifier", "IMAGE1D" )]
			| IMAGE2D[on_rule( "image_specifier", "IMAGE2D" )]
			| IMAGE3D[on_rule( "image_specifier", "IMAGE3D" )]
			| IMAGE2DRECT[on_rule( "image_specifier", "IMAGE2DRECT" )]
			| IMAGECUBE[on_rule( "image_specifier", "IMAGECUBE" )]
			| IMAGEBUFFER[on_rule( "image_specifier", "IMAGEBUFFER" )]
			| IMAGE1DARRAY[on_rule( "image_specifier", "IMAGE1DARRAY" )]
			| IMAGE2DARRAY[on_rule( "image_specifier", "IMAGE2DARRAY" )]
			| IMAGECUBEARRAY[on_rule( "image_specifier", "IMAGECUBEARRAY" )]
			| IMAGE2DMS[on_rule( "image_specifier", "IMAGE2DMS" )]
			| IMAGE2DMSARRAY[on_rule( "image_specifier", "IMAGE2DMSARRAY" )];
		image_specifier.name( "image_specifier" );

		iimage_specifier = IIMAGE1D[on_rule( "iimage_specifier", "IIMAGE1D" )]
			| IIMAGE2D[on_rule( "iimage_specifier", "IIMAGE2D" )]
			| IIMAGE3D[on_rule( "iimage_specifier", "IIMAGE3D" )]
			| IIMAGE2DRECT[on_rule( "iimage_specifier", "IIMAGE2DRECT" )]
			| IIMAGECUBE[on_rule( "iimage_specifier", "IIMAGECUBE" )]
			| IIMAGEBUFFER[on_rule( "iimage_specifier", "IIMAGEBUFFER" )]
			| IIMAGE1DARRAY[on_rule( "iimage_specifier", "IIMAGE1DARRAY" )]
			| IIMAGE2DARRAY[on_rule( "iimage_specifier", "IIMAGE2DARRAY" )]
			| IIMAGECUBEARRAY[on_rule( "iimage_specifier", "IIMAGECUBEARRAY" )]
			| IIMAGE2DMS[on_rule( "iimage_specifier", "IIMAGE2DMS" )]
			| IIMAGE2DMSARRAY[on_rule( "iimage_specifier", "IIMAGE2DMSARRAY" )];
		iimage_specifier.name( "iimage_specifier" );

		uimage_specifier = UIMAGE1D[on_rule( "uimage_specifier", "UIMAGE1D" )]
			| UIMAGE2D[on_rule( "uimage_specifier", "UIMAGE2D" )]
			| UIMAGE3D[on_rule( "uimage_specifier", "UIMAGE3D" )]
			| UIMAGE2DRECT[on_rule( "uimage_specifier", "UIMAGE2DRECT" )]
			| UIMAGECUBE[on_rule( "uimage_specifier", "UIMAGECUBE" )]
			| UIMAGEBUFFER[on_rule( "uimage_specifier", "UIMAGEBUFFER" )]
			| UIMAGE1DARRAY[on_rule( "uimage_specifier", "UIMAGE1DARRAY" )]
			| UIMAGE2DARRAY[on_rule( "uimage_specifier", "UIMAGE2DARRAY" )]
			| UIMAGECUBEARRAY[on_rule( "uimage_specifier", "UIMAGECUBEARRAY" )]
			| UIMAGE2DMS[on_rule( "uimage_specifier", "UIMAGE2DMS" )]
			| UIMAGE2DMSARRAY[on_rule( "uimage_specifier", "UIMAGE2DMSARRAY" )];
		uimage_specifier.name( "uimage_specifier" );

		type_specifier_nonarray = base_type_specifier[on_rule( "type_specifier_nonarray", "base_type_specifier" )]
			| vec_specifier[on_rule( "type_specifier_nonarray", "vec_specifier" )]
			| mat_specifier[on_rule( "type_specifier_nonarray", "mat_specifier" )]
			| dmat_specifier[on_rule( "type_specifier_nonarray", "dmat_specifier" )]
			| ATOMIC_UINT[on_rule( "type_specifier_nonarray", "ATOMIC_UINT" )]
			| fsampler_specifier[on_rule( "type_specifier_nonarray", "fsampler_specifier" )]
			| isampler_specifier[on_rule( "type_specifier_nonarray", "isampler_specifier" )]
			| usampler_specifier[on_rule( "type_specifier_nonarray", "usampler_specifier" )]
			| image_specifier[on_rule( "type_specifier_nonarray", "image_specifier" )]
			| iimage_specifier[on_rule( "type_specifier_nonarray", "iimage_specifier" )]
			| uimage_specifier[on_rule( "type_specifier_nonarray", "uimage_specifier" )]
			| struct_specifier[on_rule( "type_specifier_nonarray", "struct_specifier" )]
			| type_name[on_rule( "type_specifier_nonarray", "type_name" )];
		type_specifier_nonarray.name( "type_specifier_nonarray" );
	}

	CGlslTypeGrammar::~CGlslTypeGrammar()
	{
	}
}
