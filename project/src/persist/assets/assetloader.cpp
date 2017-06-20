//
//	assetloader
//	DCPP
//
//	Created by Jorge López González on 25/05/2017 14:39:16.
//

#include "assetloader.h"

#include <assert.h>

#include <persist/texture/textureloader.h>
#include <persist/shader/shaderloader.h>
#include <persist/obj/objloader.h>
#include <persist/md3/md3loader.h>

#include <pathie.hpp>

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

		m_rootPath = "./" + std::string(document["folder"].GetString());
		
		
		ReadTextures(document, assetManager);
		ReadShaders(document, assetManager);
		ReadMeshes(document, assetManager);
		ReadMD3(document, assetManager);
		
		fclose(fp);
		free(buffer);
	}
	
	void CAssetLoader::ReadTextures(Document& document, CAssetManager& assetManager)
	{
		const char* ASSET_GROUP_KEY = "texture";
		const char* FOLDER_KEY = "folder";
		const char* ASSETS_KEY = "assets";
		
		assert(document.IsObject());
		assert(document.HasMember(ASSET_GROUP_KEY) && "[CAssetLoader::ReadTextures] No textures defined in asset_config");
		
		CTextureLoader loader;

		auto& assetGroupObj = document[ASSET_GROUP_KEY];
		
		const std::string folder = assetGroupObj[FOLDER_KEY].GetString();
		
		Pathie::Path assetPath(m_rootPath);
		assetPath.append(folder);
		
		printf("Current dir %s\n", assetPath.c_str());
		
		auto& assetsObj = assetGroupObj[ASSETS_KEY];
		for(auto& assetsEntry : assetsObj.GetObject())
		{
			const char* fileName = assetsEntry.name.GetString();
			const char* fileType = assetsEntry.value.GetString();
			
			Pathie::Path filePath(assetPath);
			filePath.append(fileName);
			
			printf("file: %s, type: %s\n", filePath.c_str(), fileType);
			
			CTexture* texture = loader.Load(filePath.c_str());
			
			assetManager.TextureManager().Add(fileName, texture);
		}
		
		printf("All textures loaded\n");
	}
	
	void CAssetLoader::ReadShaders(Document& document, CAssetManager& assetManager)
	{
		const char* ASSET_GROUP_KEY = "shader";
		const char* FOLDER_KEY = "folder";
		const char* ASSETS_KEY = "assets";
		
		assert(document.IsObject());
		assert(document.HasMember(ASSET_GROUP_KEY) && "[CAssetLoader::ReadShaders] No textures defined in asset_config");
		
		CShaderLoader loader;
		
		auto& textureObject = document[ASSET_GROUP_KEY];
		
		const std::string folder = textureObject[FOLDER_KEY].GetString();
		printf("Folder for textures %s\n", folder.c_str());
		
		const std::string textureFolder = m_rootPath+"/"+folder+"/";
		
		auto& assetsObj = textureObject[ASSETS_KEY];
		for(auto& assetsEntry : assetsObj.GetObject())
		{
			const char* fileName = assetsEntry.name.GetString();
			const char* fileType = assetsEntry.value.GetString();
			
			int shaderType = 0;
			if(strcmp(fileType, "VERTEX") == 0)
			{
				shaderType = EShaderType::VERTEX_SHADER;
			}
			else if(strcmp(fileType, "FRAGMENT") == 0)
			{
				shaderType = EShaderType::FRAGMENT_SHADER;
			}
			
			const std::string filePath = textureFolder + fileName;
			CShader* shader = loader.Load(filePath.c_str(), shaderType);
			
			printf("file: %s, type: %s\n", filePath.c_str(), fileType);
			
			assetManager.ShaderManager().Add(fileName, shader);
		}
		
		printf("All shaders loaded\n");
	}
	
	void CAssetLoader::ReadMeshes(rapidjson::Document& document, CAssetManager& assetManager)
	{
		const char* ASSET_GROUP_KEY = "mesh";
		const char* FOLDER_KEY = "folder";
		const char* ASSETS_KEY = "assets";
		
		assert(document.IsObject());
		assert(document.HasMember(ASSET_GROUP_KEY) && "[CAssetLoader::ReadMeshes] No textures defined in asset_config");

		auto& assetGroupObj = document[ASSET_GROUP_KEY];
		
		const std::string folder = assetGroupObj[FOLDER_KEY].GetString();
		
		Pathie::Path assetPath(m_rootPath);
		assetPath.append(folder);
		
		printf("Current dir %s\n", assetPath.c_str());
		
		auto& assetsObj = assetGroupObj[ASSETS_KEY];
		for(auto& assetsEntry : assetsObj.GetObject())
		{
			const char* fileName = assetsEntry.name.GetString();
			const char* fileType = assetsEntry.value.GetString();
			
			Pathie::Path filePath(assetPath);
			filePath.append(fileName);
			
			CMesh* mesh = 0;
			if(strcmp(fileType, "OBJ") == 0)
			{
				CObjLoader loader;
				CArray<CMesh*> meshArray = loader.Load(filePath.c_str());
				mesh = meshArray[0];
			}
			
			printf("file: %s, type: %s\n", filePath.c_str(), fileType);
			
			assetManager.MeshManager().Add(fileName, mesh);
		}
		
		printf("All meshes loaded\n");
	}
	
	void CAssetLoader::ReadMD3(rapidjson::Document& document, CAssetManager& assetManager)
	{
		const char* ASSET_GROUP_KEY = "md3";
		
		assert(document.IsObject());
		assert(document.HasMember(ASSET_GROUP_KEY) && "[CAssetLoader::ReadMD3] No md3 defined in asset_config");
		
		auto& assetGroupObj = document[ASSET_GROUP_KEY];
		
		for(auto& modelEntry : assetGroupObj.GetObject())
		{
			auto modelObj = modelEntry.value.GetObject();
			for(auto& assetEntry : modelObj)
			{
				Pathie::Path assetPath (assetEntry.value.GetString());
				if(assetPath.size())
				{
					CMD3Loader loader(assetManager);
					CGameObject* md3GO = loader.Load(assetPath);
					assetManager.GameObjectManager().Add(md3GO->Name(), md3GO);
				}
			}
		}
	}
}
