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

inline std::string GetExtension (const std::string& file)
{
	std::string::size_type pos = file.find_last_of('.');
	
	// no file extension at all
	if( pos == std::string::npos)
		return "";
	
	std::string ret = file.substr(pos+1);
	std::transform(ret.begin(),ret.end(),ret.begin(),::tolower); // thanks to Andy Maloney for the hint
	return ret;
}

/**
 * Plantilla para convertir datos en cadenas de caracteres
 *
 * @param data
 * @return string, una cadena de caracteres
 */
template <class C>
inline std::string Data2string(const C& data)
{
	std:: stringstream flow;
	flow << data;
	return(flow.str());
}

inline const bool IsInString(const std::string& strString, const std::string& strSubString)
{
	
	if(strString.length() <= 0 || strSubString.length() <= 0)
		return false;
	
	// Si no se encuentra en la cadena, devolvera -1
	const int index = (int)strString.find(strSubString);
	
	return (0 <= index && index < (int)strString.length());
}

#endif /*UTILITYS_H_*/
