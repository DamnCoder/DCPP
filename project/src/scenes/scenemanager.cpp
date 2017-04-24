//
//  scenemanager.cpp
//  DCPP
//
//  Created by Jorge López on 21/1/17.
//
//

#include "scenemanager.h"

#include <assert.h>
#include "help/deletehelp.h"

namespace dc
{
	CSceneManager::~CSceneManager()
	{
		SafeDelete(m_sceneList);
	}
	
	CScene* CSceneManager::Scene(const char* name)
	{
		assert(name && "You need to specify a name");
		
		for(auto* scene : m_sceneList)
		{
			if(strcmp(scene->Name(), name) == 0)
			{
				return scene;
			}
		}
		
		return 0;
	}
	
	void CSceneManager::Add(CScene* scene)
	{
		m_sceneList.push_back(scene);
	}
	
	void CSceneManager::Remove(const char* name)
	{
		TSceneList::iterator it, end;
		end = m_sceneList.end();
		for(it = m_sceneList.begin(); it != end; ++it)
		{
			if(strcmp((*it)->Name(), name) == 0)
			{
				m_sceneList.erase(it);
				return;
			}
		}
	}
	
	void CSceneManager::Remove(CScene* scene)
	{
		Remove(scene->Name());
	}
}
