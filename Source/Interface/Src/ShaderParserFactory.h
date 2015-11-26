/************************************************************************//**
* @file FactoryShaderParser.h
* @author Sylvain Doremus
* @version 1.0
* @date 11/23/2015
*
*
* @brief ShaderParser factory class.
*
* @details CFactoryShaderGrammar is used to manage CShaderParser creation.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_FACTORY_SHADER_PARSER_H___
#define ___SHADER_PARSER_FACTORY_SHADER_PARSER_H___

#include "ShaderParserPrerequisites.h"

#include "ShaderParserException.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	const String ERROR_DUPLICATE_FUNCTION = STR( "Duplicate creator function" );

	/** ShaderParser factory class.
		CObject factory used to manage CShaderParser creation.
	*/
	class CFactoryShaderGrammar
	{
	public:
		/** Default constructor.
		*/
		ShaderParserExport CFactoryShaderGrammar();

		/** Destructor.
		*/
		ShaderParserExport virtual ~CFactoryShaderGrammar();

		/** Perform the factory initialization.
		@remarks
			This function calls the RegisterServices() and RegisterObjectTypes() function.
		*/
		ShaderParserExport void Initialise();

		/** Returns the factory type name.
		*/
		ShaderParserExport String GetType()
		{
			return STR( "Factory.ShaderParser" );
		}

		/** Get the list of object type hat the factory can create.
		@return
			The list of object type.
		*/
		inline const std::list<String> & GetObjectTypes()
		{
			return m_objTypes;
		}

		typedef CShaderGrammar * ( *CreatorFunction )( void );
		typedef std::map< String, CreatorFunction > MapFactory;
		typedef MapFactory::iterator iterator; //!< Iterator on the map factory

		/** Register creation functions to create new objects.
		@param idKey
			key identifier.
		@param classCreator
			Class creator function.

		\b Example
		@code
			class CCmdAbort
				: public CCmdPusherControl
			{
			public:
				CCmdAbort();
				virtual ~CCmdAbort();

				// Creator function
				static CCmdPusherControl* CreateInstance() { return new CCmdAbort(); }

				// Execute command
				void Execute();
				...
			};
		@endcode
		@code
			void CCmdPusherControlFactory::RegisterServices()
			{
				RegisterCreatorFunction( ABORT, CCmdAbort::CreateInstance );
				RegisterCreatorFunction( ACCELERATION_CONTROL, CCmdAccelerationCtrl::CreateInstance );
				...
			}
		@throw ExceptionCodes_NullPointer, ExceptionCodes_DuplicateItem
		@endcode
		*/
		ShaderParserExport void RegisterCreatorFunction( const String & idKey, CreatorFunction classCreator );

		/** Create a Base object instance linked by a key.
		@param idKey
			key identifier.
		@return
			Return a new _Base object created.

		\b Example
		@code
			CCmdPusherControl* cmd = _cmdFactory.CreateInstance( sIdCmd );
			if( cmd )
			{
			...
			}
		@endcode
		*/
		ShaderParserExport CShaderGrammar * CreateInstance( const String & idKey );

	protected:
		/** Register creation functions to create new objects.
		@remarks
			This function is called by Initialise().
		*/
		ShaderParserExport virtual void RegisterServices() = 0;

		/** Register the object types.
		@remarks
			This function is called by Initialise().
		*/
		ShaderParserExport virtual void RegisterObjectTypes() = 0;

	protected:
		/** Get the Map where the construction info is stored.
		@return
			Return the Map where the construction info is stored.
		*/
		inline MapFactory * GetMapFactory()
		{
			return &m_mapFactory;
		}

		//! List of object type that the factory can create.
		std::list< String > m_objTypes;

	private:
		//! Map where the construction info is stored.
		MapFactory m_mapFactory;
	};
}
END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_FACTORY_SHADER_PARSER_H___
