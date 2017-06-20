//
//  glwraps.h
//  BitThemAll
//
//  Created by Jorge López González on 08/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef BitThemAll_glwraps_h
#define BitThemAll_glwraps_h

/* If using gl3.h */
/* Ensure we are using opengl's core profile only */
#define GL3_PROTOTYPES 1

#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

/*
 #ifdef __APPLE__
 #define glGenVertexArrays glGenVertexArraysAPPLE
 #define glBindVertexArray glBindVertexArrayAPPLE
 #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
 #endif
 */

#include <math/vector3.h>
#include <math/vector4.h>

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
	
	enum EShaderType
	{
		VERTEX_SHADER	= GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
	};
	
	enum EPixelFormat
	{
		RGB				= GL_RGB,
		BGR				= GL_BGR,
		RGBA			= GL_RGBA,
		BGRA			= GL_BGRA
	};
	
	enum EWrap
	{
		REPEAT			= GL_REPEAT,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
	};
	
	enum EFiltering
	{
		NEAREST					= GL_NEAREST,
		LINEAR					= GL_LINEAR,
		NEAREST_MIPMAP_NEAREST	= GL_NEAREST_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR	= GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST	= GL_LINEAR_MIPMAP_NEAREST,
		LINEAR_MIPMAP_LINEAR	= GL_LINEAR_MIPMAP_LINEAR
	};
	
	enum EBlendMode
	{
		ADD,
		MULT,
		ALPHA,
		NORMAL,
		LIGHTMAP,
		INV_BACK,
		INV,
	};
	
	inline void DrawElements(const ETopology& topology, const unsigned int indexCount)
	{
		glDrawElements(topology, indexCount, GL_UNSIGNED_INT, 0);
	}
	
	inline void DrawArrays(const ETopology& topology, const unsigned int indexCount)
	{
		glDrawArrays((GLenum)topology,0, indexCount);
	}
	
	inline void ClearScreen(const math::ColorRGBf& screenColor)
	{
		glClearColor(screenColor.r, screenColor.g, screenColor.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	inline void ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	inline void ClearColor()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	inline void ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	
	inline void Enable(int mode)
	{
		glEnable((GLenum)mode);
	}
	
	inline void Disable(int mode)
	{
		glDisable((GLenum)mode);
	}
	
	inline void EnableBlending(const EBlendMode& mode)
	{
		GLenum sfactor;
		GLenum dfactor;
		
		switch (mode)
		{
			case EBlendMode::ADD:
				sfactor = GL_ONE;
				dfactor = GL_ONE;
				break;
			case EBlendMode::ALPHA:
				sfactor = GL_SRC_ALPHA;
				dfactor = GL_ONE;
				break;
			case EBlendMode::NORMAL:
				sfactor = GL_SRC_ALPHA;
				dfactor = GL_ONE_MINUS_SRC_ALPHA;
				break;
			case EBlendMode::MULT:
				sfactor = GL_ZERO;
				dfactor = GL_SRC_COLOR;
				break;
			case EBlendMode::LIGHTMAP:
				sfactor = GL_SRC_COLOR;
				dfactor = GL_DST_COLOR;
				break;
			case EBlendMode::INV_BACK:
				sfactor = GL_ONE_MINUS_DST_COLOR;
				dfactor = GL_ZERO;
				break;
			case EBlendMode::INV:
				sfactor = GL_ONE_MINUS_SRC_COLOR;
				dfactor = GL_ZERO;
				break;
		}
		
		glEnable(GL_BLEND);
		glBlendFunc(sfactor, dfactor);
	}
	
	inline void DisableBlending()
	{
		glDisable(GL_BLEND);
	}
}

#endif
