//
//  model.h
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef model_h
#define model_h

#include <map>

#include "mesh.h"

#include "material/material.h"
#include "containers/array.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TMeshArray		= CArray<CMesh*>;
	using TMaterialArray	= CArray<CMaterial*>;
	using TMeshMap			= std::map<CMaterial*, CMesh*>;
	
	class CModel
	{
		// ===========================================================
		// Constant / Enums / Typedefs
		// ===========================================================
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		void					MeshArray(TMeshArray& meshArray) { m_meshArray = meshArray; }
		
		const TMeshArray&		MeshArray() const	{ return m_meshArray; }
		
		const TMaterialArray&	Materials() const	{ return m_materialArray; }
		TMaterialArray&			Materials()			{ return m_materialArray; }
		
		CMesh* Mesh(CMaterial* material);
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CModel()
		{}
		
		CModel(TMeshArray& meshArray) : m_meshArray(meshArray)
		{}
		
		~CModel()
		{}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void Add(CMaterial* material, CMesh* mesh);
		
		void SwapMaterials(CMaterial* oldMaterial, CMaterial* newMaterial);
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		TMeshArray		m_meshArray;
		TMaterialArray	m_materialArray;
		
		TMeshMap		m_meshMap;
	};
	
}

#endif /* model_hpp */
