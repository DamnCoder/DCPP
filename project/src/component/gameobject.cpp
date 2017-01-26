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
	const unsigned int GameObject::ComponentsNum(const CompId& comId) const
	{
		return 0;
	}
	
	Component* GameObject::AddComponent(Component* component)
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
	
	Component* GameObject::RemoveComponent(const CompId& name)
	{
		TComponentListTable::iterator componentsEntryIt = m_componentTable.find(name);
		if(componentsEntryIt != m_componentTable.end())
		{
			TComponentsEntry& componentsEntry = componentsEntryIt->second;
			// Decrease components counter
			--componentsEntry.first;
			
			TComponentList& componentList = componentsEntry.second;
			Component* component = componentList.front();
			componentList.pop_front();
			
			if(componentList.empty())
			{
				m_componentTable.erase(componentsEntryIt);
			}
			
			return component;
		}
		return 0;
	}
	
	Component* GameObject::RemoveComponent(Component* component)
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
	
	void GameObject::DestroyComponent(Component* component)
	{
		Component* componentToRemove = RemoveComponent(component);
		
		SafeDelete(componentToRemove);
	}
	
	const GameObject::TComponentsEntry* GameObject::GetComponentsEntry(const CompId& compId) const
	{
		const auto& componentsEntryIt = m_componentTable.find(compId);
		if(componentsEntryIt != m_componentTable.end())
		{
			return &componentsEntryIt->second;
		}
		return 0;
	}
}