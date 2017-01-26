//
//  Subsystem.hpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef Subsystem_hpp
#define Subsystem_hpp

#include "types/rtti.h"

namespace dc
{
    class ISubsystem
    {
		RTTI_BASE_DECLARATIONS(ISubsystem)
		
    public:
        ISubsystem() {}
        virtual ~ISubsystem() {}
        
    public:
        virtual void Initialize() = 0;
        virtual void Terminate() = 0;

    };
}

#endif /* Subsystem_hpp */
