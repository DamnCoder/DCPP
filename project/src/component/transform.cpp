//
//  transform.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "transform.h"

#include <assert.h>

namespace dc
{
	math::Matrix4x4f CTransform::WorldMatrix() const
	{
		if (mp_parent)
		{
			return mp_parent->WorldMatrix() * m_matrix;
		}
		return m_matrix;
	}
	
	void CTransform::Parent(CTransform* parent)
	{
		assert(parent != 0);
		mp_parent = parent;
		mp_parent->AddChild(this);
		
		if (!parent->Root())
		{
			mp_root = parent;
		}
		else
		{
			mp_root = parent->Root();
		}
	}
	
	void CTransform::Reset()
	{
		m_matrix.Identity();
		mp_root = 0;
		mp_parent = 0;
		ml_childs.clear();
	}
	
	math::Vector3f CTransform::TransformPosition(const math::Vector3f& point)
	{
		return m_matrix.TransformPosition(point);
	}
	
	void CTransform::AddChild(CTransform* child)
	{
		assert(child != 0);
		ml_childs.push_back(child);
	}
	
	void CTransform::Translate(const math::Vector3f& position)
	{
		m_matrix.Translate(position);
	}
	
	void CTransform::Rotate(const math::Vector3f& rotation)
	{
		m_matrix.Rotate(rotation);
	}
	
	void CTransform::Scale(const math::Vector3f& scale)
	{
		m_matrix.Scale(scale);
	}

}
