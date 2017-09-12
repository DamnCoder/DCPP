/*
 * SkinLoader.cpp
 *
 *  Created on: 01/06/2011
 *      Author: jorge
 */

#include "md3skinloader.h"

#include <dirent.h>

#include "persist/texture/textureloader.h"
#include "help/utils.h"

namespace dc
{
	/**
	 * Run through all the .skin files to store the textures
	 * in the asset manager
	 *
	 * @param path
	 * @param pattern
	 */
	const TSkinMap CSkinLoader::Load(const Pathie::Path& path, const std::string& pattern)
	{
		TSkinMap skinMap;
		
		Pathie::Path skinPath (path);
		
		// Open directory
		DIR* dd = opendir (path.c_str());
		assert(dd && "[CSkinLoader::Load] The path doesn't exist");
		
		const std::string fileext (".skin");
		const std::string finalPattern = pattern + (std::string)"_";
		
		//printf("[CSkinLoader::Load] Path: %s Pattern: %s\n", skinPath.c_str(), finalPattern.c_str());
		
		// Read the directory to find the .skin file
		dirent* dit;
		
		while ((dit = readdir (dd)) != NULL)
		{
			const std::string filename (dit->d_name);
			
			if (filename.length () - fileext.length () == filename.find (fileext))
			{
				if (filename.compare (0, finalPattern.length (), finalPattern) == 0)
				{
					skinPath.append(filename);
					//printf("[CSkinLoader::Load] Skin path: %s\n", skinPath.c_str());
					ReadSkin(skinPath, skinMap);
				}
			}
		}
		
		closedir(dd);

		//printf("[CSkinLoader::Load] Skin map readed\n");
		return skinMap;
	}
	
	/**
	 * Read the .skin file and stores the texture in the asset manager if
	 * it is not already there
	 *
	 * @param skinFilePath
	 */
	void CSkinLoader::ReadSkin(const Pathie::Path& skinFilePath, TSkinMap& skinMap)
	{
		FILE* fp = fopen(skinFilePath.c_str(), "r");
		
		if(!fp)
		{
			printf("[CSkinLoader::ReadSkin] The file doesn't exist");
			return;
		}
		
		TTextureManager& textureManager = m_assetManager.TextureManager();
		
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		
		CTextureLoader textureLoader;
		while ((read = getline(&line, &len, fp)) != -1)
		{
			//printf("[CSkinLoader::ReadSkin] Skin line %s\n", line);
			
			// pch will containt the path like this: ",/path/to/file"
			char* pch = strchr(line, ',');
			
			size_t initIndex = pch - line;
			const int meshLength = initIndex;
			char meshCharArray[meshLength];
			strncpy(meshCharArray, line, meshLength);
			const std::string meshName (meshCharArray, meshLength);
			//printf("[CSkinLoader::ReadSkin] Mesh for the texture: %s\n", meshName.c_str());
			
			const int pathLength = len - initIndex + 1;
			char pathCharArray[pathLength];
			
			// We remove the ','
			strncpy(pathCharArray, pch+1, pathLength);
			
			Pathie::Path texturePath (pathCharArray);
			texturePath.prepend(".");
			
			std::string path = texturePath.str();
			EraseAll(path, '\n');
			
			std::string filename = texturePath.basename().str();
			EraseAll(filename, '\n');
			
			//printf("[CSkinLoader::ReadSkin] Path to texture: %s\n", texturePath.c_str());
			//printf("[CSkinLoader::ReadSkin] File name: %s\n", filename.c_str());
			
			if(!textureManager.Exists(filename))
			{
				CTexture* texture = textureLoader.Load(path.c_str());
				textureManager.Add(filename.c_str(), texture);
			}
			printf("[CSkinLoader::ReadSkin] Texture: %s for mesh: %s\n", filename.c_str(), meshName.c_str());
			skinMap[meshName] = filename;
		}
		
		fclose(fp);
	}
}
