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
		
		CRenderLayer* renderLayer = CRenderer::Instance().RenderLayerManager()->Layer(GameObject()->LayerName());
		renderLayer->Add(this);
	}
	
	void CRendererComponent::Terminate()
	{
		CRenderLayer* renderLayer = CRenderer::Instance().RenderLayerManager()->Layer(GameObject()->LayerName());
		renderLayer->Remove(this);
	}
	
	void CRendererComponent::AddMaterial(CMaterial* material)
	{
		assert(material && "[CRendererComponent::AddMaterial] The material is NULL");
		
		m_materialList.push_back(material);
	}
	
	void CRendererComponent::Render()
	{
		extern void DrawElements(const ETopology& topology, const unsigned int indexCount);

		TMeshArray& meshArray = mp_modelComponent->Model()->MeshArray();
		
		for(CMesh* mesh : meshArray)
		{
			// Submission of VBO's
			
			TVertexProperty2VBOMap& dataVBOMap = mp_modelComponent->DataVBOMap(mesh);
			for(const auto& dataVBOEntry : dataVBOMap)
			{
				const TFloatVBO& dataVBOArray = dataVBOEntry.second;
				
				TFloatVBO::Submit(dataVBOArray);
			}
			
			TUIntVBO& indexVBO = mp_modelComponent->IndexVBO(mesh);
			TUIntVBO::Submit(indexVBO);
			
			// Activation of VBO
			for(const auto& dataVBOEntry : dataVBOMap)
			{
				const CVertexProperty* vertexProperty = dataVBOEntry.first;
				const TFloatVBO& dataVBOArray = dataVBOEntry.second;
				
				CVertexProperty::Activate(vertexProperty->Id(), dataVBOArray.Id(), dataVBOArray.TypeSize());
			}
			
			// Drawing
			DrawElements(ETopology::TRIANGLES, mesh->IndexCount());
		}
	}
}
