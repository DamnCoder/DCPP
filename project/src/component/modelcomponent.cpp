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
	TUIntVBO& CModelComponent::IndexVBO(const CMesh* mesh)
	{
		assert(mesh && "[CModelComponent::IndexVBO] The mesh is NULL");

		return m_uintVBOMap[mesh];
	}
	
	TVertexProperty2VBOMap& CModelComponent::DataVBOMap(const CMesh* mesh)
	{
		assert(mesh && "[CModelComponent::DataVBO] The mesh is NULL");
		return m_floatVBOMap[mesh];
	}
	
	void CModelComponent::Initialize()
	{
		const TVertexPropertyMap& vertexPropertyMap = CRenderer::Pointer()->VertexProperties();

		TMeshArray& meshArray = mp_model->MeshArray();
		
		for(CMesh* mesh : meshArray)
		{
			// Access to mesh index array
			TUIntArray& indexArray = mesh->IndexArray();
			TUIntVBO indexVBO = TUIntVBO::Create(indexArray, 1, EVBOTarget::ELEMENT_ARRAY, EVBOUsage::STREAM_DRAW);
			
			// Store of VBO for later use
			m_uintVBOMap[mesh] = indexVBO;
			
			
			// To store VBOs for later use
			TVertexProperty2VBOMap dataVBOMap = m_floatVBOMap[mesh];
			
			// Access to mesh data arrays
			for(const auto& vertexPropertyEntry : vertexPropertyMap)
			{
				const char* propertyName = vertexPropertyEntry.first;
				const CVertexProperty& vertexProperty = vertexPropertyEntry.second;
				
				const unsigned int elementNum = CVertexProperty::ElementNum(propertyName);
				
				TFloatArray& dataVBOArray = mesh->FloatDataArray(propertyName);
				TFloatVBO dataVBO = TFloatVBO::Create(dataVBOArray, elementNum, EVBOTarget::ARRAY, EVBOUsage::STREAM_DRAW);
				dataVBOMap[&vertexProperty] = dataVBO;
			}
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
	
	void CModelComponent::Render()
	{
		
	}
}
