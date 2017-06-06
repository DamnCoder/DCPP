//
//	assetloader
//	DCPP
//
//	Created by Jorge López González on 25/05/2017 14:39:16.
//

#include "assetloader.h"

#include <assert.h>

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

	// ===========================================================
	// Methods
	// ===========================================================
	void CAssetLoader::Load(const char* path, CAssetManager& assetManager)
	{
		FILE* fp = fopen(path, "r");
		
		if(!fp)
		{
			printf("File not found: %s!\n", path);
			exit(1);
		}
		
		long lSize;
		
		fseek( fp , 0L , SEEK_END);
		lSize = ftell( fp );
		rewind( fp );
		
		/* allocate memory for entire content */
		char* buffer = (char*) malloc(lSize * sizeof(char));
		if( !buffer )
		{
			fclose(fp);
			fputs("memory alloc fails", stderr);
			exit(1);
		}
		
		/* copy the file into the buffer */
		if(fread( buffer , lSize, 1 , fp) != 1)
		{
			fclose(fp);
			free(buffer);
			fputs("entire read fails", stderr);
			exit(1);
		}
		
		printf("%s\n", buffer);
		
		Document document;
		document.Parse(buffer, lSize);
		if(document.HasParseError())
		{
			printf("Error parsing!\n");
		}

		ReadTextures(document, assetManager);
		
		fclose(fp);
		free(buffer);
	}
	
	void CAssetLoader::ReadTextures(Document& document, CAssetManager& assetManager)
	{
		const char* TEXTURE_KEY = "texture";
		const char* FOLDER_KEY = "folder";
		const char* ASSETS_KEY = "assets";
		
		assert(document.IsObject());
		assert(document.HasMember(TEXTURE_KEY) && "[CAssetLoader::ReadTextures] No textures defined in asset_config");
		
		auto& textureObject = document[TEXTURE_KEY];
		
		const char* folder = textureObject[FOLDER_KEY].GetString();
		printf("Folder for textures %s\n", folder);
		
		auto& assetsObj = textureObject[ASSETS_KEY];
		for(auto& assetsEntry : assetsObj.GetObject())
		{
			const char* fileName = assetsEntry.name.GetString();
			const char* fileType = assetsEntry.value.GetString();
			
			printf("file: %s, type: %s\n", fileName, fileType);
		}
	}

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
