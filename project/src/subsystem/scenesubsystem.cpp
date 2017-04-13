//
//  scenemanagersubsystem.cpp
//  DCPP
//
//  Created by Jorge López on 21/1/17.
//
//
#include "scenesubsystem.h"

#include <assert.h>

namespace dc
{
	void CSceneSubsystem::Initialize()
	{
		mp_sceneManager = new CSceneManager();
	}
	
	void CSceneSubsystem::Run()
	{
		assert(mp_currentScene && "There is no current scene set");
		mp_currentScene->PrepareUpdate();
		mp_currentScene->Update();
	}
	
	void CSceneSubsystem::Terminate()
	{
		delete mp_sceneManager;
		mp_sceneManager = 0;
	}
	
	CScene* CSceneSubsystem::CreateScene(const char* name)
	{
		CScene* newScene = new CScene(name);
		mp_sceneManager->Add(newScene);
		return newScene;
	}
	
	void CSceneSubsystem::SetCurrentScene(const char *name)
	{
		mp_currentScene = mp_sceneManager->Scene(name);
	}
}
