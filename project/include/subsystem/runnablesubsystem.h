//
//  runnablesubsystem.h
//  dcpp
//
//  Created by Jorge López on 21/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef runnablesubsystem_h
#define runnablesubsystem_h

#include "subsystem.h"

namespace dc
{
    class IRunnableSubsystem : public ISubsystem
    {
		RTTI_DECLARATIONS(IRunnableSubsystem, ISubsystem)
    public:
        IRunnableSubsystem() : ISubsystem() {}
        virtual ~IRunnableSubsystem() {}
        
    public:
		virtual void Run() = 0;
		
		virtual void PrepareUpdate() = 0;
		virtual void FinishUpdate() = 0;
    };
}

#endif /* runnablesubsystem_h */
