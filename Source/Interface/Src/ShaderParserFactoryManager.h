/************************************************************************//**
* @file FactoryObjectManager.h
* @author spastor
* @version 1.0
* @date 11/23/2015
*
*
* @brief This manager manages factory objects.
*
* @details This class not only manages the object themselves, it also manages
*          the factory classes which allow the creation of specific objects.
*
***************************************************************************/

#ifndef ___SHADER_PARSER_FACTORY_MANAGER_H___
#define ___SHADER_PARSER_FACTORY_MANAGER_H___

#include "ShaderParserPrerequisites.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	/** This manager manages factory objects.
		This class is not only managing the objects themselves,
		it also manages the factory classes which allow the creation of specific objects.
	*/
	class CFactoryManager
	{
	public:
		/** Add a new factory object.
		@param factory
			Object factory to add.
		*/
		ShaderParserExport virtual void AddFactory( CFactoryShaderParser * factory );

		/** Remove a factory object.
		@param factory
			Object factory to remove.
		*/
		ShaderParserExport virtual void RemoveFactory( CFactoryShaderParser * factory );

		/** Create a object instance with its given type.
		@param factoryType
			Type that identify wich factory is used to create the object.
		@param objectType
			Type that identify wich object has to create.
		@return
			Pointer on a new object of type \c type.
		@remarks
			If the factory type \c type doesn't exist, a NULL be returned.
		*/
		ShaderParserExport CShaderParser * CreateInstance( const String & factoryType, const String & objectType );

		/** Create a object instance with its given type.
		@param objectType
			Type that identify wich object has to create.
		@return
			Pointer on a new object of type \c type.
		@remarks
			If the factory type \c type doesn't exist, a NULL be returned.
		*/
		ShaderParserExport CShaderParser * CreateInstance( const String & objectType );

		/** Retrieves the unique instance
		*/
		ShaderParserExport static CFactoryManager & Instance()
		{
			static CFactoryManager l_singleton;
			return l_singleton;
		}

	protected:
		/** Default constructor.
		*/
		ShaderParserExport CFactoryManager();

		/** Destructor.
		*/
		ShaderParserExport virtual ~CFactoryManager();

	protected:
		/** Get the Map where the construction info is stored.
		*/
		ShaderParserExport std::map< String, CFactoryShaderParser * > * GetMapFactories()
		{
			return &m_factories;
		}

	protected:
		//! Factories managing the created instances.
		std::map< String, CFactoryShaderParser * > m_factories;
		//! Manage the association between an object type and its factory.
		std::map< String, String > m_objectFactories;
	};
}
END_NAMESPACE_SHADER_PARSER

#endif // ___SHADER_PARSER_FACTORY_MANAGER_H___
