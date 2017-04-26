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
}
