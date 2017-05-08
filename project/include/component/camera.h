//
//  camera.h
//  DCPP
//
//  Created by Jorge López on 14/4/17.
//
//

#ifndef camera_h
#define camera_h

#include "component.h"

#include "math/matrix.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	class CTransform;
	
	/**
	 * \class
	 * \brief
	 * \author Jorge Lopez Gonzalez
	 *
	 * Description.
	 */
	class CCameraComponent : public CComponent
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		RTTI_DECLARATIONS(CCameraComponent, CComponent)
		
	private:
		const float FOV_DEF		= 90.f;
		const float AR_DEF		= 4.f / 3.f;
		const float NEAR_DEF	= 1.f;
		const float FAR_DEF		= 1000.f;
		
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
		const math::ColorRGBf&	BackgroundColor() const { return m_backgroundColor; }
		void					BackgroundColor(const math::ColorRGBf& color) { m_backgroundColor = color; }
		
		const float FOV() const { return m_fov; }
		void		FOV(const float fov)
		{
			Configure(fov, m_aspectRatio, m_near, m_far);
		}
		
		const float AspectRatio() const { return m_aspectRatio; }
		void		AspectRatio(const float aspectRatio)
		{
			Configure(m_fov, aspectRatio, m_near, m_far);
		}
		
		const float Near() const { return m_near; }
		void		Near(const float near)
		{
			Configure(m_fov, m_aspectRatio, near, m_far);
		}
		
		const float Far() const { return m_far; }
		void		Far(const float far)
		{
			Configure(m_fov, m_aspectRatio, m_near, far);
		}
		
		const math::Matrix4x4f	ModelViewProjection (const CTransform* modelTransform) const;
		
		const math::Matrix4x4f	ViewMatrix() const { return m_viewMatrix; }
		void					ViewMatrix(const math::Matrix4x4f& viewMatrix) { m_viewMatrix = viewMatrix; }
		
		const math::Matrix4x4f& ProjectionMatrix() const { return m_projectionMatrix; }
		void					ProjectionMatrix(const math::Matrix4x4f& projectionMatrix) { m_projectionMatrix = projectionMatrix; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CCameraComponent()
		{}
		
		~CCameraComponent()
		{}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void Initialize() override;
		void Terminate() override {}
		
		void Awake() override {}
		void Start() override {}
		void Finish() override {}
		void Sleep() override {}
		
		// ===========================================================
		// Methods
		// ===========================================================
		//Real fovY, Real aspect, Real near, Real far
		void Configure(const float fov, const float aspectRatio, const float near, const float far);
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		float				m_fov;
		float				m_aspectRatio;
		float				m_near;
		float				m_far;
		
		math::ColorRGBf		m_backgroundColor;
		
		math::Matrix4x4f	m_viewMatrix;
		math::Matrix4x4f	m_projectionMatrix;
		
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}


#endif /* camera_hpp */
