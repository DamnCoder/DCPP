//
//  RendererComponent.hpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef RendererComponent_hpp
#define RendererComponent_hpp

#include <vector>

#include "component.h"

#include "material/material.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	class CModelComponent;
	
	using TMaterialList = std::vector<CMaterial*>;
	
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
	public:
		const TMaterialList&	Materials()			const	{ return m_materialList; }
		TMaterialList&			Materials()					{ return m_materialList; }
		
		CModelComponent*		ModelComponent()	const	{ return mp_modelComponent; }
		
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
	public:
		void Initialize() override;
		void Terminate() override;
		
		void Awake() override;
		void Start() override {}
		void Finish() override {}
		void Sleep() override {}
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void AddMaterial(CMaterial* material);
		
		void SetMaterial(const unsigned int index, CMaterial* material);
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CModelComponent*	mp_modelComponent;
		TMaterialList		m_materialList;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	using TRenderComponentList = std::vector<CRendererComponent*>;
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* RendererComponent_hpp */
