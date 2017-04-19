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

#include "renderer/vertexproperty.h"
#include "renderer/vbo.h"

#include "mesh/model.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TVertexProperty2VBOMap	= std::map<const CVertexProperty*, TFloatVBO>;
	using TMeshFVBOMap				= std::map<const CMesh*, TVertexProperty2VBOMap>;
	using TMeshUintVBOMap			= std::map<const CMesh*, TUIntVBO>;
	
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
		const CModel*	Model() const	{ return mp_model; }
		CModel*			Model()			{ return mp_model; }
		
		void Model(CModel* model) { mp_model = model; }
		
		TUIntVBO&				IndexVBO(const CMesh* mesh);
		TVertexProperty2VBOMap& DataVBOMap(const CMesh* mesh);
		
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
		
		void Render();
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CModel*				mp_model;
		
		TMeshFVBOMap		m_floatVBOMap;
		TMeshUintVBOMap		m_uintVBOMap;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
}

#endif /* modelcomponent_hpp */
