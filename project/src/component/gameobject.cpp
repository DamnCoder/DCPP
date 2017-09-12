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

#include "transform.h"

namespace dc
{
	CGameObject::CGameObject():
		m_name("GameObject"),
		mp_layer(CRenderLayerManager::DEFAULT_LAYER)
	{
		mp_transform = AddComponent<CTransform>();
	}
	
	CGameObject::CGameObject(const std::string& name):
		m_name(name),
		mp_layer(CRenderLayerManager::DEFAULT_LAYER)
	{
		mp_transform = AddComponent<CTransform>();
	}
	
	CGameObject::CGameObject(const std::string& name, const char* layerName):
		m_name(name),
		mp_layer(layerName)
	{
		mp_transform = AddComponent<CTransform>();
	}
	
	CGameObject::~CGameObject()
	{
		mp_layer = 0;
		mp_transform = 0;
		SafeDelete(m_componentTable);
	}
	
	const bool CGameObject::HasChild(const std::string& name) const
	{
		return FindChild(name) != 0;
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
	
	CGameObject* CGameObject::FindChild(const std::string& name) const
	{
		assert(mp_transform && "[CGameObject::FindChild] The game object has no transform component");
		
		TTransformList childrenTransList = mp_transform->Children();
		for(auto* childTrans : childrenTransList)
		{
			auto* childGO = childTrans->GameObject();
			if(childGO->Name() == name)
			{
				return childGO;
			}
			else if(childGO->Transform()->HasChildren())
			{
				CGameObject* go = childGO->FindChild(name);
				if(go)
				{
					return go;
				}
			}
		}
		
		return 0;
	}
}
