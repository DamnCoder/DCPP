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

//-----------------------------------------------------------------------
// COMMON FUNCTIONS
//-----------------------------------------------------------------------

/**
 * Plantilla para convertir datos en cadenas de caracteres
 *
 * @param data
 * @return string, una cadena de caracteres
 */
template <class C>
std::string Data2string(const C& data)
{
	std:: stringstream flow;
	flow << data;
	return(flow.str());
}

const bool IsInString(const std::string& strString, const std::string& strSubString)
{
	
	if(strString.length() <= 0 || strSubString.length() <= 0)
		return false;
	
	// Si no se encuentra en la cadena, devolvera -1
	const int index = (int)strString.find(strSubString);
	
	return (0 <= index && index < (int)strString.length());
}

#endif /*UTILITYS_H_*/