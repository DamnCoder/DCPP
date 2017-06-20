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
	const math::Matrix4x4f CTransform::WorldMatrix() const
	{
		CTransform* parentTrans = Parent();
		math::Matrix4x4f worldMatrix = LocalMatrix();
		
		while(parentTrans)
		{
			worldMatrix *= parentTrans->LocalMatrix();
			
			parentTrans = parentTrans->Parent();
		}
			
		return worldMatrix;
	}
	
	const bool CTransform::HasChild(CTransform* transform) const
	{
		for (const auto* child : m_children)
		{
			if (child == transform)
				return true;
		}
		return false;
	}
	
	void CTransform::Parent(CTransform* parent)
	{
		assert(parent && "[CTransform::Parent] You're adding a NULL pointer");
		
		mp_parent = parent;
		
		if(!mp_parent->HasChild(this))
		{
			mp_parent->Add(this);
		}
		
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
		m_matrix.Identify();
		mp_root = 0;
		mp_parent = 0;
		m_children.clear();
	}
	
	math::Vector3f CTransform::TransformPosition(const math::Vector3f& point)
	{
		return m_matrix.TransformPosition(point);
	}
	
	void CTransform::Add(CTransform* child)
	{
		assert(child && "[CTransform::Add] You're adding a NULL pointer");
		m_children.push_back(child);
		child->Parent(this);
	}
	
	void CTransform::Remove(CTransform* child)
	{
		assert(child && "[CTransform::Remove] You're removing a NULL pointer");
		m_children.erase(std::find(Begin(), End(), child));
		
		delete child;
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
