//
//  DeleteHelp.h
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef DeleteHelp_h
#define DeleteHelp_h

#include <vector>
#include <list>
#include <map>
#include <algorithm>

namespace dc
{
	//-----------------------------------------------------------------------
	// COMMON FUNCTIONS
	//-----------------------------------------------------------------------

	/**
	* Template for safely deleting pointers
	* @param data
	*/
	template <typename T>
	void SafeDelete(T*& data)
	{
		if(data)
		{
			delete data;
			data = 0;
		}
	}
    
    /**
     * Template for deleting pointers from vectors
     * Calls clear at the end.
     */
	template<typename T>
	void SafeDelete(std::vector<T*>& v)
	{
		typename std::vector<T*>::iterator it, end;
		it = v.begin();
		end = v.end();

		for (; it!=end; ++it)
		{
			delete (*it);
			(*it) = 0;
		}

		v.clear();
	}

	/**
	 * Template for deleting pointers from lists
     * Calls clear at the end.
	 */
	template<typename T>
	void SafeDelete(std::list<T *>& l)
	{
		typename std::list<T *>::iterator it, end;
	    it = l.begin();
		end = l.end();

		for (; it!=end; ++it)
	    {
			delete (*it);
			(*it) = 0;
		}

		l.clear();
	}
    
    /**
	 * Template for deleting pointers from maps
	 * Calls clear at the end.
	 */
	template <typename K, typename T>
	void SafeDelete(std::map<K, T*>& m)
	{
		typename std::map<K, T* >::iterator it, end;
		it=m.begin();
		end = m.end();

		for(; it!=end; ++it)
		{
			T* element = it->second;
			m.erase(it);

			delete element;
			element = 0;
		}

		m.clear();
	}
    
	//-----------------------------------------------------------------------
	// FUNCTORS
	//-----------------------------------------------------------------------
    
    /**
     * Functor overwriting the operator () so we can use it to delete pointers
     * in STL structures with for_each
     */
	template<typename PointerType>
    struct SafeDeletor
    {
        void operator()(PointerType*& pointer) const
        {
            safeDelete(pointer);
        }
    };

    //-----------------------------------------------------------------------
    // FUNCTOR FUNCTIONS
    //-----------------------------------------------------------------------

    template <typename T>
    void DeleteWithFunctors(std::vector<T *>& vctr)
    {
    	std::for_each(vctr.begin(), vctr.end(), SafeDeletor<T>());
        vctr.clear();
    }

    template <typename T>
    void DeleteWithFunctors(std::list<T *>& lst)
    {
    	std::for_each(lst.begin(), lst.end(), SafeDeletor<T>());
        lst.clear();
    }

}

#endif /* DeleteHelp_h */
