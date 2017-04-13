//
//  RendererComponent.hpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef RendererComponent_hpp
#define RendererComponent_hpp

#include "component.h"

#include "modelcomponent.h"

#include "containers/array.h"

#include "material/material.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TMaterialArray = CArray<CMaterial>;
	
	class CRendererComponent : public CComponent
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		RTTI_DECLARATIONS(CRendererComponent, CComponent)
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CRendererComponent():
			mp_modelComponent (0)
		{}
		
		~CRendererComponent()
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
		CModelComponent*	mp_modelComponent;
		TMaterialArray		m_materialArray;
	};
	
}

#endif /* RendererComponent_hpp */
