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
	
	class CMaterial
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
	private:
		using TPropertiesMap = std::map<const char*, IProperty*>;
		
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
		
		const bool	Exists(const char* name) const;
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CMaterial(const char* name):
			m_name(name)
		{}
		
		~CMaterial();
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Activate() const;
		
		void Deactivate() const;
		
		template<typename PT>
		void AddProperty(const char* name, const PT& propertyType, void(*activationCallback)(const PT&), void(*deactivationCallback)(const PT&));
		
	private:
		void AddIProperty(const char* name, IProperty* property);

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
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
	template<typename PT>
	void CMaterial::AddProperty(const char* name, const PT& propertyType, void(*activationCallback)(const PT&), void(*deactivationCallback)(const PT&))
	{
		CMaterialProperty<PT>* property = new CMaterialProperty<PT> (propertyType);
		property->ActivationSignal().Connect(activationCallback);
		property->DeactivationSignal().Connect(deactivationCallback);
		property->Enable(true);
		AddIProperty(name, property);
	}

}

#endif /* material_hpp */
