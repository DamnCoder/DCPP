#ifndef UTILITYS_H_
#define UTILITYS_H_

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <sys/types.h>

#include <iostream>

#include <string>
#include <sstream>

#include <vector>
#include <list>
#include <map>

#include <iterator>
#include <algorithm>

/** Insercion de espacios de nombres muy comunes */

using namespace std;

//-----------------------------------------------------------------------
// COMMON FUNCTORS
//-----------------------------------------------------------------------

template<typename T>
struct ComparisonFunctor
{
public:
    ComparisonFunctor(const T* searchedElement):
        mp_searchedElement(searchedElement)
    {}
    
    const bool operator()(const T* element) const
    {
        return mp_searchedElement == element;
    }
    
private:
    const T* mp_searchedElement;
};

struct cmp_c_str
{
	const bool operator()(const char* a, const char* b) const
	{
		return std::strcmp(a, b) < 0;
	}
};

//-----------------------------------------------------------------------
// STRING FUNCTIONS
//-----------------------------------------------------------------------

inline
std::string GetFileExtension (const std::string& filename)
{
	std::string::size_type pos = filename.find_last_of('.');
	
	// no file extension at all
	if( pos == std::string::npos)
		return "";
	
	std::string ret = filename.substr(pos+1);
	std::transform(ret.begin(),ret.end(),ret.begin(),::tolower); // thanks to Andy Maloney for the hint
	return ret;
}

/**
 * Returns a file name without extension. It uses dynamic memory so you
 * have to call free() when done with the char array
 */
inline
char* GetFileExtension(const char* filename)
{
	char* pch = strrchr(filename, '.');
	size_t lastIndex = pch - filename;
	char* filenameNoExt = strndup(filename, lastIndex);
	return filenameNoExt;
}

inline
void EraseAll(std::string& str, const char toRemove)
{
	str.erase(std::remove(str.begin(), str.end(), toRemove), str.end());
}

/**
 * Template to transform data in a string of characters
 *
 * @param data
 * @return string, the actual string of characters
 */
template <class C>
inline
std::string Data2string(const C& data)
{
	std:: stringstream flow;
	flow << data;
	return(flow.str());
}

inline const bool IsInString(const std::string& strString, const std::string& strSubString)
{
	
	if(strString.length() <= 0 || strSubString.length() <= 0)
		return false;
	
	// If it's not in the string it return -1
	const int index = (int)strString.find(strSubString);
	
	return (0 <= index && index < (int)strString.length());
}

#endif /*UTILITYS_H_*/
