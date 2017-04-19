//
//  glwraps.h
//  BitThemAll
//
//  Created by Jorge López González on 08/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef BitThemAll_glwraps_h
#define BitThemAll_glwraps_h

#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

namespace dc
{
	enum ETopology
	{
		LINES			= GL_LINES,
		LINE_LOOP		= GL_LINE_LOOP,
		LINE_STRIP		= GL_LINE_STRIP,
		TRIANGLES		= GL_TRIANGLES,
		TRIANGLE_STRIP	= GL_TRIANGLE_STRIP,
		TRIANGLE_FAN	= GL_TRIANGLE_FAN,
	};
	
	enum EVBOUsage
	{
		STATIC_COPY		= GL_STATIC_COPY,
		STATIC_DRAW		= GL_STATIC_DRAW,
		STATIC_READ		= GL_STATIC_READ,
		DYNAMIC_COPY	= GL_DYNAMIC_COPY,
		DYNAMIC_DRAW	= GL_DYNAMIC_DRAW,
		DYNAMIC_READ	= GL_DYNAMIC_READ,
		STREAM_COPY		= GL_STREAM_COPY,
		STREAM_DRAW		= GL_STREAM_DRAW,
		STREAM_READ		= GL_STREAM_READ,
	};
	
	enum EVBOTarget
	{
		ELEMENT_ARRAY	= GL_ELEMENT_ARRAY_BUFFER,
		ARRAY			= GL_ARRAY_BUFFER,
	};
	//*
	inline void DrawElements(const ETopology& topology, const unsigned int indexCount)
	{
		glDrawElements((GLenum)topology, (GLsizei)indexCount, GL_UNSIGNED_SHORT, 0);
	}
	//*/
}

#endif
