//
//  windowappsubsystem.hpp
//  dcpp
//
//  Created by Jorge López on 20/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef windowappsubsystem_hpp
#define windowappsubsystem_hpp

#include "subsystem.h"
#include "window/window.h"

namespace dc
{
    class IWindow;
    
    class CWindowSubsystem : public ISubsystem
    {
		RTTI_DECLARATIONS(CWindowSubsystem, ISubsystem)
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Constant / Enums / Typedefs
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const TDisplayInfo DisplayInfo() const { return m_displayInfo; }
		
		void DisplayInfo(const TDisplayInfo& displayInfo)
		{
			m_displayInfo = displayInfo;
		}
		
		IWindow* Window() const { return mp_window; }

		// ===========================================================
		// Constructors
		// ===========================================================
    public:
        CWindowSubsystem () : ISubsystem(), mp_window(0) {}
        CWindowSubsystem (const CWindowSubsystem& copy) = delete;
        
        virtual ~CWindowSubsystem() {}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void Initialize() override;
		
		void Terminate() override;
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================

	public:
        IWindow* 		mp_window;
        TDisplayInfo 	m_displayInfo;
    };
}

#endif /* windowappsubsystem_hpp */
