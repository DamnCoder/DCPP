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

#include "help/deletehelp.h"

namespace dc
{
    void CRenderer::Initialize()
    {
		mp_renderLayerMgr = CRenderLayerManager::Pointer();
    }
	
    void CRenderer::Terminate()
    {
		CRenderLayerManager::Destroy();
		mp_renderLayerMgr = 0;
    }
	
	void CRenderer::Prepare()
	{
		
	}
	
	void CRenderer::Render()
	{
		for(auto renderLayer : mp_renderLayerMgr->RenderLayerList())
		{
			renderLayer->Render();
		}
	}

}
