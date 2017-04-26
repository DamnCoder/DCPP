//
//  RendererComponent.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "renderercomponent.h"

#include "gameobject.h"

#include "modelcomponent.h"

#include "renderer/renderer.h"

namespace dc
{
	void CRendererComponent::Initialize()
	{
		mp_modelComponent = GameObject()->GetComponent<CModelComponent>();
		
		assert(mp_modelComponent && "[CRendererComponent::Initialize] You need a CModelComponent with a CRendererComponent");
		
		TMaterialArray materialArray = mp_modelComponent->Model()->Materials();
		
		for(CMaterial* material : materialArray)
		{
			AddMaterial(material);
		}
		
		// We add ourselves to the render layer
		CRenderLayer* renderLayer = CRenderer::Instance().RenderLayerManager()->Layer(GameObject()->LayerName());
		renderLayer->Add(this);
	}
	
	void CRendererComponent::Awake()
	{
		
	}
	
	void CRendererComponent::Terminate()
	{
		CRenderLayer* renderLayer = CRenderer::Instance().RenderLayerManager()->Layer(GameObject()->LayerName());
		renderLayer->Remove(this);
		
		mp_modelComponent = 0;
		m_materialList.clear();
	}
	
	void CRendererComponent::AddMaterial(CMaterial* material)
	{
		assert(material && "[CRendererComponent::AddMaterial] The material is NULL");
		
		m_materialList.push_back(material);
	}
	
	void CRendererComponent::SetMaterial(const unsigned int index, CMaterial* material)
	{
		assert(material && "[CRendererComponent::SetMaterial] The material is NULL");
		assert(index < m_materialList.size() && "[CRendererComponent::SetMaterial] The index is out of bounds!");
		
		CMaterial* previousMaterial = m_materialList[index];
		
		m_materialList[index] = material;
		
		mp_modelComponent->SwapMaterials(previousMaterial, material);
	}

}
