//
//  App.cpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "app.h"

namespace dc
{
	void CApp::Run()
	{
		Initialize();
		RunSubsystems();
		Terminate();
	}

	void CApp::Initialize()
	{
		printf("Initializing app\n");
		// First creation stage, where subsystems are created
		Create();
		
		// Second, initialization of the subsystems
		m_subsystemManager.Initialize();
		
		// Third, configuration stage before start running them
		Configure();
	}

	void CApp::Add(ISubsystem* subsystem)
	{
		m_subsystemManager.Add(subsystem);
	}

	void CApp::Add(IRunnableSubsystem* subsystem)
	{
		m_subsystemManager.Add(subsystem);
	}
	
	void CApp::RunSubsystems()
	{
		do
		{
			m_subsystemManager.Run();
		}
		while(!m_terminationAsked);
	}

	void CApp::Terminate()
	{
		printf("Terminating app\n");
		m_subsystemManager.Terminate();
	}
}
