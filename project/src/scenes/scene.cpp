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
		for(CGameObject* gameObject : m_newGOList)
		{
			Add(gameObject);
		}
		m_newGOList.clear();
	}
	
	void CScene::Update()
	{
		
	}
	
	void CScene::Add(CGameObject* gameObject)
	{
		m_newGOList.push_back(gameObject);
	}
	
	void CScene::Remove(CGameObject* gameObject)
	{
		TGOList::iterator it = std::find(m_goList.begin(), m_goList.end(), gameObject);
		
		assert(it != m_goList.end() && "[CScene::Remove] The game object is not in the scene");
		
		m_goList.erase(it);
		
		const TComponentListTable& goComponentsMap = gameObject->ComponentsTable();
		for(auto& componentListEntry : goComponentsMap)
		{
			Remove(componentListEntry.first, componentListEntry.second);
		}
	}

	void CScene::AddToScene(CGameObject* gameObject)
	{
		TGOList::iterator it = std::find(m_goList.begin(), m_goList.end(), gameObject);
		
		assert(it != m_goList.end() && "[CScene::AddToScene] You can't add more than one instance of a GameObject");
		
		m_goList.push_back(gameObject);
		
		const TComponentListTable& goComponentsMap = gameObject->ComponentsTable();
		for(auto& componentListEntry : goComponentsMap)
		{
			AddToScene(componentListEntry.first, componentListEntry.second);
		}
	}
	
	void CScene::AddToScene(const char* name, const TComponentList& newComponentList)
	{
		assert(newComponentList.size() && "[CScene::AddToScene] No components being added");
		
		TComponentList& componentList = m_componentsMap[name];
		for(CComponent* component : newComponentList)
		{
			componentList.push_back(component);
			component->Initialize();
			component->Awake();
		}
	}
	
	void CScene::Remove(const char* name, const TComponentList& oldComponentList)
	{
		assert(oldComponentList.size() && "[CScene::Remove] No components being removed");
		
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

