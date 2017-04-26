//
//  modelcomponent.hpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef modelcomponent_hpp
#define modelcomponent_hpp

#include "component.h"

#include "renderer/vao.h"

#include "mesh/model.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TVAOMap					= std::map<const CMaterial*, CVAO>;
	
	class CModelComponent : public CComponent
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		RTTI_DECLARATIONS(CModelComponent, CComponent)
		
	private:
		
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
		const CModel*	Model() const		{ return mp_model; }
		CModel*			Model()				{ return mp_model; }
		
		void			Model(CModel* model){ mp_model = model; }
		
		const CVAO&		VAO(const CMaterial* material) const;
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CModelComponent() :
			mp_model(0)
		{}
		
		~CModelComponent()
		{}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		void Initialize() override;
		
		void Awake() override;
		void Start() override;
		
		void Terminate() override;
		
		// ===========================================================
		// Methods
		// ===========================================================
		void SwapMaterials(CMaterial* oldMaterial, CMaterial* newMaterial);
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CModel*				mp_model;
		
		TVAOMap				m_vaoMap;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
}

#endif /* modelcomponent_hpp */
