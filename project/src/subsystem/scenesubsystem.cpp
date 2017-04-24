//
//  scenemanagersubsystem.cpp
//  DCPP
//
//  Created by Jorge López on 21/1/17.
//
//
#include "scenesubsystem.h"

#include <assert.h>

#include "app.h"

namespace dc
{
	void CSceneSubsystem::Initialize()
	{
		mp_sceneManager = new CSceneManager();
	}
	
	void CSceneSubsystem::Terminate()
	{
		delete mp_sceneManager;
		mp_sceneManager = 0;
	}
	
	void CSceneSubsystem::Run()
	{
		if(mp_currentScene)
		{
			mp_currentScene->Update();
		}
	}
	
	void CSceneSubsystem::PrepareUpdate()
	{
		if(mp_currentScene)
		{
			mp_currentScene->PrepareUpdate();
		}
	}
	
	void CSceneSubsystem::FinishUpdate()
	{
		if(mp_currentScene)
		{
			mp_currentScene->FinishUpdate();
		}
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
