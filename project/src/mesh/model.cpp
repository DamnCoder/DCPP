//
//  model.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "model.h"

namespace dc
{
	CMesh* CModel::Mesh(CMaterial* material)
	{
		return m_meshMap[material];
	}
	
	void CModel::Add(CMaterial* material, CMesh* mesh)
	{
		m_meshMap[material] = mesh;
		
		m_meshArray.Append(mesh);
		m_materialArray.Append(material);
	}
	
	void CModel::SwapMaterials(CMaterial* oldMaterial, CMaterial* newMaterial)
	{
		// TODO: Change the material in the model too
	}
}
