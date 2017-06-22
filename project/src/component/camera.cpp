//
//  camera.cpp
//  DCPPTest
//
//  Created by Jorge López on 14/4/17.
//
//

#include "camera.h"

#include <assert.h>

#include "renderer/renderer.h"

#include "gameobject.h"
#include "transform.h"

namespace dc
{
	const math::Matrix4x4f CCameraComponent::ModelViewProjection (const CTransform* modelTransform) const
	{
		return ProjectionMatrix() * ViewMatrix() * modelTransform->LocalMatrix();
	}
	
	void CCameraComponent::Initialize()
	{
		CRenderer::Pointer()->Camera(this);
	}
	
	void CCameraComponent::Configure(const float fov, const float aspectRatio, const float near, const float far)
	{
		m_fov = fov;
		m_aspectRatio = aspectRatio;
		m_near = near;
		m_far = far;
		
		m_projectionMatrix = math::Matrix4x4f::Perspective(fov, aspectRatio, near, far);
		
		CTransform* transform = GameObject()->GetComponent<CTransform>();
		math::Matrix4x4f worldMatrix = transform->WorldMatrix();
		
		assert(transform && "The camera component needs its game object to have a transform");
		
		m_viewMatrix = math::Matrix4x4f::LookAt(worldMatrix.Position(), worldMatrix.Position() + worldMatrix.Forward(), worldMatrix.Up());
	}
}
