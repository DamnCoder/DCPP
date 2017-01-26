//
//  scenemanagersubsystem.cpp
//  DCPP
//
//  Created by Jorge López on 21/1/17.
//
//
#include "scenesubsystem.h"

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

}
