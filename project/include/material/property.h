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

#include "math/dcmath.h"
#include "signals/signal.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	class IProperty
	{
	public:
		IProperty() {}
		virtual ~IProperty() {}
		
	public:
		virtual void Activate() const = 0;
		virtual void Deactivate() const = 0;
		
		virtual void CalculateOrder() = 0;
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
	public:
		const int MIN_PRIO = 0;
		const int MAX_PRIO = 9;
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
		
		const int	Order() const				{ return m_order; }
		
		const bool	Enabled() const				{ return m_enabled;}
		void		Enable(const bool enable)	{ m_enabled = enable; }
		
		const int	Priority() const			{ return m_priority; }
		void		Priority(const int priority)
		{ m_priority = math::Clamp(priority, MIN_PRIO, MAX_PRIO); }
		
		const T&	Value() const			{ return m_value; }
		void		Value(const T& value)	{ m_value = value; }
		
		CSignal<void(const T&)>&	ActivationCallback()
		{
			return m_activationCallback;
		}
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CMaterialProperty(const T& property):
			m_enabled(false),
			m_priority(0),
			m_order(0),
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
		void Activate() const override
		{
			if(Enabled())
			{
				m_activationCallback(m_value);
			}
		}
		
		void Deactivate() const override {}
		
		void CalculateOrder() override {}
		// ===========================================================
		// Fields
		// ===========================================================
	
	protected:
		
		bool				m_enabled;
		int					m_priority;
		int					m_order;
		
		T					m_value;
		
		CSignal<void(const T&)>	m_activationCallback;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* property_h */
