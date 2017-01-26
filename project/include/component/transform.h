//
//  transform.h
//  BitThemAll
//
//  Created by Jorge López González on 27/12/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef BitThemAll_transform_h
#define BitThemAll_transform_h

#include "math/matrix.h"

#include "component.h"

#include <vector>

namespace dc
{
    /*
     
     */
    class Transform : public Component
    {
		RTTI_DECLARATIONS(Transform, Component)
		
	public:
		typedef std::vector<Transform*>     TTransformList;
		typedef TTransformList::iterator    TTransformIterator;
		
    public:
        Transform()
        {
            Reset();
        }
        
        ~Transform() {}
        
    public:
        // Getters
        const math::Matrix4x4f  LocalMatrix() const { return m_matrix; }
        
        const TTransformList    Childs() const { return ml_childs; }
        TTransformIterator      Begin() { return ml_childs.begin(); }
        TTransformIterator      End() { return ml_childs.end(); }
        
        Transform*              Root() const { return mp_root; }
        Transform*              Parent() const { return mp_parent; }
        
        void SetParent(Transform* parent)
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
        
        math::Vector3f LocalPos() const { return m_matrix.translation; }
        math::Vector3f WorldPos() const { return WorldMatrix().translation; }
        
        math::Vector3f LocalEulerAngles() const { return m_matrix.EulerAngles(); }
        math::Vector3f WorldEulerAngles() const { return WorldMatrix().EulerAngles(); }
        
        math::Matrix4x4f WorldMatrix() const
        {
            if (mp_parent)
            {
                return mp_parent->WorldMatrix() * m_matrix;
            }
            return m_matrix;
        }
        
        //operator math::Matrix4x4f () { return m_localMatrix; }
        
    public:
        void Reset();
        
        void AddChild(Transform* child);
        
        void Translate(const math::Vector3f& position);
        void Rotate(const math::Vector3f& rotation);
        void Scale(const math::Vector3f& scale);
        
        // Transforms position from local space to world space.
        math::Vector3f TransformPosition(const math::Vector3f& point);
        
    private:
        // Private atributes
        
        Transform*          mp_root;    // Topmost transform in the hierarchy
        Transform*          mp_parent;  // Transform parent
        
        math::Matrix4x4f    m_matrix;   // Local matrix
        TTransformList      ml_childs;
    };
	
    inline
    void Transform::Reset()
    {
        m_matrix.Identity();
        mp_root = 0;
        mp_parent = 0;
        ml_childs.clear();
    }
    
    inline
    math::Vector3f Transform::TransformPosition(const math::Vector3f& point)
    {
        return m_matrix.TransformPosition(point);
    }
    
    inline
    void Transform::AddChild(Transform* child)
    {
        assert(child != 0);
        ml_childs.push_back(child);
    }
    
    inline
    void Transform::Translate(const math::Vector3f& position)
    {
        m_matrix.Translate(position);
    }
    
    inline
    void Transform::Rotate(const math::Vector3f& rotation)
    {
        m_matrix.Rotate(rotation);
    }
    
    inline
    void Transform::Scale(const math::Vector3f& scale)
    {
        m_matrix.Scale(scale);
    }
}

#endif
