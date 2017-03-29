#include "mesh.h"

#include <climits>

namespace dc
{
	const char* CMesh::VERTEX_ID	= "InVertex";
	const char* CMesh::NORMAL_ID	= "InNormal";
	const char* CMesh::UV0_ID		= "InUV0";
	const char* CMesh::UV1_ID		= "InUV1";
	const char* CMesh::COLOR_ID		= "InColor";
	
	const char* CMesh::INDICES_ID	= "InIndices";
	
	const bool CMesh::IsValid() const
	{
		bool valid = true;
		for(auto& arrayEntry : m_floatDataMap)
		{
			valid &= arrayEntry.second.IsValid();
		}
		return valid;
	}
	
	TFloatArray& CMesh::FloatDataArray(const char* id)
	{
		return m_floatDataMap[id];
	}
	
	void CMesh::FloatDataArray(const char *id, TFloatArray &floatArray)
	{
		m_floatDataMap[id] = floatArray;
	}
	
	void CMesh::AddFloatDataArray(const char* id, TFloatArray& floatArray)
	{
		m_floatDataMap[id].Append(floatArray, floatArray.Size());
	}
	
	//------------------------------------------------------------//
	// Mesh init operations
	//------------------------------------------------------------//
	CMesh* CMesh::MergeWith(const CMesh* mesh)
	{
		// Adaptation of the mesh size to make it fit both meshes
		m_vertexCount += mesh->VertexCount();
		m_indexCount += mesh->IndexCount();
		
		//m_vertexArray.Merge(mesh->VertexArray());
		//m_normalArray.Merge(mesh->NormalArray());
		//m_colorArray.Merge(mesh->ColorArray());
		//m_uv0Array.Merge(mesh->UV0Array());
		//m_uv1Array.Merge(mesh->UV1Array());
		
		//m_indicesArray.Merge(mesh->IndexArray());
		
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
		
		const TFloatArray& m_vertexArray = FloatDataArray(VERTEX_ID);
		
		for (unsigned int i = 0; i < m_indexCount*3; i+=3)
		{
			tx = m_vertexArray.At(i);
			ty = m_vertexArray.At(i+1);
			tz = m_vertexArray.At(i+2);
			
			if (tx > mx)
				mx = tx;
			else if (tx < px)
				px = tx;
			
			if (ty > my)
				my = ty;
			else if (ty < py)
				py = ty;
			
			if (tz > mz)
				mz = tz;
			else if (tz < pz)
				pz = tz;
		}
		m_size.SetCoords(mx - px, my - py, mz - pz);
		m_center.SetCoords(mx - m_size.x * 0.5f,
							my - m_size.y * 0.5f,
							mz - m_size.z * 0.5f);
	}
}
