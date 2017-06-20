//
//  material.h
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef material_h
#define material_h

#include <string>
#include <map>
#include <vector>

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
		using TPropertiesMap = std::map<std::string, IProperty*>;
		using TPropertiesList = std::vector<IProperty*>;
		
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
		const std::string&		Name() const { return m_name; }
		
		template<typename PT>
		CMaterialProperty<PT>*	GetTypedProperty(const std::string& name);
		
		IProperty*				GetProperty(const std::string& name);
		
		const bool				Exists(const std::string& name) const;
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CMaterial(const std::string& name):
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
		CMaterialProperty<PT>* AddProperty(const std::string& name, PT* propertyType);
		
		template<typename PT>
		CMaterialProperty<PT>* AddProperty(const std::string& name);
		
		CMaterialProperty<CBlending>* AddProperty(const std::string& name, const EBlendMode& blending);
		
	private:
		void AddIProperty(const std::string& name, IProperty* property);

		// ===========================================================
		// Fields
		// ===========================================================
	private:
		std::string		m_name;
		
		// map to make fast the get
		TPropertiesMap	m_propertiesMap;
		
		// vector to make fast and ordered the iteration
		TPropertiesList	m_propertiesList;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
	template<typename PT>
	CMaterialProperty<PT>*	CMaterial::GetTypedProperty(const std::string& name)
	{
		IProperty* property = GetProperty(name);
		if(property)
		{
			return static_cast<CMaterialProperty<PT>*>(property);
		}
		return 0;
	}
	
	template<typename PT>
	inline
	CMaterialProperty<PT>* CMaterial::AddProperty(const std::string& name, PT* propertyType)
	{
		CMaterialProperty<PT>* property = new CMaterialProperty<PT> (propertyType);
		property->Enable(true);
		AddIProperty(name, property);
		return property;
	}
	
	template<typename PT>
	inline
	CMaterialProperty<PT>* CMaterial::AddProperty(const std::string& name)
	{
		CMaterialProperty<PT>* property = new CMaterialProperty<PT> ();
		property->Enable(false);
		AddIProperty(name, property);
		return property;
	}
}

#endif /* material_hpp */
