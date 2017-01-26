#include "mesh.h"

namespace dc
{
	//------------------------------------------------------------//
	// Mesh init operations
	//------------------------------------------------------------//
	void CMesh::Initialize(const int vertexCount, const int indexCount)
	{
		mn_vertexCount = vertexCount;
		mn_indexCount = indexCount;
		
		const int v2Elements = mn_vertexCount * 2;
		const int v3Elements = mn_vertexCount * 3;
		const int v4Elements = mn_vertexCount * 4;
		
		m_positionArray.Init(v3Elements);
		m_normalArray.Init(v3Elements);
		m_colorArray.Init(v4Elements);
		m_uv0Array.Init(v2Elements);
		m_uv1Array.Init(v2Elements);
		m_indicesArray.Init(mn_indexCount);
	}
	
	void CMesh::Resize(const int vertexCount, const int indexCount)
	{
		mn_vertexCount = VertexCount() + vertexCount;
		mn_indexCount = IndexCount() + indexCount;
		
		const int v2Elements = mn_vertexCount * 2;
		const int v3Elements = mn_vertexCount * 3;
		const int v4Elements = mn_vertexCount * 4;
		
		m_positionArray.Resize(v3Elements);
		m_normalArray.Resize(v3Elements);
		m_colorArray.Resize(v4Elements);
		m_uv0Array.Resize(v2Elements);
		m_uv1Array.Resize(v2Elements);
		m_indicesArray.Resize(mn_indexCount);
	}
	
	CMesh* CMesh::MergeWith(const CMesh* mesh)
	{
		// Adaptamos el tamaño de la malla para que de cabida a la informacion de las dos mallas
		mn_vertexCount += mesh->VertexCount();
		mn_indexCount += mesh->IndexCount();
		
		// Repasamos los elementos nuevos para incluirlos en la malla
		m_positionArray.Merge(mesh->PositionArray());
		m_normalArray.Merge(mesh->NormalArray());
		m_colorArray.Merge(mesh->ColorArray());
		m_uv0Array.Merge(mesh->UV0Array());
		m_uv1Array.Merge(mesh->UV1Array());
		
		m_indicesArray.Merge(mesh->IndexArray());
		
		CalculateMeshDimensions();
		return this;
	}
	
	void CMesh::CalculateMeshDimensions()
	{
		float mx, my, mz;
		float px, py, pz;
		float tx, ty, tz;
		
		mx = my = mz = -INT_MAX;
		px = py = pz = INT_MAX;
		
		for (unsigned int i = 0; i < mn_indexCount*3; i+=3)
		{
			tx = m_positionArray.At(i);
			ty = m_positionArray.At(i+1);
			tz = m_positionArray.At(i+2);
			
			if (tx > mx) mx = tx;
			else if (tx < px) px = tx;
			
			if (ty > my) my = ty;
			else if (ty < py) py = ty;
			
			if (tz > mz) mz = tz;
			else if (tz < pz) pz = tz;
		}
		mv_size.SetCoords(mx - px, my - py, mz - pz);
		mv_center.SetCoords(mx - mv_size.x * 0.5f,
							my - mv_size.y * 0.5f,
							mz - mv_size.z * 0.5f);
	}
	
	
	
	//------------------------------------------------------------//
	// Mesh accesor operations
	//------------------------------------------------------------//
	TMultiTextureVertex CMesh::GetVertex(const int index)
	{
		const int v2Index = index*2;
		const int v3Index = index*3;
		const int v4Index = index*4;
		math::Vector3f position(m_positionArray[v3Index], m_positionArray[v3Index+1], m_positionArray[v3Index+2]);
		math::Vector3f normal(m_normalArray[v3Index], m_normalArray[v3Index+1], m_normalArray[v3Index+2]);
		math::Vector4f color(m_colorArray[v4Index], m_colorArray[v4Index+1], m_colorArray[v4Index+2], m_colorArray[v4Index+3]);
		math::Vector2f uv0(m_uv0Array[v2Index], m_uv0Array[v2Index+1]);
		math::Vector2f uv1(m_uv1Array[v2Index], m_uv1Array[v2Index+1]);
		
		return TMultiTextureVertex(position, normal, color, uv0, uv1);
	}
	
	//------------------------------------------------------------//
	// Mesh modification operations
	//------------------------------------------------------------//
	
	void CMesh::AddVertex(const TMultiTextureVertex& vertex)
	{
		m_positionArray.Append(vertex.position, 3);
		m_normalArray.Append(vertex.normal, 3);
		m_colorArray.Append(vertex.color, 4);
		m_uv0Array.Append(vertex.uv0, 2);
		m_uv1Array.Append(vertex.uv1, 2);
	}
	
	void CMesh::AddIndex(const unsigned short index)
	{
		m_indicesArray.Append(index);
	}
	
	void CMesh::ReplaceVertex(const int index, const TMultiTextureVertex& vertex)
	{
		m_positionArray.Set(3*index, vertex.position, 3);
		m_normalArray.Set(3*index, vertex.normal, 3);
		m_colorArray.Set(4*index, vertex.color, 4);
		m_uv0Array.Set(2*index, vertex.uv0, 2);
		m_uv1Array.Set(2*index, vertex.uv1, 2);
	}
	
	void CMesh::ReplaceVertexPosition(const int index, const math::Vector3f& position)
	{
		m_positionArray.Set(3*index, position, 3);
	}
	
	void CMesh::ReplaceVertexColor(const int index, const math::ColorRGBAf& color)
	{
		m_colorArray.Set(4*index, color, 4);
	}
	
	void CMesh::ReplaceVerticesPosition(const int index, const math::Vector3f* posArray, const int length)
	{
		int positionIndex = 3*index;
		for(int posArrayIndex = 0; posArrayIndex < length; ++posArrayIndex)
		{
			m_positionArray.Set(index, posArray[posArrayIndex], 3);
			positionIndex += 3;
		}
	}
}