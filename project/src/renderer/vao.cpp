//
//  vao.cpp
//  DCPPTest
//
//  Created by Jorge López on 26/4/17.
//
//

#include "vao.h"

#include "glwraps.h"

namespace dc
{
	CVAO CVAO::Create(CMesh* mesh, const TVertexPropertyMap& vertexPropertyMap)
	{
		printf("Generating VAO for %s\n", mesh->Name());
		GLuint identifier;
		glGenVertexArrays(1, &identifier);
		
		printf("VAO ID %d\n", identifier);
		
		TBufferMap bufferMap;
		// Access to mesh data arrays and relate them to the vertex properties
		for(const auto& vertexPropertyEntry : vertexPropertyMap)
		{
			const char* propertyName = vertexPropertyEntry.first;
			const CVertexProperty& vertexProperty = vertexPropertyEntry.second;
			
			TFloatArray& dataVBOArray = mesh->FloatDataArray(propertyName);
			const unsigned int elementNum = vertexProperty.Size();
			
			TFloatVBO dataVBO = TFloatVBO::Create(dataVBOArray, elementNum, EVBOTarget::ARRAY, EVBOUsage::STATIC_DRAW);
			
			printf("Property %s\n", propertyName);
			printf("Num of elements %u with type size %u\n", dataVBO.DataArray().Size(), dataVBO.TypeSize());
			
			bufferMap[&vertexProperty] = dataVBO;
		}
		
		// Access to mesh index array
		TUIntVBO indexVBO = TUIntVBO::Create(mesh->IndexArray(), 1, EVBOTarget::ELEMENT_ARRAY, EVBOUsage::STATIC_DRAW);
		printf("Indices\n");
		printf("Num of elements %u with type size %u\n", indexVBO.DataArray().Size(), indexVBO.TypeSize());
		return CVAO(identifier, indexVBO, bufferMap);
	}
	
	void CVAO::Submit(CVAO& vao)
	{
		const TBufferMap& dataVBOMap = vao.BufferMap();
		
		CVAO::Activate(vao);
		
		for(const auto& dataVBOEntry : dataVBOMap)
		{
			const CVertexProperty& vertexProperty = *dataVBOEntry.first;
			const TFloatVBO& dataVBOArray = dataVBOEntry.second;
			
			printf("%s\n", vertexProperty.Name());
			TFloatVBO::Submit(dataVBOArray);
			CVertexProperty::Activate(vertexProperty);
		}
		
		const TUIntVBO& indexVBO = vao.IndexVBO();
		TUIntVBO::Submit(indexVBO);
	}
	
	void CVAO::Activate(const CVAO& vao)
	{
		glBindVertexArray((GLuint)vao.Id());
	}
	
	void CVAO::Deactivate()
	{
		glBindVertexArray(0);
	}
}
