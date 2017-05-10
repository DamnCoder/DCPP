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
		IProperty() {}
		virtual ~IProperty() {}
		
	public:
		virtual void Activate() const = 0;
		virtual void Deactivate() const = 0;
	};
	
	inline void Activate(const CShaderProgram& program)
	{
		program.Activate();
	}
	
	inline void Deactivate(const CShaderProgram& program)
	{
		program.Deactivate();
	}
	
	inline void Activate(const CTexture& texture)
	{
		CTexture::Activate(texture);
	}
	
	inline void Deactivate(const CTexture& texture)
	{
		CTexture::Deactivate();
	}
	
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
		using TPropertyCallback = void (*)(const T&);
		
		using TPropertySignal = CSignal<void(const T&)>;
		
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
		
		const bool			Enabled() const					{ return m_enabled;}
		void				Enable(const bool enable)		{ m_enabled = enable; }
		
		T&					Value()							{ return m_value; }
		const T&			Value() const					{ return m_value; }
		void				Value(const T& value)			{ m_value = value; }
		
		TPropertySignal&	ActivationSignal()				{ return m_activationCallback; }
		TPropertySignal&	DeactivationSignal()			{ return m_deactivationCallback; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CMaterialProperty(const T& property):
			m_enabled(false),
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
			if(Enabled() && !m_activationCallback.IsEmpty())
			{
				m_activationCallback(m_value);
			}
		}
		
		void Deactivate() const override
		{
			if(Enabled() && !m_deactivationCallback.IsEmpty())
			{
				m_deactivationCallback(m_value);
			}
		}
		
		// ===========================================================
		// Fields
		// ===========================================================
	
	protected:
		
		bool			m_enabled;
		
		T				m_value;
		
		TPropertySignal	m_activationCallback;
		TPropertySignal	m_deactivationCallback;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* property_h */
