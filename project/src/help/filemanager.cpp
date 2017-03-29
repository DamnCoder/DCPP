/*
 * filemanager.cpp
 *
 *  Created on: 31 ene. 2017
 *      Author: jorge
 */

#include "filemanager.h"

namespace dc
{

CFileManager::CFileManager(const char* rootPath) : mp_rootPath(rootPath)
{
}

CFileManager::~CFileManager()
{
}

const std::string CFileManager::RootPath()
{
	return std::string(mp_rootPath);
}

} /* namespace dc */
