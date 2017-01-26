#ifndef MESHTATICO_H
#define MESHTATICO_H

#include "containers/array.h"
#include "vertices.h"

namespace dc
{
    
    class CMesh
    {
    // Constructores / Destructores
    public:
        CMesh():
            mv_center(),
            mv_size(),
            mn_indexCount(0),
            mn_vertexCount(0)
        {};
        
        ~CMesh() {}
        
        /**
         * Initializes all data of this model with a number of empty vertexes.
         */
        void Initialize(const int vertexCount, const int indexCount);
        
        /**
         * Resizes the mesh without modificate the current mesh data
         */
        void Resize(const int vertexCount, const int indexCount);
        
        /**
         * Merges this mesh with another one and stores the result in
         * this mesh. The other mesh is not modified at all in the process.
         * \param mesh the mesh you want to merge with this one.
         */
        CMesh* MergeWith(const CMesh* mesh);
        
        /**
         * Calculates size and center of this mesh.
         */
        void CalculateMeshDimensions();
        
    // Accesors
    public:
        const math::Vector3f&       Center() const { return mv_center; }
        const math::Vector3f&       Size() const { return mv_size; }
        const int                   IndexCount() const { return mn_indexCount; };
        const int                   VertexCount() const { return mn_vertexCount; };
        
        TMultiTextureVertex         GetVertex(const int index);
        
        const TFloatArray&			PositionArray() const { return m_positionArray; }
        const TFloatArray&			NormalArray() const { return m_normalArray; }
        const TFloatArray&			ColorArray() const { return m_colorArray; }
        const TFloatArray&			UV0Array() const { return m_uv0Array; }
        const TFloatArray&			UV1Array() const { return m_uv1Array; }
        const TUShortArray&			IndexArray() const { return m_indicesArray; }
        
        const bool                  IsValid() const
        {
            return m_indicesArray.IsValid() && m_positionArray.IsValid() && m_normalArray.IsValid() && m_colorArray.IsValid() && m_uv0Array.IsValid() && m_uv1Array.IsValid();
        }
    
    // Public interface
    public:
        void AddVertex(const TMultiTextureVertex& vertex);
        void AddIndex(const unsigned short index);

        void ReplaceVertex(const int index, const TMultiTextureVertex& vertex);
        
        void ReplaceVertexPosition(const int index, const math::Vector3f& position);
        void ReplaceVertexColor(const int index, const math::ColorRGBAf& color);
        
        // Reemplaza un array de vertices
        void ReplaceVerticesPosition(const int index, const math::Vector3f* posArray, const int length);
        
    // Atributes
    private:
        math::Vector3f      mv_center;
        math::Vector3f      mv_size;
        
        int                 mn_indexCount;
        int                 mn_vertexCount;
        
        TFloatArray  m_positionArray;
        TFloatArray  m_normalArray;
        TFloatArray  m_colorArray;
        TFloatArray  m_uv0Array;
        TFloatArray  m_uv1Array;
        
        TUShortArray m_indicesArray;
    };
}

#endif





