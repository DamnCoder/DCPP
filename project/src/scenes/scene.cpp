//
//  scene.cpp
//  DCPP
//
//  Created by Jorge López on 20/1/17.
//
//

#include "scene.h"

#include <assert.h>
#include <algorithm>

namespace dc
{
	void CScene::PrepareUpdate()
	{
		
	}
	
	void CScene::Update()
	{
		
	}
	
	void CScene::Add(CGameObject* gameObject)
	{
		TGOList::iterator it = std::find(m_goList.begin(), m_goList.end(), gameObject);
		assert(it != m_goList.end() && "You can't add more than one instance of a GameObject");
		
		m_goList.push_back(gameObject);
		
		const TComponentListTable& goComponentsMap = gameObject->ComponentsTable();
		for(auto& componentListEntry : goComponentsMap)
		{
			Add(componentListEntry.first, componentListEntry.second);
		}
	}
	
	void CScene::Remove(CGameObject* gameObject)
	{
		TGOList::iterator it = std::find(m_goList.begin(), m_goList.end(), gameObject);
		m_goList.erase(it);
		
		const TComponentListTable& goComponentsMap = gameObject->ComponentsTable();
		for(auto& componentListEntry : goComponentsMap)
		{
			Remove(componentListEntry.first, componentListEntry.second);
		}
	}

	void CScene::Add(const char* name, const TComponentList& newComponentList)
	{
		assert(newComponentList.size() && "No components being added");
		
		TComponentList& componentList = m_componentsMap[name];
		for(CComponent* component : newComponentList)
		{
			componentList.push_back(component);
			component->Initialize();
		}
	}
	
	void CScene::Remove(const char* name, const TComponentList& oldComponentList)
	{
		assert(oldComponentList.size() && "No components being removed");
		
		TComponentList& componentList = m_componentsMap[name];
		
		TComponentList::iterator oldBegin = std::find(componentList.begin(), componentList.end(), *oldComponentList.begin());
		TComponentList::iterator oldEnd = oldBegin + oldComponentList.size();
		
		componentList.erase(oldBegin, oldEnd);
		
		for(CComponent* component : oldComponentList)
		{
			component->Terminate();
		}
	}
}

