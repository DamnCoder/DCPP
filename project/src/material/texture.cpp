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
	// Static methods
	// ===========================================================
	
	void CTexture::Bind(const CTexture* texture)
	{
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->Id());
	}
	
	void CTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	const unsigned int CTexture::Create()
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		return textureID;
	}
	
	void CTexture::Destroy(const CTexture* texture)
	{
		const GLuint identifier = (GLuint)texture->Id();
		glDeleteTextures(1, &identifier);
	}
	
	// ===========================================================
	// Methods
	// ===========================================================
	const bool CTexture::Equals(const CTexture* texture) const
	{
		return m_id == texture->Id();
	}
	
	void CTexture::Activate()
	{
		Bind(this);
	}
	
	void CTexture::Deactivate()
	{
		Unbind();
	}

}
