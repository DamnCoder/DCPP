
//
//	proxy
//	DCPP
//
//	Created by Jorge López González on 09/11/12.
//


#ifndef CPROXY_H
#define CPROXY_H

#include <map>
#include <utility>
#include "help/utils.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	/**
	 * \class CProxy
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */

    template<typename T>
    class CProxy
    {
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
	private:
		using TProxyPair	= std::pair<int, T*>;
		using TProxyMap		= std::map<const char*, TProxyPair, cmp_c_str>;
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const bool	Exists(const char* key)	const { return m_proxy.find(key) != m_proxy.end(); }
		
		const int	Count(const char* key)	const { return Find(key)->first; }
		const int	Count()					const { return m_proxy.size(); }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
        CProxy()
        {};
        
        ~CProxy()
        {};
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
		
    public:
		void		Add(const char* key, T* element);
		T&			GetRef(const char* key);
		T*			GetPtr(const char* key);
		
        template<typename ST>
		ST*			GetTyped(const char* key);
		
		void		Remove(const char* key);
		void		Clear();
		
    private:
		TProxyPair& Find(const char* key) const;
		void		DeleteProxyPair(TProxyPair& elementTuple);
		
		// ===========================================================
		// Fields
		// ===========================================================
    private:
        TProxyMap m_proxy;
    };
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
	template<typename T>
	inline
	void CProxy<T>::Add(const char* key, T* element)
	{
		m_proxy[key] = TProxyPair(1, element);
	}
	
	template<typename T>
	inline
	T& CProxy<T>::GetRef(const char* key)
	{
		return *GetPtr(key);
	}

	template<typename T>
	inline
	T* CProxy<T>::GetPtr(const char* key)
	{
		typename TProxyMap::iterator it = m_proxy.find(key);
		
		assert(it != m_proxy.end());
		
		TProxyPair& tuple = it->second;
		
		// First element corresponds to the reference counter
		tuple.first += 1;
		
		// Second element is the pointer to the object stored
		return tuple.second;
	}
	
	template<typename T>
	template<typename ST>
	inline
	ST* CProxy<T>::GetTyped(const char* key)
	{
		return static_cast<ST*>(GetPtr(key));
	}
	
	template<typename T>
	inline
	void CProxy<T>::Remove(const char* key)
	{
		TProxyPair* elementTuple = Find(key);
		
		// If exists at least one reference to the element
		if(0 < elementTuple->first)
		{
			// We decrease the reference counter
			--elementTuple->first;
		}
		
		// If the reference counter reaches zero, we destroy the element
		if(elementTuple->first == 0)
		{
			m_proxy.erase(key);
			delete elementTuple->second;
			elementTuple->second = 0;
		}
	}
	
	template<typename T>
	inline
	void CProxy<T>::Clear()
	{
		typename TProxyMap::iterator it, end;
		it = m_proxy.begin();
		end = m_proxy.end();
		for(; it!=end; ++it)
		{
			// We destroy the element stored
			delete it->second;
			it->second = 0;
		}
		
		m_proxy.clear();
	}
	
	template<typename T>
	inline
	typename CProxy<T>::TProxyPair& CProxy<T>::Find(const char* key) const
	{
		typename TProxyMap::const_iterator it, end; it = m_proxy.find(key);
		assert(it != m_proxy.end());
		return it->second;
	}
}

#endif
