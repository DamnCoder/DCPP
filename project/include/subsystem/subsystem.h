//
//  Subsystem.hpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef Subsystem_hpp
#define Subsystem_hpp

#include <typeinfo>

namespace dc
{
    class ISubsystem
    {
    public:
    	virtual const std::type_info& Type() const { return typeid(this); }

    public:
        ISubsystem() {}
        virtual ~ISubsystem() {}
        
    public:
        virtual void Initialize() = 0;
        virtual void Terminate() = 0;

    };
}

#endif /* Subsystem_hpp */
