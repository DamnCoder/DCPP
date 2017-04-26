//
//  modelcomponent.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "modelcomponent.h"

#include <assert.h>

#include "renderer/renderer.h"

namespace dc
{
	const CVAO& CModelComponent::VAO(const CMaterial* material) const
	{
		assert(material && "[CModelComponent::VAO] The material is NULL");
		return m_vaoMap.at(material);
	}

	void CModelComponent::Initialize()
	{
		const TVertexPropertyMap& vertexPropertyMap = CRenderer::Pointer()->VertexProperties();

		const TMaterialArray& materialArray = mp_model->Materials();
		
		for(CMaterial* material : materialArray)
		{
			CMesh* mesh = mp_model->Mesh(material);
			
			CVAO vao = CVAO::Create(mesh, vertexPropertyMap);
			CVAO::Submit(vao);
			
			m_vaoMap[material] = vao;
		}
	}
	
	void CModelComponent::Awake()
	{
		
	}
	
	void CModelComponent::Start()
	{
	}
	
	void CModelComponent::Terminate()
	{
		
	}
	
	void CModelComponent::SwapMaterials(CMaterial* oldMaterial, CMaterial* newMaterial)
	{
		assert(oldMaterial && newMaterial && "[CModelComponent::SwapMaterials] One of the materials is NULL");
		
		TVAOMap::iterator it = m_vaoMap.find(oldMaterial);
		
		assert(it != m_vaoMap.end() && "[CModelComponent::SwapMaterials] The material you are trying to swap doesn't exist!");
		
		CVAO& vao = it->second;
		m_vaoMap[newMaterial] = vao;
		
		m_vaoMap.erase(it);
		
		mp_model->SwapMaterials(oldMaterial, newMaterial);
	}
}
