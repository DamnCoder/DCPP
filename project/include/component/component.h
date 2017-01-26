//
//  component.h
//  BitThemAll
//
//  Created by Jorge López González on 26/12/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __BitThemAll__component__
#define __BitThemAll__component__

#include "types/rtti.h"

#include <string>

namespace dc
{
    class GameObject;
    
    // Type redefinitions
	using CompId = std::string;
	
    /*
     Component base class and interface
     */
	class Component
    {
		RTTI_BASE_DECLARATIONS(Component)
	public:
        Component(): mp_owner(0)
        {}
        
        virtual ~Component() {}
        
    public:
        // Getters / Setters
        GameObject* Owner() const { return mp_owner; }

        void SetOwner(GameObject* owner) { mp_owner = owner; }
        
    public:
        // Abstract interface
        virtual void Update() {}
        
    private:
        GameObject*				mp_owner;
    };
}

#endif /* defined(__BitThemAll__component__) */
