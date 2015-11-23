/************************************************************************//**
* @file DynLibManager.cpp
* @author spastor
* @version 1.0
* @date 11/23/2015
*
*
* @brief Manager for Dynamic-loading Libraries.
*
* @details Manager for Dynamic-loading Libraries.
*
***************************************************************************/

#include "ShaderParserPch.h"

#include "ShaderParserDynLibManager.h"
#include "ShaderParserDynLib.h"
#include "ShaderParserException.h"

BEGIN_NAMESPACE_SHADER_PARSER
{
	CDynLibManager::CDynLibManager()
	{
	}

	CDynLibManager::~CDynLibManager()
	{
		//!@remarks Unload
		for ( auto & l_it : m_libList )
		{
			l_it.second->Unload();
			l_it.second.reset();
		}

		//!@remarks Clear the list
		m_libList.clear();
	}

	DynLibSPtr CDynLibManager::Load( const String & filename )
	{
		auto && l_it = m_libList.find( filename );
		DynLibSPtr l_lib;

		if ( l_it != m_libList.end() )
		{
			l_lib = l_it->second;
		}
		else
		{
			l_lib = std::make_shared< CDynLib >( filename );

			try
			{
				l_lib->Load();
			}
			catch ( CShaderParserException & )
			{
				throw;
			}

			m_libList.insert( std::make_pair( l_lib->GetName(), l_lib ) );
		}

		return l_lib;
	}

	void CDynLibManager::Unload( CDynLib & p_dynLib )
	{
		auto && l_it = m_libList.find( p_dynLib.GetName() );

		if ( l_it != m_libList.end() )
		{
			DynLibSPtr l_lib = std::move( l_it->second );
			m_libList.erase( l_it );
			l_lib->Unload();
			l_lib.reset();
		}
	}

} END_NAMESPACE_SHADER_PARSER
