//
//  modelcomponent.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "modelcomponent.h"

namespace dc
{
	void CModelComponent::AddVertexProperty(const char* name, int size)
	{
		static unsigned int identifier = 0;
		m_vertexProperties[name] = CVertexProperty(name, size, identifier++);
	}
	
	const TVertexPropertyMap CModelComponent::VertexProperties()
	{
		return m_vertexProperties;
	}
	
	void CModelComponent::Awake()
	{
		
	}
	
	void CModelComponent::Start()
	{
	}
}
