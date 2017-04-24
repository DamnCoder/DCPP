//
//  material.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "material.h"

#include <assert.h>

namespace dc
{
	// ===========================================================
	// Getter & Setter
	// ===========================================================
	
	IProperty* CMaterial::GetProperty(const char* name)
	{
		assert(name && "[CMaterial::GetProperty] Name is NULL!");
		
		TPropertiesMap::iterator it = m_propertiesMap.find(name);
		if(it != m_propertiesMap.end())
		{
			return it->second;
		}
		return 0;
	}
	
	const bool CMaterial::Exists(const char* name) const
	{
		assert(name && "[CMaterial::Exists] Name is NULL!");
		
		TPropertiesMap::const_iterator it = m_propertiesMap.find(name);
		return it != m_propertiesMap.end();
	}
	
	// ===========================================================
	// Methods
	// ===========================================================
	
	void CMaterial::Activate()
	{
		for(const auto& mapEntry : m_propertiesMap)
		{
			mapEntry.second->Activate();
		}
	}
	
	void CMaterial::AddProperty(const char* name, IProperty* property)
	{
		assert(name && property && "[CMaterial::AddProperty] Name or property, or both, are NULL!");
		m_propertiesMap[name] = property;
	}
}
