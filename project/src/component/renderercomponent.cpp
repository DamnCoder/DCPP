//
//  RendererComponent.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "renderercomponent.h"

#include "gameobject.h"

#include "renderer/renderer.h"

namespace dc
{
	void CRendererComponent::Initialize()
	{
		mp_modelComponent = GameObject()->GetComponent<CModelComponent>();
		
		assert(mp_modelComponent && "You need a CModelComponent with a CRendererComponent");
		
		CRenderLayer* renderLayer = CRenderer::Instance().RenderLayerManager()->Layer(GameObject()->LayerName());
		renderLayer->Add(this);
	}
	
	void CRendererComponent::Terminate()
	{
		
	}
	
}
