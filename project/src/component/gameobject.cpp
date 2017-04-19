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
		SafeDelete(m_componentTable);
	}
	
	const unsigned int CGameObject::ComponentsNum(const char* compId) const
	{
		return GetComponentList(compId)->size();
	}
	
	const TComponentList* CGameObject::GetComponentList(const char* compId) const
	{
		const auto& componentsEntryIt = m_componentTable.find(compId);
		if(componentsEntryIt != m_componentTable.end())
		{
			return &componentsEntryIt->second;
		}
		return 0;
	}
	
	CComponent* CGameObject::AddComponent(CComponent* component)
	{
		assert(component && "Component is NULL");
		
		component->GameObject(this);
		TComponentList& componentList = m_componentTable[component->InstanceName()];
		
		componentList.push_back(component);
		return component;
	}
	
	CComponent* CGameObject::RemoveComponent(const char* name)
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
			
			return component;
		}
		return 0;
	}
	
	CComponent* CGameObject::RemoveComponent(CComponent* component)
	{
		return RemoveComponent(component->InstanceName());
	}
	
	void CGameObject::DestroyComponent(CComponent* component)
	{
		CComponent* componentToRemove = RemoveComponent(component);
		
		SafeDelete(componentToRemove);
	}
}
