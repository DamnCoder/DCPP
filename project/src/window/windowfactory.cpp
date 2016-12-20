//
//  CWindowFactory.cpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "window/sdlwindow.h"
#include "window/windowfactory.h"


namespace dc
{
    IWindow* CWindowFactory::Create(const TDisplayInfo& displayInfo, EWindowType type)
    {
        switch (type)
        {
            case EWindowType::SDL:
            {
                return new CSDLWindow(displayInfo);
            }
        }
        
        return 0;
    }
}
