//
//  transform.cpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#include "transform.h"

#include "gameobject.h"

#include <assert.h>

namespace dc
{
	void CTransform::LocalMatrix(const math::Matrix4x4f& matrix)
	{
		m_localMatrix = matrix;
		m_position = m_localMatrix.Position();
		m_rotation = m_localMatrix.Rotation();
		m_scale = m_localMatrix.Scale();
	}
	
	const math::Matrix4x4f& CTransform::LocalMatrix() const
	{
		return m_localMatrix;
	}

	const math::Matrix4x4f& CTransform::WorldMatrix() const
	{
		return m_globalMatrix;
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
		
		// If it's the same we do nothing
		if(mp_parent == parent)
		{
			return;
		}
		
		// If it already has a parent, first we need to remove ourselves from its list of children
		if(mp_parent)
		{
			mp_parent->Remove(this);
		}
		
		mp_parent = parent;

		// If we are not already a child we add ourselves as child
		if(!mp_parent->HasChild(this))
		{
			mp_parent->Add(this);
		}
		
		// If
		if (!mp_parent->Root())
		{
			Root(mp_parent);
		}
		else
		{
			Root(mp_parent->Root());
		}
		
		CalculateTransforms();
	}
	
	void CTransform::Root(CTransform* root)
	{
		mp_root = root;
		
		for(auto* child : m_children)
		{
			child->Root(root);
		}
	}
	
	math::Vector3f CTransform::EulerAngles()
	{
		math::Vector3f radAngles =  WorldMatrix().EulerAngles();
		return radAngles * math::DC_180_OVER_PI;
	}
	
	math::Vector3f CTransform::LocalEulerAngles()
	{
		math::Vector3f radAngles = m_localMatrix.EulerAngles();
		return radAngles * math::DC_180_OVER_PI;
	}
	
	void CTransform::Changed()
	{
		if(!m_changed)
		{
			m_changed = true;
			
			for(auto* child : m_children)
			{
				child->Changed();
			}
		}
	}
	
	void CTransform::Reset()
	{
		m_changed = false;
		m_localMatrix.Identify();
		m_globalMatrix.Identify();
		m_scale = math::Vector3f::One();
		m_rotation.Identity();
		mp_root = 0;
		mp_parent = 0;
		m_children.clear();
	}
	
	math::Vector3f CTransform::TransformPosition(const math::Vector3f& point)
	{
		return m_localMatrix.TransformPosition(point);
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
	}
	
	CTransform* CTransform::FindChild(const std::string& name)
	{
		CTransform* found = 0;
		for(auto* child : m_children)
		{
			printf("%s\n", child->GameObject()->Name().c_str());
			if(child->GameObject()->Name() == name)
				return child;
			
			if(child->HasChildren())
			{
				found = child->FindChild(name);
				if(found)
					return found;
			}
		}
		return found;
	}
	
	void CTransform::Position(const math::Vector3f& position)
	{
		m_position = position;
		CalculateTransforms();
	}
	
	void CTransform::Rotation(const math::Vector3f& rotation)
	{
		math::Vector3f radRotation = rotation * math::DC_PI_OVER_180;
		m_rotation = math::Quaternionf::FromEulerRad(radRotation);
		CalculateTransforms();
	}
	
	void CTransform::Rotation(const math::Quaternionf& rotation)
	{
		m_rotation = rotation;
		CalculateTransforms();
	}
	
	void CTransform::Scale(const math::Vector3f& scale)
	{
		m_scale = scale;
		CalculateTransforms();
	}

	void CTransform::CalculateLocalTransform()
	{
		m_localMatrix.Set(m_position, m_rotation, m_scale);
	}
	
	void CTransform::CalculateWorldTransform()
	{
		if(HasParent())
		{
			m_globalMatrix = mp_parent->WorldMatrix() * m_localMatrix;
		}
		else
		{
			m_globalMatrix = m_localMatrix;
		}
	}
	
	void CTransform::CalculateTransforms()
	{
		CalculateLocalTransform();
		CalculateWorldTransform();
		
		for(auto* child: m_children)
		{
			child->CalculateTransforms();
		}
	}
	
	void PrintLocalMatrix(const CTransform* transform)
	{
		printf("ROOT\n");
		printf("GO %s\n", transform->GameObject()->Name().c_str());
		PrintMatrix(transform->LocalMatrix());
		
		printf("CHILDREN\n");
		for(auto* child : transform->Children())
		{
			printf("GO %s\n", child->GameObject()->Name().c_str());

			PrintMatrix(child->LocalMatrix());
			PrintLocalMatrix(child);
		}
	}
}
