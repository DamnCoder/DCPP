//
//  HFSMSubsystem.cpp
//  dcpp
//
//  Created by Jorge López on 20/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "hfsmsubsystem.h"

namespace dc
{
    void CHFSMSubsystem::Initialize()
    {
        CreateHFSM();
        CreateStates();
        InitHFSM();
    }
    
    void CHFSMSubsystem::Run()
    {
    	mp_rootState->OnTick();
    }

    void CHFSMSubsystem::Terminate()
    {
        DestroyHFSM();
    }
    
    void CHFSMSubsystem::CreateHFSM()
    {
        mp_rootState = new CComposedState(ROOT_STATE);
        mp_rootState->OnCreate();
        mp_rootState->OnActivate();
    }
    
    void CHFSMSubsystem::DestroyHFSM()
    {
        mp_rootState->OnDeactivate();
        mp_rootState->OnDestroy();
        
        delete mp_rootState;
        mp_rootState = 0;
    }
    
    void CHFSMSubsystem::InitHFSM()
    {
        mp_rootState->Set(m_initState);
    }

}
