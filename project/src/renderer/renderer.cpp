//
//  renderer.cpp
//  BitThemAll
//
//  Created by Jorge López González on 07/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "renderer.h"

#include <assert.h>

#include "renderlayermanager.h"

namespace dc
{
	void CRenderer::AddVertexProperty(const char* name, const unsigned int size)
	{
		static unsigned int identifier = 0;
		m_vertexProperties[name] = CVertexProperty(name, size, identifier++);
	}
	
	const TVertexPropertyMap& CRenderer::VertexProperties() const
	{
		return m_vertexProperties;
	}
	
    void CRenderer::Initialize()
    {
		mp_renderLayerMgr = CRenderLayerManager::Pointer();
		
		AddVertexProperty(CVertexProperty::IN_VERTEX, 3);
		AddVertexProperty(CVertexProperty::IN_NORMAL, 3);
		AddVertexProperty(CVertexProperty::IN_UV0, 2);
    }
	
    void CRenderer::Terminate()
    {
		CRenderLayerManager::Destroy();
		mp_renderLayerMgr = 0;
    }
	
	void CRenderer::Prepare()
	{
		for(auto renderLayer : mp_renderLayerMgr->RenderLayerList())
		{
			renderLayer->PrepareRender();
		}
	}
	
	void CRenderer::Render()
	{
		// Clear the screen
		
		
		for(auto renderLayer : mp_renderLayerMgr->RenderLayerList())
		{
			renderLayer->Render();
		}
	}

}
