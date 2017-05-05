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
		GLuint identifier;
		glGenVertexArrays(1, &identifier);
		
		TBufferMap bufferMap;
		// Access to mesh data arrays and relate them to the vertex properties
		for(const auto& vertexPropertyEntry : vertexPropertyMap)
		{
			const char* propertyName = vertexPropertyEntry.first;
			const CVertexProperty& vertexProperty = vertexPropertyEntry.second;
			
			TFloatArray& dataVBOArray = mesh->FloatDataArray(propertyName);
			const unsigned int elementNum = vertexProperty.Size();
			
			TFloatVBO dataVBO = TFloatVBO::Create(dataVBOArray, elementNum, EVBOTarget::ARRAY, EVBOUsage::STREAM_DRAW);
			
			bufferMap[&vertexProperty] = dataVBO;
		}
		
		// Access to mesh index array
		TUIntVBO indexVBO = TUIntVBO::Create(mesh->IndexArray(), 1, EVBOTarget::ELEMENT_ARRAY, EVBOUsage::STREAM_DRAW);
		
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
