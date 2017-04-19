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
}
