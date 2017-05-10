//
//	texture
//	DCPP
//
//	Created by Jorge López González on 09/05/2017 12:22:37.
//

#include "texture.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	void CTexture::Activate(const CTexture& texture)
	{
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.Id());
	}
	
	void CTexture::Deactivate()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	const unsigned int CTexture::Create()
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		return textureID;
	}
	
	void CTexture::Destroy(const CTexture& texture)
	{
		const GLuint identifier = (GLuint)texture.Id();
		glDeleteTextures(1, &identifier);
	}
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================
	
	// ===========================================================
	// Static fields / methods
	// ===========================================================

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Constructors
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	// ===========================================================
	// Fields
	// ===========================================================

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}
