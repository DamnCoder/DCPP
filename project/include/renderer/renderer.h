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
#include "vertexproperty.h"

#include "structures/singleton.h"

#include "component/camera.h"

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
		
		void Camera(CCameraComponent* camera) { mp_currentCamera = camera; }
		
		void AddVertexProperty(const char* name, const unsigned int size);
		
		const TVertexPropertyMap& VertexProperties() const;
		
		// ===========================================================
		// Constructors
		// ===========================================================
		
    public:
        CRenderer()
        {}
        
        ~CRenderer()
        {
			m_vertexProperties.clear();
		}
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
		
		void Finish();
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CRenderLayerManager*			mp_renderLayerMgr;
		TVertexPropertyMap				m_vertexProperties;
		
		CCameraComponent*				mp_currentCamera;
    };
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
}
#endif /* defined(__BitThemAll__renderer__) */
