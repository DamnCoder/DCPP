
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
		using TProxyPair	= std::pair<int, T>;
		using TProxyMap		= std::map<const char*, TProxyPair>;
		
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
		void		Add(const char* key, T element);
		T&			Get(const char* key);
		
        template<typename ST>
		ST			GetTyped(const char* key);
		
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
	void CProxy<T>::Add(const char* key, T element)
	{
		m_proxy[key] = TProxyPair(1, element);
	}
	
	template<typename T>
	inline
	T& CProxy<T>::Get(const char* key)
	{
		typename TProxyMap::iterator it = m_proxy.find(key);
		
		assert(it != m_proxy.end());
		
		TProxyPair& tuple = it->second;
		
		// First element corresponds to the reference counter
		tuple->first += 1;
		
		// Second element is the pointer to the object stored
		return tuple->second;
	}
	
	template<typename T>
	template<typename SpecializedType>
	inline
	SpecializedType CProxy<T>::GetTyped(const char* key)
	{
		return static_cast<SpecializedType>(Get(key));
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
			DeleteProxyPair(elementTuple);
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
			DeleteProxyPair(it->second);
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
	
	template<typename T>
	inline
	void CProxy<T>::DeleteProxyPair(TProxyPair& elementTuple)
	{
		// We destroy the element stored
		delete elementTuple->second;
		elementTuple->second = 0;
	}
}

#endif
