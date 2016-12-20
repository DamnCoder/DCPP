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
    public:
		const std::type_info& Type() const override { return typeid(CWindowSubsystem); }

    public:
    	void DisplayInfo(const TDisplayInfo& displayInfo)
    	{
    		m_displayInfo = displayInfo;
    	}

    public:
        CWindowSubsystem () : ISubsystem(), mp_window(0) {}
        CWindowSubsystem (const CWindowSubsystem& app) = delete;
        
        virtual ~CWindowSubsystem() {}
        
    public:
        void Initialize() override;
        
        void Terminate() override;

    public:
        IWindow* 		mp_window;
        TDisplayInfo 	m_displayInfo;
    };
}

#endif /* windowappsubsystem_hpp */
