//
//  component.h
//  BitThemAll
//
//  Created by Jorge López González on 26/12/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef component_h
#define component_h

#include "types/rtti.h"

#include <map>
#include <vector>

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
    class CGameObject;
	
	/*
     Component base class and interface
     */
	class CComponent
    {
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		
		RTTI_BASE_DECLARATIONS(CComponent)
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		// Getters / Setters
		CGameObject* GameObject() const { return mp_gameObject; }
		
		void GameObject(CGameObject* gameObject) { mp_gameObject = gameObject; }

		// ===========================================================
		// Constructors
		// ===========================================================
	public:
        CComponent(): mp_gameObject(0)
        {}
        
        virtual ~CComponent() {}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		virtual void Initialize() {}
		virtual void Terminate() {}
		
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Finish() {}
		virtual void Sleep() {}
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
    private:
        CGameObject*	mp_gameObject;
    };
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	using TComponentList		= std::vector<CComponent*>;
	using TComponentListTable	= std::map<const char*, TComponentList>;
}

#endif
