//
//  renderlayer.h
//  BitThemAll
//
//  Created by Jorge López González on 02/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __BitThemAll__renderlayer__
#define __BitThemAll__renderlayer__

#include "component/renderercomponent.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
    /**
     * \class RenderLayer
     * \brief This class groups a subset of the graphic nodes for rendering
     * \author Jorge Lopez Gonzalez
     *
     * Holds a list of Nodes that should be rendered together. The graphics engine
     * will render a RenderLayer given to it, sorting the Nodes by distance to the camera node.
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
		const unsigned int			Count()			const { return ml_renderList.size(); }
		const TRenderComponentList&	RenderList()	const { return ml_renderList; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
    public:
        CRenderLayer()
        {}
        
        ~CRenderLayer()
        {};
        
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
    public:
		void Render();
		
        /**
         * Adds a node to this render group. Note that only the node is added, children and parent nodes
         * are not affected.
         * \param a the node.
         */
        void Add(CRendererComponent* renderComponent);

        /**
         * Removes a node from this render group. Note that only this node is removed, children and parent nodes
         * are not affected.
         * \param a the node.
         */
        void Remove(CRendererComponent* oldRenderComponent);
        
        void Clear();

		// ===========================================================
		// Fields
		// ===========================================================
    private:
        TRenderComponentList	ml_renderList;
    };
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* defined(__BitThemAll__renderlayer__) */
