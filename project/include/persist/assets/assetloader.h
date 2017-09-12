//
//	assetloader
//	DCPP
//
//	Created by Jorge López González on 25/05/2017 14:39:16.
//

#ifndef CASSETLOADER_H
#define CASSETLOADER_H

#include "assets/assetmanager.h"

#include <string>

#include <pathie.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

using namespace rapidjson;

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	/**
	 * \class CAssetLoader
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */
class CAssetLoader
{
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
public:
	CAssetLoader()
	{}

	~CAssetLoader()
	{}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================
public:
	void Load(const char* path, CAssetManager& assetManager);
	
private:
	void ReadTextures(rapidjson::Document& document, CAssetManager& assetManager);
	
	void ReadShaders(rapidjson::Document& document, CAssetManager& assetManager);
	
	void ReadMeshes(rapidjson::Document& document, CAssetManager& assetManager);
	
	void ReadMD3(rapidjson::Document& document, CAssetManager& assetManager);
	
	void ReadMD5(rapidjson::Document& document, CAssetManager& assetManager);
	
	// ===========================================================
	// Fields
	// ===========================================================
	
private:
	Pathie::Path m_rootPath;
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* CASSETLOADER_H */
