//
//  game_object.cpp
//  BitThemAll
//
//  Created by Jorge López González on 26/12/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "gameobject.h"

#include <assert.h>

#include "help/deletehelp.h"

namespace dc
{
	CGameObject::~CGameObject()
	{
		m_id = 0;
		m_layer = 0;
		SafeDelete(m_componentTable);
	}
	
	const unsigned int CGameObject::ComponentsNum(const char* compId) const
	{
		return GetComponents(compId).size();
	}
	
	const TComponentList& CGameObject::GetComponents(const char* compId) const
	{
		const auto& componentsEntryIt = m_componentTable.find(compId);
		assert(componentsEntryIt != m_componentTable.end() && "[CGameObject::GetComponents] You shouldn't be asking for Components that doesn't exist");
		return componentsEntryIt->second;
	}
	
	CComponent* CGameObject::AddComponent(CComponent* component)
	{
		assert(component && "[CGameObject::GetComponents] Component is NULL");
		
		component->GameObject(this);
		TComponentList& componentList = m_componentTable[component->InstanceName()];
		
		componentList.push_back(component);
		return component;
	}
	
	void CGameObject::RemoveComponent(const char* name)
	{
		TComponentListTable::iterator componentsEntryIt = m_componentTable.find(name);
		if(componentsEntryIt != m_componentTable.end())
		{
			TComponentList& componentList = componentsEntryIt->second;
			
			CComponent* component = componentList.front();
			componentList.erase(std::find(componentList.begin(), componentList.end(), component));
			
			if(componentList.empty())
			{
				m_componentTable.erase(componentsEntryIt);
			}
			
			delete component;
		}
	}
}
