/************************************************************************//**
* @file ShaderParserMacros.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
* @brief Useful macros and preprocessor checks
*
***************************************************************************/

#ifndef ___SHADER_PARSER_MACROS_H___
#define ___SHADER_PARSER_MACROS_H___

#	if !defined( __FUNCTION__ )
//! Defines this macro if not in debug
#		define __FUNCTION__ ""
#	endif

#undef PARSER_HAS_MAKE_UNIQUE

#if defined( _MSC_VER)
#	include <tchar.h>
#	pragma warning( disable: 4061 ) // enum value is not *explicitly* handled in switch
#	pragma warning( disable: 4099 ) // first seen using 'struct' now seen using 'class'
#	pragma warning( disable: 4127 ) // conditional expression is constant
#	pragma warning( disable: 4217 ) // member template isn't copy constructor
#	pragma warning( disable: 4250 ) // inherits (implements) some member via dominance
#	pragma warning( disable: 4251 ) // needs to have dll-interface to be used by clients
#	pragma warning( disable: 4275 ) // exported class derived from non-exported class
#	pragma warning( disable: 4347 ) // "behavior change", function called instead of template
#	pragma warning( disable: 4355 ) // "'this': used in member initialiser list
#	pragma warning( disable: 4428 ) // MSVC 9: universal-character-name encountered in source
#	pragma warning( disable: 4505 ) // unreferenced function has been removed
#	pragma warning( disable: 4510 ) // default constructor could not be generated
#	pragma warning( disable: 4511 ) // copy constructor could not be generated
#	pragma warning( disable: 4512 ) // assignment operator could not be generated
#	pragma warning( disable: 4513 ) // destructor could not be generated
#	pragma warning( disable: 4610 ) // can never be instantiated user defined constructor required
#	pragma warning( disable: 4623 ) // default constructor could not be generated
#	pragma warning( disable: 4624 ) // destructor could not be generated
#	pragma warning( disable: 4625 ) // copy constructor could not be generated
#	pragma warning( disable: 4626 ) // assignment operator could not be generated
#	pragma warning( disable: 4640 ) // a local static object is not thread-safe
#	pragma warning( disable: 4661 ) // a member of the template class is not defined.
#	pragma warning( disable: 4670 ) // a base class of an exception class is inaccessible for catch
#	pragma warning( disable: 4672 ) // a base class of an exception class is ambiguous for catch
#	pragma warning( disable: 4673 ) // a base class of an exception class is inaccessible for catch
#	pragma warning( disable: 4675 ) // resolved overload was found by argument-dependent lookup
#	pragma warning( disable: 4702 ) // unreachable code, e.g. in <list> header.
#	pragma warning( disable: 4710 ) // call was not inlined
#	pragma warning( disable: 4711 ) // call was inlined
#	pragma warning( disable: 4820 ) // some padding was added
#	pragma warning( disable: 4917 ) // a GUID can only be associated with a class, interface or namespace
#	pragma warning( disable: 4996 ) // MSVC 9: a C std library function has been "deprecated" (says MS)
#	if _MSC_VER >= 1800
#		define PARSER_HAS_MAKE_UNIQUE 1
#	else
#		define PARSER_HAS_MAKE_UNIQUE 0
#	endif
#	define cvsnprintf _vsnprintf_s
#elif defined( __clang__)
#	define PARSER_HAS_MAKE_UNIQUE has_feature(cxx_variadic_templates)
#	if !defined( _WIN32 )
#		define _FILE_OFFSET_BITS 64
#		define cvsnprintf( buf, sz, cnt, fmt, arg ) vsnprintf( buf, cnt, fmt, arg )
#	else
#		define _FILE_OFFSET_BITS 64
#		define cvsnprintf( buf, sz, cnt, fmt, arg ) vsnprintf( buf, cnt, fmt, arg )
#	endif
#elif defined( __GNUG__)
#	define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#	if GCC_VERSION >= 40900
#		define PARSER_HAS_MAKE_UNIQUE 1
#	else
#		define PARSER_HAS_MAKE_UNIQUE 0
#	endif
#	if !defined( _WIN32 )
#		define _FILE_OFFSET_BITS 64
#		define cvsnprintf( buf, sz, cnt, fmt, arg ) vsnprintf( buf, cnt, fmt, arg )
#	else
#		define _FILE_OFFSET_BITS 64
#		define cvsnprintf( buf, sz, cnt, fmt, arg ) vsnprintf( buf, cnt, fmt, arg )
#	endif
#elif defined( __BORLANDC__ )
#	define PARSER_HAS_MAKE_UNIQUE 0
#	if !defined( _WIN32 )
#		define _FILE_OFFSET_BITS 64
#		define cvsnprintf( buf, sz, cnt, fmt, arg ) vsnprintf( buf, cnt, fmt, arg )
#	else
#		define _FILE_OFFSET_BITS 64
#		define cvsnprintf( buf, sz, cnt, fmt, arg ) vsnprintf( buf, cnt, fmt, arg )
#	endif
#else
#	error "Yet unsupported compiler"
#endif

#define DECLARE_SMART_PTR( class_name )\
		using class_name##SPtr = std::shared_ptr< C##class_name >;\
		using class_name##WPtr = std::weak_ptr< C##class_name >;\
		using class_name##UPtr = std::unique_ptr< C##class_name >;\
		using class_name##RPtr = C##class_name *

#if !defined( PARSER_PARAM_UNUSED )
#	define PARSER_PARAM_UNUSED( x )
#endif

#endif
