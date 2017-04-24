//
//  renderlayer.cpp
//  BitThemAll
//
//  Created by Jorge López González on 02/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "renderlayer.h"

namespace dc
{
	void CRenderLayer::PrepareRender()
	{
		
	}
	
	void CRenderLayer::Render()
	{
		for(auto* renderComponent : ml_renderList)
		{
			renderComponent->Render();
		}
	}
    
    void CRenderLayer::Add(CRendererComponent* newNode)
    {
		ml_renderList.push_back(newNode);
		printf("RenderLayer %d has %lu render components\n", LayerId(), ml_renderList.size());
    }
    
    void CRenderLayer::Remove(CRendererComponent* oldNode)
    {
    }

    
    void CRenderLayer::Clear()
    {
    }
    
}
