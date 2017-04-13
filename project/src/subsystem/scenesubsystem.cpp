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
		
		mp_renderSubsystem = CApp::Instance().GetSubsystem<CRenderSubsystem>();
		assert(mp_renderSubsystem && "To use the CSceneSubsystem you need to add CRenderSubsystem to your app!");
	}
	
	void CSceneSubsystem::Terminate()
	{
		delete mp_sceneManager;
		mp_sceneManager = 0;
	}
	
	void CSceneSubsystem::Run()
	{
		assert(mp_currentScene && "There is no current scene set");
		PrepareUpdate();
		mp_currentScene->Update();
	}
	
	void CSceneSubsystem::PrepareUpdate()
	{
		
		mp_currentScene->PrepareUpdate();
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
