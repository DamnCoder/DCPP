/*
 * CBoundingBox.h
 *
 *  Created on: 10/08/2010
 *      Author: jorge
 */

#ifndef CBOUNDINGBOX_H_
#define CBOUNDINGBOX_H_

#include <math/vector3.h>

namespace dc
{

	class CBoundingBox
	{

	public:
		CBoundingBox(): m_lower(), m_upper(){}

		CBoundingBox(const math::Vector3f& lower, const math::Vector3f& upper):
			m_lower(lower),
			m_upper(upper)
		{}

		CBoundingBox(float x1, float y1, float z1, float x2, float y2, float z2):
			m_lower(math::Vector3f(x1, y1, z1)),
			m_upper(math::Vector3f(x2, y2, z2))
		{}

		CBoundingBox(float* lower, float* upper) :
			m_lower(math::Vector3f(lower[0], lower[1], lower[2])),
			m_upper(math::Vector3f(upper[0], upper[1], upper[2]))
		{}

		~CBoundingBox() {}

	public:
		const math::Vector3f Lower() const { return m_lower;}
		const math::Vector3f Upper() const { return m_upper;}

		/**
		 * Consideramos que lower y upper son coordenadas globales.
		 * Decide si un punto se encuentra dentro de la bounding box
		 * @param p
		 * @return true si el punto esta dentro de la bounding box
		 */
		const bool IsInside2dBox(const math::Vector3f& p) const;
		const bool IsInside(const math::Vector3f& p) const;

	protected:
		math::Vector3f m_lower;
		math::Vector3f m_upper;
	};

	class CBoundingSphere
	{
	public:
		CBoundingSphere() : m_radius(0) {}
		CBoundingSphere(float x, float y, float z, float radius) :
			m_center(math::Vector3f(x, y, z)),
			m_radius(radius) {}
		CBoundingSphere(float* center, float radius) :
			m_center(math::Vector3f(center[0] ,center[1], center[2])),
			m_radius(radius) {}

		~CBoundingSphere() {}
		
	public:
		const math::Vector3f	Center() const { return m_center; }
		const float				Radius() const { return m_radius; }

		void Center(const math::Vector3f& newCenter) { m_center = newCenter; }
		void Radius(float radius) { m_radius = radius; }

	private:
		math::Vector3f	m_center;
		float			m_radius;

	};

}

#endif /* CBOUNDINGBOX_H_ */
