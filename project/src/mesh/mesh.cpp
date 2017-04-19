#include "mesh.h"

//#include <climits>

namespace dc
{
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

}
