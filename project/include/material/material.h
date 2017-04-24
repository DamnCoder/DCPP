//
//  material.h
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef material_h
#define material_h

#include <map>

#include "property.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TPropertiesMap = std::map<const char*, IProperty*>;
	
	class CMaterial
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
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
		const char* Name() const { return m_name; }
		
		IProperty*	GetProperty(const char* name);
		
		const bool Exists(const char* name) const;
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CMaterial(const char* name):
			m_name(name)
		{}
		
		~CMaterial()
		{}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
		void Activate();
		
		void AddProperty(const char* name, IProperty* property);
		
		
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		const char*		m_name;
		TPropertiesMap	m_propertiesMap;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
}

#endif /* material_hpp */
