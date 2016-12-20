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
		Create();

		Initialize();

		Configure();

		do
		{
			m_subsystemManager.Run();
		}
		while(!m_terminationAsked);

		Terminate();
	}

	void CApp::Initialize()
	{
		printf("Initializing app\n");
		m_subsystemManager.Initialize();
	}

	void CApp::Add(ISubsystem* subsystem)
	{
		m_subsystemManager.Add(subsystem);
	}

	void CApp::Add(IRunnableSubsystem* subsystem)
	{
		m_subsystemManager.Add(subsystem);
	}

	void CApp::Terminate()
	{
		printf("Terminating app\n");
		m_subsystemManager.Terminate();
	}
}
