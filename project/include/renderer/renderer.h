//
//  renderer.h
//  BitThemAll
//
//  Created by Jorge López González on 07/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __BitThemAll__renderer__
#define __BitThemAll__renderer__

#include <vector>
#include <map>

#include "renderlayermanager.h"

#include "structures/singleton.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
    class CRenderer : public CSingleton<CRenderer>
    {
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		friend class CSingleton<CRenderer>;
		
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
		CRenderLayerManager* RenderLayerManager() const { return mp_renderLayerMgr; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
		
    public:
        CRenderer()
        {}
        
        ~CRenderer()
        {}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Initialize();
		void Terminate();
		
		void Prepare();
		
		void Render();
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CRenderLayerManager*	mp_renderLayerMgr;
		
    };
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
}
#endif /* defined(__BitThemAll__renderer__) */
