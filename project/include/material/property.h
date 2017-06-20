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
		T*		Value()			{ return m_value; }
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
	public:
		CPropertyEnabler(const int property): m_property(property)
		{}
		
	public:
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
		CBlending(const EBlendMode& mode) : m_mode (mode)
		{}
		
	public:
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
