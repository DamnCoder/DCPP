//
//  scenemanager.cpp
//  DCPP
//
//  Created by Jorge López on 21/1/17.
//
//

#include "scenemanager.h"

namespace dc
{
	void CSceneManager::Add(CScene* scene)
	{
		m_sceneList.push_back(scene);
	}
	
	void CSceneManager::Remove(CScene* scene)
	{
		m_sceneList.remove(scene);
	}
}
