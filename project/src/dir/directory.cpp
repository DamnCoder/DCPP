/*
 The MIT License (MIT)
 
 Copyright (c) 2016 Jorge López González
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//
//	directory
//	DCPP
//
//	Created by Jorge López González on 28/06/2017 12:51:38.
//

#include "directory.h"

namespace dc
{
	const std::vector<std::string> CDirectory::FindFiles(const std::string& substring)
	{
		std::vector<std::string> fileNameList;
		
		dirent* dit;
		
		while ((dit = readdir (mp_dd)) != NULL)
		{
			const std::string filename (dit->d_name);
			
			if (filename.compare (0, substring.length (), substring) == 0)
			{
				fileNameList.push_back(filename);
				printf("[CDirectory::FindFiles] filename: %s\n", filename.c_str());
			}
		}
		return fileNameList;
	}
}
