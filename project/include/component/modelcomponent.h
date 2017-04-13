//
//  modelcomponent.hpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef modelcomponent_hpp
#define modelcomponent_hpp

#include <list>

#include "component.h"

#include "renderer/vbo.h"
#include "renderer/vertexproperty.h"

#include "material/material.h"
#include "mesh/model.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	class CModelComponent : public CComponent
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		RTTI_DECLARATIONS(CModelComponent, CComponent)
		
		using TMaterialList = std::list<CMaterial*>;
		
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
		void Model(CModel& model)
		{
			m_model = model;
		}
		
		void AddVertexProperty(const char* name, int size);
		
		const TVertexPropertyMap VertexProperties();

		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CModelComponent()
		{}
		
		~CModelComponent()
		{
			m_vertexProperties.clear();
		}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		void Awake() override;
		void Start() override;
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CModel					m_model;
		TMaterialList			m_materialList;
		
		TVertexPropertyMap		m_vertexProperties;
		
		TVBOMap<TFloatArray>	m_floatVBOMap;
		TVBOMap<TUIntArray>		m_uintVBOMap;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
}

#endif /* modelcomponent_hpp */
