/************************************************************************//**
* @file FactoryObjectManager.cpp
* @author spastor
* @version 1.0
* @date 11/23/2015
*
*
* @brief This manager manages factory objects.
*
* @details This class not only manages the object themselves, it also manages
*          the factory classes wich allow the creation of specific objects.
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderParserFactory.h"
#include "ShaderParserFactoryManager.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	static const String ERROR_DB_FACTORY_TYPE_NOT_FOUND = STR( "Factory type %1% not found in registered factories" );
	static const String ERROR_DB_OBJECT_TYPE_NOT_FOUND = STR( "Object type %1% not found in registered objects" );

	CFactoryManager::CFactoryManager()
	{
	}

	CFactoryManager::~CFactoryManager()
	{
	}

	void CFactoryManager::AddFactory( CFactoryShaderGrammar * p_factory )
	{
		m_factories.insert( std::make_pair( p_factory->GetType(), p_factory ) );

		//!@remarks Create the association between an object type and its factory.
		auto && l_objTypes = p_factory->GetObjectTypes();

		for ( auto && l_name : l_objTypes )
		{
			m_objectFactories.insert( std::make_pair( l_name, p_factory->GetType() ) );
		}
	}

	void CFactoryManager::RemoveFactory( CFactoryShaderGrammar * factory )
	{
		auto && l_itFactory = m_factories.find( factory->GetType() );

		if ( l_itFactory != m_factories.end() )
		{
			m_factories.erase( l_itFactory );

			//!@remarks Remove the association between an object type and its factory.
			auto && l_objTypes = factory->GetObjectTypes();

			for ( auto && l_name : l_objTypes )
			{
				auto && l_itObject = m_objectFactories.find( l_name );

				if ( l_itObject != m_objectFactories.end() )
				{
					m_objectFactories.erase( l_itObject );
				}
			}
		}
	}

	CShaderGrammar * CFactoryManager::CreateInstance( const String & p_factoryType, const String & p_objectType )
	{
		CShaderGrammar * l_object = NULL;

		//!@remarks Find factory object.
		auto && l_itFactory = m_factories.find( p_factoryType );

		if ( l_itFactory != m_factories.end() )
		{
			CFactoryShaderGrammar * l_factory = l_itFactory->second;

			if ( l_factory )
			{
				//!@remarks Create a new object instance.
				l_object = l_factory->CreateInstance( p_objectType );
			}
			else
			{
				Format l_fmt( ERROR_DB_FACTORY_TYPE_NOT_FOUND );
				l_fmt % p_factoryType;
				PARSER_EXCEPT( EShaderParserExceptionCodes_NullPointer, l_fmt.str() );
			}
		}
		else
		{
			Format l_fmt( ERROR_DB_FACTORY_TYPE_NOT_FOUND );
			l_fmt % p_factoryType;
			PARSER_EXCEPT( EShaderParserExceptionCodes_ItemNotFound, l_fmt.str() );
		}

		return l_object;
	}

	CShaderGrammar * CFactoryManager::CreateInstance( const String & p_objectType )
	{
		//!@remarks Find factory type.
		auto && l_itObject = m_objectFactories.find( p_objectType );

		if ( l_itObject != m_objectFactories.end() )
		{
			//!@remarks Create a new object instance.
			return CreateInstance( l_itObject->second, p_objectType );
		}
		else
		{
			Format l_fmt( ERROR_DB_OBJECT_TYPE_NOT_FOUND );
			l_fmt % p_objectType;
			PARSER_EXCEPT( EShaderParserExceptionCodes_ItemNotFound, l_fmt.str() );
		}

		return NULL;
	}
}
END_NAMESPACE_SHADER_PARSER
