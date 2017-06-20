//
//  property.h
//  DCPPTest
//
//  Created by Jorge López on 18/4/17.
//
//

#ifndef property_h
#define property_h

#include <functional>

#include <math/dcmath.h>

#include "material/shader.h"
#include "material/texture.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	class IProperty
	{
	public:
		const bool			Enabled() const					{ return m_enabled;}
		void				Enable(const bool enable)		{ m_enabled = enable; }
		
	public:
		IProperty(): m_enabled(false) {}
		virtual ~IProperty() {}
		
	public:
		virtual const bool Equals(const IProperty* property) const = 0;
		virtual void Activate() const = 0;
		virtual void Deactivate() const = 0;
		
	protected:
		bool m_enabled;
	};
	
	/**
	 * \class
	 * \brief
	 * \author Jorge Lopez Gonzalez
	 *
	 * Description.
	 */
	template<typename T>
	class CMaterialProperty : public IProperty
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
		T*		Value() const	{ return m_value; }
		void	Value(T* value)	{ m_value = value; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CMaterialProperty():
			IProperty(),
			m_value(0)
		{}
		
		CMaterialProperty(T* property):
			IProperty(),
			m_value(property)
		{}
		
		~CMaterialProperty()
		{}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		const bool Equals(const IProperty* property) const override;
		
		void Activate() const override;
		void Deactivate() const override;
		
		// ===========================================================
		// Fields
		// ===========================================================
	
	protected:
		T*	m_value;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================

	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
	
	template<typename T>
	const bool CMaterialProperty<T>::Equals(const IProperty* property) const
	{
		const auto* typedProperty = static_cast<const CMaterialProperty<T>*>(property);
		if(!typedProperty)
		{
			return false;
		}
		
		const T* value = typedProperty->Value();
		return m_value->Equals(value);
	}
	
	template<typename T>
	void CMaterialProperty<T>::Activate() const
	{
		if(Enabled())
		{
			m_value->Activate();
		}
	}
	
	template<typename T>
	void CMaterialProperty<T>::Deactivate() const
	{
		if(Enabled())
		{
			m_value->Deactivate();
		}
	}
	
	// ===========================================================
	// Other classes
	// ===========================================================
	
	class CPropertyEnabler
	{
		const int Property() const { return m_property; }
	public:
		CPropertyEnabler(const int property): m_property(property)
		{}
		
	public:
		const bool Equals(const CPropertyEnabler* propertyEnabler) const
		{
			return m_property == propertyEnabler->Property();
		}
		
		void Activate()
		{
			Enable(m_property);
		}
		
		void Deactivate()
		{
			Disable(m_property);
		}
		
	private:
		int m_property;
	};
	
	class CBlending
	{
	public:
		const EBlendMode& Mode() const { return m_mode; }
		
	public:
		CBlending(const EBlendMode& mode) : m_mode (mode)
		{}
		
	public:
		const bool Equals(const CBlending* blending) const
		{
			return m_mode == blending->Mode();
		}
		
		void Activate()
		{
			EnableBlending(m_mode);
		}
		
		void Deactivate()
		{
			DisableBlending();
		}
		
	private:
		EBlendMode	m_mode;
	};
}

#endif /* property_h */
