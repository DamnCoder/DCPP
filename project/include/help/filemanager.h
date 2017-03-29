/*
 * filemanager.h
 *
 *  Created on: 31 ene. 2017
 *      Author: jorge
 */

#ifndef SUBPROJECTS__DCPP_PROJECT_FILEMANAGER_H_
#define SUBPROJECTS__DCPP_PROJECT_FILEMANAGER_H_

#include <string>

namespace dc
{

class CFileManager
{
public:
	CFileManager(const char* rootPath);
	~CFileManager();

public:
	const std::string RootPath();

private:

	const char* mp_rootPath;
};

} /* namespace dc */

#endif /* SUBPROJECTS__DCPP_PROJECT_FILEMANAGER_H_ */
