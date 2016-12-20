//
//  CSubsystemManager.cpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "subsystem/subsystemmanager.h"

#include "help/deletehelp.h"

#include <cstdio>

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
        for(IRunnableSubsystem* runnableSubsystem : m_runnableSubsystemList)
        {
            runnableSubsystem->Run();
        }
    }
    
    void CSubsystemManager::Add(ISubsystem* subsystem)
    {
    	//TSubsystemMap::const_iterator it = m_subsystemMap.find(subsystem->Identifier());
    	m_subsystemList.push_back(subsystem);
    }
    
    void CSubsystemManager::Add(IRunnableSubsystem* runnableSubsystem)
    {
    	printf("Adding subsystem as normal subsystem\n");
    	m_subsystemList.push_back(runnableSubsystem);

        printf("Adding subsystem as runnable subsystem\n");
        m_runnableSubsystemList.push_back(runnableSubsystem);
    }
}
