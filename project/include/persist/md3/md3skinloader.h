/*
 * SkinLoader.h
 *
 *  Created on: 01/06/2011
 *      Author: jorge
 */

#ifndef SKINLOADER_H_
#define SKINLOADER_H_

#include <string>
#include <map>
#include <pathie.hpp>

#include "md3structs.h"
#include "assets/assetmanager.h"

namespace dc
{

	using TSkinMap = std::map<std::string, std::string>;
	
	class CSkinLoader
	{
	public:
		CSkinLoader(CAssetManager& assetManager): m_assetManager(assetManager) {}
		~CSkinLoader() {}
		
	public:
		const TSkinMap Load(const Pathie::Path& skinPath, const std::string& pattern);
		
	private:
		void ReadSkin(const Pathie::Path& skinFilePath, TSkinMap& skinMap);
		
	private:
		CAssetManager m_assetManager;
	};

}

#endif /* SKINLOADER_H_ */
