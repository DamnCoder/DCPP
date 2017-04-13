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
		// Prepare update
		
        for(IRunnableSubsystem* runnableSubsystem : m_runnableSubsystemList)
        {
            runnableSubsystem->Run();
        }
		
		// End update
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
}
