//
//  CSubsystemManager.cpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "subsystem/subsystemmanager.h"

#include "help/deletehelp.h"

namespace dc
{
	void CSubsystemManager::Initialize()
    {
        for(ISubsystem* subsystem : m_subsystemList)
        {
            subsystem->Initialize();
        }
    }
    
    void CSubsystemManager::Terminate()
    {
        for(ISubsystem* subsystem : m_subsystemList)
        {
            subsystem->Terminate();
            
            SafeDelete(subsystem);
        }
        
        m_subsystemList.clear();
    }
    
    void CSubsystemManager::Run()
    {
		PrepareUpdate();
		
		for(IRunnableSubsystem* runnableSubsystem : m_runnableSubsystemList)
		{
			runnableSubsystem->Run();
		}
		
		FinishUpdate();
    }
    
    void CSubsystemManager::Add(ISubsystem* subsystem)
    {
    	m_subsystemList.push_back(subsystem);
    }
    
    void CSubsystemManager::Add(IRunnableSubsystem* runnableSubsystem)
    {
    	m_subsystemList.push_back(runnableSubsystem);
        m_runnableSubsystemList.push_back(runnableSubsystem);
    }
	
	void CSubsystemManager::PrepareUpdate()
	{
		for(IRunnableSubsystem* runnableSubsystem : m_runnableSubsystemList)
		{
			runnableSubsystem->PrepareUpdate();
		}
	}

	void CSubsystemManager::FinishUpdate()
	{
		for(IRunnableSubsystem* runnableSubsystem : m_runnableSubsystemList)
		{
			runnableSubsystem->FinishUpdate();
		}
	}
}
