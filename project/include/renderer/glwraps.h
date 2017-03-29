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

#include "mesh/mesh.h"

namespace dc
{
	enum EVBOUsage
	{
		STATIC_COPY = GL_STATIC_COPY,
		STATIC_DRAW = GL_STATIC_DRAW,
		STATIC_READ = GL_STATIC_READ,
		DYNAMIC_COPY = GL_DYNAMIC_COPY,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		STREAM_COPY = GL_STREAM_COPY,
		STREAM_DRAW = GL_STREAM_DRAW,
		STREAM_READ = GL_STREAM_READ,
	};
	
	enum EVBOTarget
	{
		ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
		ARRAY = GL_ARRAY_BUFFER,
	};
	
    struct DrawTris
    {
        void operator()(const CMesh* mesh) const
        {
            glDrawElements(GL_TRIANGLES, mesh->IndexCount(), GL_UNSIGNED_SHORT, 0);
        }
        
    };
    
    struct DrawLines
    {
        void operator()(const CMesh* mesh) const
        {
            glDrawElements(GL_LINES, mesh->IndexCount(), GL_UNSIGNED_SHORT,0);
        }
        
    };
    
    struct DrawTriangleStrip
    {
        void operator()(const CMesh* mesh) const
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->IndexCount());
        }
        
    };
}

#endif
