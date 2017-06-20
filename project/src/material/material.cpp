//
//  material.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "material.h"

#include <assert.h>

#include "help/deletehelp.h"

namespace dc
{
	// ===========================================================
	// Getter & Setter
	// ===========================================================
	
	IProperty* CMaterial::GetProperty(const std::string& name)
	{
		assert(name.length() && "[CMaterial::GetProperty] Name is NULL!");
		
		TPropertiesMap::iterator it = m_propertiesMap.find(name);
		if(it != m_propertiesMap.end())
		{
			return it->second;
		}
		return 0;
	}
	
	const bool CMaterial::Exists(const std::string& name) const
	{
		assert(name.length() && "[CMaterial::Exists] Name is NULL!");
		
		TPropertiesMap::const_iterator it = m_propertiesMap.find(name);
		return it != m_propertiesMap.end();
	}
	
	CMaterial::~CMaterial()
	{
		SafeDelete(m_propertiesMap);
	}
	
	// ===========================================================
	// Methods
	// ===========================================================
	const bool CMaterial::Equals(const CMaterial* material)
	{
		if(Properties().size() != material->Properties().size())
		{
			return false;
		}
		
		for(auto* matProp1 : Properties())
		{
			for(auto* matProp2 : material->Properties())
			{
				if(!matProp1->Equals(matProp2))
				{
					return false;
				}
				
			}
		}
		return true;
	}
	
	
	void CMaterial::Activate() const
	{
		for(const auto* property : m_propertiesList)
		{
			property->Activate();
		}
	}
	
	void CMaterial::Deactivate() const
	{
		for(const auto* property : m_propertiesList)
		{
			property->Deactivate();
		}
	}
	
	CMaterialProperty<CBlending>* CMaterial::AddProperty(const std::string& name, const EBlendMode& blending)
	{
		auto* property =  new CMaterialProperty<CBlending>(new CBlending(blending));
		AddIProperty(name, property);
		return property;
	}
	
	void CMaterial::AddIProperty(const std::string& name, IProperty* property)
	{
		assert(name.length() && property && "[CMaterial::AddProperty] Name or property, or both, are NULL!");
		m_propertiesMap[name] = property;
		m_propertiesList.push_back(property);
	}
}
