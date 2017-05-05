//
//  renderlayer.cpp
//  BitThemAll
//
//  Created by Jorge López González on 02/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "renderlayer.h"

#include <assert.h>

#include "renderer.h"
#include "component/gameobject.h"
#include "component/transform.h"
#include "component/modelcomponent.h"

namespace dc
{
	void CRenderLayer::PrepareRender()
	{
		for(CRendererComponent* renderComponent : m_renderList)
		{
			TMaterialList& materialList = renderComponent->Materials();
			for(CMaterial* material : materialList)
			{
				m_renderBatchMap[material].push_back(renderComponent);
			}
		}
	}
	
	/*
	 I need access to the camera's projection and view matrix
	 
	 I need access to every render component's transform
	 */
	void CRenderLayer::Render()
	{
		CCameraComponent* camera = CRenderer::Instance().Camera();
		math::Matrix4x4f projectionMatrix = camera->ProjectionMatrix();
		math::Matrix4x4f viewMatrix = camera->ViewMatrix();
		
		math::Matrix4x4f VP = projectionMatrix * viewMatrix;
		math::Matrix4x4f modelMatrix;
		math::Matrix4x4f MVP;
		
		for(auto& renderBatchEntry : m_renderBatchMap)
		{
			CMaterial* material = renderBatchEntry.first;
						
			material->Activate();
			
			std::vector<CRendererComponent*>& renderBatch = renderBatchEntry.second;
			for(CRendererComponent* renderComponent : renderBatch)
			{
				CGameObject* gameObject = renderComponent->GameObject();
				CTransform* transform = gameObject->GetComponent<CTransform>();
				//modelMatrix = transform->LocalMatrix();
				modelMatrix = transform->WorldMatrix();
				
				MVP = VP * modelMatrix;
				
				math::Vector3f forward = viewMatrix.Forward();
				
				math::Vector3f position = modelMatrix.Translation();
				printf("Camera forward [%f, %f, %f]\n", forward.x, forward.y, forward.z);
				printf("position %s [%f, %f, %f]\n", gameObject->Name(), position.x, position.y, position.z);
				
				IProperty* property = material->GetProperty("ShaderProgram");
				if(property)
				{
					CMaterialProperty<CShaderProgram>* shaderProperty = static_cast<CMaterialProperty<CShaderProgram>*>(property);
					shaderProperty->Value().PassMatrix4x4f("MVP", MVP);
				}
				
				const CVAO& vao = renderComponent->ModelComponent()->VAO(material);
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
