//
//  vertices.h
//  BitThemAll
//
//  Created by Jorge López González on 31/10/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef BitThemAll_vertices_h
#define BitThemAll_vertices_h

#include "math/vector4.h"
#include "math/vector3.h"
#include "math/vector2.h"

namespace dc
{
    /**
     * Estructura basica de vertice de 32 bytes
     */
    struct TTextureVertex
    {
        TTextureVertex(math::Vector3f position,
                            math::Vector3f normal,
                            math::Vector2f uv0):
            position(position),
            normal(normal),
            uv0(uv0)
        {}
        
        math::Vector3f  position;   // 12 bytes
        math::Vector3f  normal;     // 12 bytes
        math::Vector2f  uv0;        // 8 bytes
    };
    
    /**
     * Estructura basica de vertice de 64 bytes
     */
    struct TMultiTextureVertex
    {
        TMultiTextureVertex(math::Vector3f position,
                            math::Vector3f normal,
                            math::Vector4f color,
                            math::Vector2f uv0,
                            math::Vector2f uv1):
            position(position),
            normal(normal),
            color(color),
            uv0(uv0),
            uv1(uv1)
        {}
        
        math::Vector3f  position;   // 12 bytes
        math::Vector3f  normal;     // 12 bytes
        math::Vector4f  color;      // 16 bytes
        math::Vector2f  uv0;        // 8 bytes
        math::Vector2f  uv1;        // 8 bytes
        float           padding[2]; // 8 bytes
    };
}

#endif