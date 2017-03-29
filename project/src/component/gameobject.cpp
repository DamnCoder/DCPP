//
//  game_object.cpp
//  BitThemAll
//
//  Created by Jorge López González on 26/12/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "gameobject.h"

#include "help/deletehelp.h"

namespace dc
{
	const unsigned int CGameObject::ComponentsNum(const CompId& comId) const
	{
		return 0;
	}
	
	CComponent* CGameObject::AddComponent(CComponent* component)
	{
		if(component)
		{
			component->SetOwner(this);
			TComponentsEntry& componentsEntry = m_componentTable[component->InstanceName()];
			TComponentList& componentList = componentsEntry.second;
			
			// Increase components counter
			++componentsEntry.first;
			componentList.push_front(component);
		}
		return component;
	}
	
	CComponent* CGameObject::RemoveComponent(const CompId& name)
	{
		TComponentListTable::iterator componentsEntryIt = m_componentTable.find(name);
		if(componentsEntryIt != m_componentTable.end())
		{
			TComponentsEntry& componentsEntry = componentsEntryIt->second;
			// Decrease components counter
			--componentsEntry.first;
			
			TComponentList& componentList = componentsEntry.second;
			CComponent* component = componentList.front();
			componentList.pop_front();
			
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
		TComponentListTable::iterator componentsEntryIt = m_componentTable.find(component->InstanceName());
		if(componentsEntryIt != m_componentTable.end())
		{
			TComponentsEntry& componentsEntry = componentsEntryIt->second;
			// Decrease components counter
			--componentsEntry.first;
			
			TComponentList& componentList = componentsEntry.second;
			componentList.remove(component);
			if(componentList.empty())
			{
				m_componentTable.erase(componentsEntryIt);
			}
			
			return component;
		}
		return 0;
	}
	
	void CGameObject::DestroyComponent(CComponent* component)
	{
		CComponent* componentToRemove = RemoveComponent(component);
		
		SafeDelete(componentToRemove);
	}
	
	const CGameObject::TComponentsEntry* CGameObject::GetComponentsEntry(const CompId& compId) const
	{
		const auto& componentsEntryIt = m_componentTable.find(compId);
		if(componentsEntryIt != m_componentTable.end())
		{
			return &componentsEntryIt->second;
		}
		return 0;
	}
}
