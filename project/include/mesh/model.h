//
//  model.hpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef model_hpp
#define model_hpp

#include "mesh.h"
#include "containers/array.h"

namespace dc
{
	
	class CModel
	{
		// ===========================================================
		// Constant / Enums / Typedefs
		// ===========================================================
		using TMeshArray = CArray<CMesh*>;
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
		void MeshArray(TMeshArray& meshArray)
		{
			m_meshArray = meshArray;
		}
		
		const TMeshArray& MeshArray() const
		{
			return m_meshArray;
		}
		
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
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		TMeshArray m_meshArray;
	};
	
}

#endif /* model_hpp */
