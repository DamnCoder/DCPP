//
//  renderlayer.cpp
//  BitThemAll
//
//  Created by Jorge López González on 02/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "renderlayer.h"

#include <assert.h>

#include "component/modelcomponent.h"

namespace dc
{
	void CRenderLayer::PrepareRender()
	{
		for(const CRendererComponent* renderComponent : m_renderList)
		{
			const CModelComponent* modelComponent = renderComponent->ModelComponent();
			
			const TMaterialList& materialList = renderComponent->Materials();
			for(const CMaterial* material : materialList)
			{
				const CVAO& vao = modelComponent->VAO(material);
				
				m_renderBatchMap[material].push_back(vao);
			}
		}
	}
	
	void CRenderLayer::Render()
	{
		for(const auto& renderBatchEntry : m_renderBatchMap)
		{
			const CMaterial* material = renderBatchEntry.first;
						
			material->Activate();
			
			const TVAOList& renderBatch = renderBatchEntry.second;
			for(const CVAO& vao : renderBatch)
			{
				CVAO::Activate(vao);
				DrawElements(ETopology::TRIANGLES, vao.IndexVBO().DataArray().Size());
			}
			
			CVAO::Deactivate();
			
			material->Deactivate();
		}
	}
	
	void CRenderLayer::Finish()
	{
		m_renderBatchMap.clear();
	}
    
    void CRenderLayer::Add(CRendererComponent* renderComponent)
    {
		assert(renderComponent && "[CRenderLayer::Add] You are trying to add a NULL CRenderComponent");
		m_renderList.push_back(renderComponent);

		printf("RenderLayer %d has %lu render components\n", LayerId(), m_renderList.size());
    }
    
    void CRenderLayer::Remove(CRendererComponent* oldRenderComponent)
    {
    }

    
    void CRenderLayer::Clear()
    {
    }
    
}
