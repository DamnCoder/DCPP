//
//  vertexproperty.cpp
//  DCPPTest
//
//  Created by Jorge López on 31/3/17.
//
//

#include "vertexproperty.h"

namespace dc
{
	const char* CVertexProperty::IN_VERTEX	= "InVertex";
	const char* CVertexProperty::IN_NORMAL	= "InNormal";
	const char* CVertexProperty::IN_UV0		= "InUV0";
	const char* CVertexProperty::IN_COLOR	= "InColor";
	
	const unsigned int CVertexProperty::VERTEX_SIZE = 3;
	const unsigned int CVertexProperty::NORMAL_SIZE = 3;
	const unsigned int CVertexProperty::UV_SIZE = 2;
	const unsigned int CVertexProperty::COLOR_SIZE = 4;
	
	void CVertexProperty::Activate(const CVertexProperty& vertexProperty)
	{
		const GLuint attributeId = (GLuint)vertexProperty.Id();
		glEnableVertexAttribArray(attributeId);
		
		const GLint typeSize = (GLint)vertexProperty.Size();
		glVertexAttribPointer(
							  attributeId,				// attribute
							  typeSize,					// size
							  GL_FLOAT,					// type
							  GL_FALSE,					// normalized?
							  0,						// stride
							  (void*)0					// array buffer offset
							  );
	}
	
	void CVertexProperty::Deactivate(const CVertexProperty& vertexProperty)
	{
		glDisableVertexAttribArray(vertexProperty.Id());
	}
	
	const unsigned int CVertexProperty::ElementNum(const char* propertyName)
	{
		if(strcmp(propertyName, IN_VERTEX) == 0)
		{
			return VERTEX_SIZE;
		}
		else if(strcmp(propertyName, IN_NORMAL) == 0)
		{
			return NORMAL_SIZE;
		}
		if(strcmp(propertyName, IN_UV0) == 0)
		{
			return UV_SIZE;
		}
		if(strcmp(propertyName, IN_COLOR) == 0)
		{
			return COLOR_SIZE;
		}
		return 0;
	}
}
