//
//  windowappsubsystem.cpp
//  dcpp
//
//  Created by Jorge López on 20/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "subsystem/windowsubsystem.h"
#include "window/windowfactory.h"

namespace dc
{
    void CWindowSubsystem::Initialize()
    {
        mp_window = CWindowFactory::Create(m_displayInfo, EWindowType::SDL);
        
        mp_window->Initialize();
    }
    
    void CWindowSubsystem::Terminate()
    {
        mp_window->Terminate();
        
        delete mp_window;
        mp_window = 0;
    }
}
