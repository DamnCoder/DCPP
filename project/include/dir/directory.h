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

#ifndef CDIRECTORY_H
#define CDIRECTORY_H

#include <vector>
#include <string>

#include <dirent.h>
#include <pathie.hpp>

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	/**
	 * \class CDirectory
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */
class CDirectory
{
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
	
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================
	
	// ===========================================================
	// Static fields / methods
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Constructors
	// ===========================================================
public:
public:
	CDirectory(const Pathie::Path& path):
		m_path(path),
		mp_dd(opendir(path.c_str()))
	{}


	~CDirectory()
	{
		closedir(mp_dd);
	}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================
public:
	const std::vector<std::string> FindFiles(const std::string& substring);

	// ===========================================================
	// Fields
	// ===========================================================
private:
	Pathie::Path	m_path;
	DIR*			mp_dd;
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* CDIRECTORY_H */
