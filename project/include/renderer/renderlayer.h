//
//  renderlayer.h
//  BitThemAll
//
//  Created by Jorge López González on 02/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __renderlayer__
#define __renderlayer__

#include "component/renderercomponent.h"

#include "renderer/vao.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TRenderBatchMap = std::map<CMaterial*, std::vector<CRendererComponent*>>;
	
    /**
     * \class RenderLayer
     * \brief This class groups a subset of the graphic nodes for rendering
     * \author Jorge Lopez Gonzalez
     */
    class CRenderLayer
    {
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		
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
		const unsigned int			LayerId()		const { return m_layerId; }
		void LayerId(const unsigned int identifier)
		{
			m_layerId = identifier;
		}
		
		const unsigned int			Count()			const { return m_renderList.size(); }
		const TRenderComponentList&	RenderList()	const { return m_renderList; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
    public:
		CRenderLayer():
			m_layerId(0)
        {}
		
		CRenderLayer(const unsigned int layerIdentifier):
			m_layerId(layerIdentifier)
		{}
		
        ~CRenderLayer()
        {};
		
		CRenderLayer(const CRenderLayer& copy) = delete;
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void operator= (const CRenderLayer& copy) = delete;
		
		// ===========================================================
		// Methods
		// ===========================================================
    public:
		void PrepareRender();
		
		void Render();
		
		void Finish();

        void Add(CRendererComponent* renderComponent);

        void Remove(CRendererComponent* oldRenderComponent);
        
        void Clear();

		// ===========================================================
		// Fields
		// ===========================================================
    private:
		unsigned int			m_layerId;
        TRenderComponentList	m_renderList;
		TRenderBatchMap			m_renderBatchMap;
    };
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* defined(__renderlayer__) */
