/*
 * CBoundingBox.cpp
 *
 *  Created on: 10/08/2010
 *      Author: jorge
 */

#include "BoundingBox.h"

namespace dc
{

	const bool CBoundingBox::IsInside2dBox(const math::Vector3f& p) const
	{
		return (m_lower.x <= p.x) && (p.x <= m_upper.x) && (m_lower.y <= p.y) && (p.y <= m_upper.y);
	}

	const bool CBoundingBox::IsInside(const math::Vector3f& p) const
	{
		return (m_lower.x <= p.x) && (p.x <= m_upper.x)
				&&
				(m_lower.y <= p.y) && (p.y <= m_upper.y)
				&&
				(m_lower.z <= p.z) && (p.z <= m_upper.z);
	}

}
