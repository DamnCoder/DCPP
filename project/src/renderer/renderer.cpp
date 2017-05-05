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
		mp_renderLayerMgr = CRenderLayerManager::New();
		
		AddVertexProperty(CVertexProperty::IN_VERTEX, CVertexProperty::VERTEX_SIZE);
		AddVertexProperty(CVertexProperty::IN_NORMAL, CVertexProperty::NORMAL_SIZE);
		AddVertexProperty(CVertexProperty::IN_UV0	, CVertexProperty::UV_SIZE);
		AddVertexProperty(CVertexProperty::IN_COLOR	, CVertexProperty::COLOR_SIZE);
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
		if(mp_currentCamera)
		{
			ClearScreen(mp_currentCamera->BackgroundColor());
		}
		else
		{
			ClearScreen();
		}
		
		for(auto renderLayer : mp_renderLayerMgr->RenderLayerList())
		{
			renderLayer->Render();
		}
	}
	
	void CRenderer::Finish()
	{
		for(auto renderLayer : mp_renderLayerMgr->RenderLayerList())
		{
			renderLayer->Finish();
		}
	}
}
