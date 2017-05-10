//
//	texture
//	DCPP
//
//	Created by Jorge López González on 09/05/2017 12:22:37.
//

#ifndef CTEXTURE_H
#define CTEXTURE_H

#include "renderer/glwraps.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	/**
	 * \class CTexture
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */
class CTexture
{
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================
public:
	static void Activate(const CTexture& texture);
	static void Deactivate();
	
	static const unsigned int Create();
	static void Destroy(const CTexture& texture);
	
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
	const int			Id()			const { return m_id; }
	const unsigned int	Width()			const { return m_width; }
	const unsigned int	Height()		const { return m_height; }
	
	const EPixelFormat	PixelFormat()	const { return m_pixelFormat; }
	const EWrap			WrapType()		const { return m_wrapType; }
	const EFiltering	MinFiltering()	const { return m_minFilterType; }
	const EFiltering	MagFiltering()	const { return m_magFilterType; }
	// ===========================================================
	// Constructors
	// ===========================================================
public:
	CTexture():
		m_id (-1),
		m_width(0),
		m_height(0),
		m_pixelFormat(EPixelFormat::RGB),
		m_wrapType(EWrap::REPEAT),
		m_minFilterType(EFiltering::LINEAR),
		m_magFilterType(EFiltering::LINEAR)
	{}
	
	CTexture(int identifier, unsigned int width, unsigned int height, EPixelFormat pixelFormat, EWrap wrapping, EFiltering minFilter, EFiltering magFilter):
		m_id (identifier),
		m_width(width),
		m_height(height),
		m_pixelFormat(pixelFormat),
		m_wrapType(wrapping),
		m_minFilterType(minFilter),
		m_magFilterType(magFilter)
	{}

	~CTexture()
	{}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	// ===========================================================
	// Fields
	// ===========================================================
private:
	int				m_id;
	unsigned int	m_width;
	unsigned int	m_height;
	EPixelFormat	m_pixelFormat;
	EWrap			m_wrapType;
	EFiltering		m_minFilterType;
	EFiltering		m_magFilterType;
	
	
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* CTEXTURE_H */
