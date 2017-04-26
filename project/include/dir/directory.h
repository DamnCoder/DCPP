/*
 * directory.h
 *
 *  Created on: 26 feb. 2017
 *      Author: jorge
 */

#ifndef DIR_DIRECTORY_H_
#define DIR_DIRECTORY_H_


#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
 #endif


namespace dc
{
	const std::string GetCurrentDir()
	{
		char currentPath[FILENAME_MAX];
		if (!getcwd(currentPath, sizeof(currentPath)))
		{
			return "";
		}

		currentPath[sizeof(currentPath) - 1] = '\0'; /* not really required */

		printf ("The current working directory is %s\n", currentPath);
		return std::string(currentPath);
	}
}


#endif /* SUBPROJECTS__DCPP_PROJECT_INCLUDE_DIR_DIRECTORY_H_ */
