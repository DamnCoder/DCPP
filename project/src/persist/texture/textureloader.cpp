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
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================

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
	CTexture* CTextureLoader::Load(const char* path)
	{
		// This is needed to provide OpenGL with the texture flipped, which is the way OpenGL expects it
		stbi_set_flip_vertically_on_load(true);
		
		int width, height, bpp;
		int channels = 3;
		unsigned char* textureData = stbi_load(path, &width, &height, &bpp, channels);
		
		
		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);
		
		glActiveTexture(GL_TEXTURE0);
		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		
		// rgb is now three bytes per pixel, width*height size. Or NULL if load failed.
		// Do something with it...
		stbi_image_free( textureData );
		
		printf("Texture %s with size [%d, %d] is loaded\n", path, width, height);
		
		// Texture configuration
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		return new CTexture(textureID, width, height, EPixelFormat::RGB, EWrap::REPEAT, EFiltering::LINEAR, EFiltering::LINEAR_MIPMAP_LINEAR);
	}
	/*
	CTexture CTextureLoader::Load(const char* path)
	{
		assert (path != 0 && "[CTextureLoader::Load] No path!");
		
		SDL_Surface* loadedImage = IMG_Load(path);
		
		assert (loadedImage != 0 && "[CTextureLoader::Load] The texture doesn't exist");
		
		int width = loadedImage->w;
		int height = loadedImage->h;
		
		EPixelFormat pixelFormat;
		switch (loadedImage->format->BytesPerPixel)
		{
			case 3:	// No tiene canal alpha
				if (loadedImage->format->Rmask == 0x000000ff)
					pixelFormat = EPixelFormat::RGB;
				else
					pixelFormat = EPixelFormat::BGR;
				break;
			case 4: // Tiene canal alpha
				if (loadedImage->format->Rmask == 0x000000ff)
					pixelFormat = EPixelFormat::RGBA;
				else
					pixelFormat = EPixelFormat::BGRA;
				break;
			default:
			pixelFormat = EPixelFormat::RGBA;
		}
		
		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);
		
		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, loadedImage->pixels);
		
		printf("Texture %s with size [%d, %d] is loaded\n", path, width, height);
		
		// Texture configuration
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		SDL_FreeSurface(loadedImage);
		
		return CTexture(textureID, width, height, pixelFormat, EWrap::REPEAT, EFiltering::LINEAR, EFiltering::LINEAR_MIPMAP_LINEAR);
	}
	*/
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
