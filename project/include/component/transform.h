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
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	class CTransform;
	
	using TTransformList = std::vector<CTransform*>;
	using TTransformIterator = TTransformList::iterator;
	
	/**
	 * \class
	 * \brief
	 * \author Jorge Lopez Gonzalez
	 *
	 * Description.
	 */
	class CTransform : public CComponent
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		RTTI_DECLARATIONS(CTransform, CComponent)
		
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
		void					LocalMatrix(const math::Matrix4x4f& matrix);
		const math::Matrix4x4f&	LocalMatrix() const;
		const math::Matrix4x4f&	WorldMatrix() const;
		
		const bool				HasChild(CTransform* transform) const;
		const bool				HasChildren() const	{ return !m_children.empty(); }
		const unsigned int		ChildCount() const	{ return m_children.size(); }
		const TTransformList	Children() const	{ return m_children; }
		
		TTransformIterator		Begin()	{ return m_children.begin(); }
		TTransformIterator		End()	{ return m_children.end(); }
		
		CTransform*				Root() const	{ return mp_root; }
		
		const bool				HasParent() const { return mp_parent != 0; }
		CTransform*				Parent() const	{ return mp_parent; }
		void					Parent(CTransform* parent);
		
		math::Vector3f			LocalPosition() { return m_localMatrix.Position(); }
		math::Vector3f			Position()		{ return m_globalMatrix.Position(); }
		
		math::Vector3f			EulerAngles();
		math::Vector3f			LocalEulerAngles();
		
		math::Quaternionf		Rotation() const { return m_localMatrix.Rotation(); }
		
		
		math::Vector3f			Scale() { return WorldMatrix().Scale(); }
		
	private:
		void					Root(CTransform* root);
		const bool				Changed() const { return m_changed; }
		void					Changed();
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CTransform()
		{
			Reset();
		}
		
		~CTransform() {}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Reset();
		
		void Add(CTransform* child);
		void Remove(CTransform* child);
		
		CTransform* FindChild(const std::string& name);
		
		void Position(const math::Vector3f& position);
		void Rotation(const math::Vector3f& rotation);
		void Rotation(const math::Quaternionf& rotation);
		void Scale(const math::Vector3f& scale);
		
		// Transforms position from local space to world space.
		math::Vector3f TransformPosition(const math::Vector3f& point);
		
	private:
		void CalculateLocalTransform();
		void CalculateWorldTransform();
		
		void CalculateTransforms();
		
		// ===========================================================
		// Fields
		// ===========================================================
    private:
		bool				m_changed;
		
		CTransform*			mp_root;    // Topmost transform in the hierarchy
		CTransform*			mp_parent;  // Transform parent

		math::Matrix4x4f	m_localMatrix;   // Local
		math::Matrix4x4f	m_globalMatrix;
		
		math::Vector3f		m_position;		// Local position
		math::Vector3f		m_scale;		// Local scale
		math::Quaternionf	m_rotation;		// Local rotaion
		TTransformList		m_children;
    };
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
	
	void PrintLocalMatrix(const CTransform* transform);
}

#endif
