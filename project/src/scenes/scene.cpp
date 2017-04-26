//
//  scene.cpp
//  DCPP
//
//  Created by Jorge López on 20/1/17.
//
//

#include "scene.h"

#include <assert.h>

namespace dc
{
	const bool CScene::Exists(const CGameObject* gameObject)
	{
		TGOList::iterator end = m_goList.end();
		TGOList::iterator it = std::find(m_goList.begin(), end, gameObject);
		return it != end;
	}
	
	void CScene::Update()
	{
		
	}
	
	void CScene::PrepareUpdate()
	{
		if(m_newGOList.size() == 0)
			return;
		
		for(CGameObject* gameObject : m_newGOList)
		{
			AddToScene(gameObject);
		}
		m_newGOList.clear();
	}

	void CScene::FinishUpdate()
	{
		if(m_oldGOList.size() == 0)
			return;
		
		for(CGameObject* gameObject : m_oldGOList)
		{
			RemoveFromScene(gameObject);
		}
		m_oldGOList.clear();
	}

	
	void CScene::Add(CGameObject* gameObject)
	{
		printf("[CScene::AddToScene] Adding %s\n", gameObject->Name());
		
		// Check if the same Game Object is already in the scene, we can't have two instances of the same game object
		assert(!Exists(gameObject) && "[CScene::AddToScene] You can't add more than one instance of a GameObject");
		
		// We add it to a list to include it in the scene in a deferred way
		m_newGOList.push_back(gameObject);
		
		// As the Game Object is a valid one, we initialize its components
		const TComponentListTable& goComponentsMap = gameObject->ComponentsTable();
		for(auto& componentListEntry : goComponentsMap)
		{
			const TComponentList& componentList = componentListEntry.second;
			for(CComponent* component : componentList)
			{
				component->Initialize();
			}
		}
	}
	
	void CScene::Remove(CGameObject* gameObject)
	{
		// We add it to a list to remove it from the scene in a deferred way
		m_oldGOList.push_back(gameObject);
		
		// To prepare the Game Object for removal we call Sleep on its components
		const TComponentListTable& goComponentsMap = gameObject->ComponentsTable();
		for(auto& componentListEntry : goComponentsMap)
		{
			const TComponentList& componentList = componentListEntry.second;
			for(CComponent* component : componentList)
			{
				component->Sleep();
			}
		}
	}

	void CScene::AddToScene(CGameObject* gameObject)
	{
		m_goList.push_back(gameObject);
		
		const TComponentListTable& goComponentsMap = gameObject->ComponentsTable();
		for(auto& componentListEntry : goComponentsMap)
		{
			AddComponents(componentListEntry.first, componentListEntry.second);
		}
	}
	
	void CScene::RemoveFromScene(CGameObject* gameObject)
	{
		TGOList::iterator end = m_goList.end();
		TGOList::iterator it = std::find(m_goList.begin(), end, gameObject);
		
		assert(it != end && "[CScene::Remove] The game object is not in the scene");
		
		m_goList.erase(it);
		
		const TComponentListTable& goComponentsMap = gameObject->ComponentsTable();
		for(auto& componentListEntry : goComponentsMap)
		{
			RemoveComponents(componentListEntry.first, componentListEntry.second);
		}
	}
	
	void CScene::AddComponents(const char* name, const TComponentList& newComponentList)
	{
		assert(newComponentList.size() && "[CScene::AddToScene] No components being added");
		
		// The Game Object is finally added into the scene, we call Awake
		TComponentList& componentList = m_componentsMap[name];
		
		OnComponentsAdded(componentList);
		
		for(CComponent* component : newComponentList)
		{
			componentList.push_back(component);
			component->Awake();
		}
	}
	
	void CScene::RemoveComponents(const char* name, const TComponentList& oldComponentList)
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

