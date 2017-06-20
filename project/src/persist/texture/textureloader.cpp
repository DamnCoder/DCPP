//
//	textureloader
//	DCPP
//
//	Created by Jorge López González on 09/05/2017 12:08:52.
//

#include "textureloader.h"

//#include <SDL2_image/SDL_image.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <assert.h>
#include <stdio.h>

#include "renderer/glwraps.h"

namespace dc
{
	CTexture* CTextureLoader::Load(const char* path)
	{
		// This is needed to provide OpenGL with the texture flipped, which is the way OpenGL expects it
		stbi_set_flip_vertically_on_load(true);
		
		int width, height, bpp;
		int channels = 3;
		unsigned char* textureData = stbi_load(path, &width, &height, &bpp, channels);
		
		if(!textureData)
		{
			printf("[CTextureLoader::Load] No texture to load in %s\n", path);
			return 0;
		}
		
		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);
		
		//glActiveTexture(GL_TEXTURE0);
		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		
		// rgb is now three bytes per pixel, width*height size. Or NULL if load failed.
		// Do something with it...
		stbi_image_free( textureData );
		
		printf("[CTextureLoader::Load] Texture %s with size [%d, %d] is loaded\n", path, width, height);
		
		// Texture configuration
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		return new CTexture(textureID, width, height, EPixelFormat::RGB, EWrap::REPEAT, EFiltering::LINEAR, EFiltering::LINEAR_MIPMAP_LINEAR);
	}
}
