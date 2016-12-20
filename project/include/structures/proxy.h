//
//  bag.h
//  BitThemAll
//
//  Created by Jorge López González on 09/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __BitThemAll__bag__
#define __BitThemAll__bag__

#include <string>
#include <map>
#include <utility>

namespace dc
{
    
    template<typename T>
    class CProxy
    {
    public:
        typedef std::pair<int, T> TProxyPair;
        typedef std::map<const std::string, TProxyPair*> TProxyMap;
        typedef typename TProxyMap::iterator TProxyIterator;
        typedef typename TProxyMap::const_iterator TProxyConstIterator;
        
        CProxy()
        {};
        
        ~CProxy()
        {};
        
    public:
        void Add(const std::string& key, T element)
        {
            // The reference counter starts with 0 because it is supposed that the original reference
            // is no longer used
            mm_proxy[key] = new TProxyPair(0, element);
        }
        
        T Get(const std::string& key)
        {
            TProxyIterator it = mm_proxy.find(key);
            
            assert(it != mm_proxy.end());
            
            TProxyPair* tuple = it->second;
            
            // First element corresponds to the reference counter
            ++tuple->first;
            
            // Second element is the pointer to the object stored
            return tuple->second;
        }
        
        template<typename SpecializedType>
        SpecializedType GetTyped(const std::string& key)
        {
            return static_cast<SpecializedType>(Get(key));
        }
        
        void Remove(const std::string& key)
        {
            TProxyPair* elementTuple = Find(key);
            
            // If the reference counter reaches zero, we destroy the element
            if(elementTuple->first == 0)
            {
                DeleteProxyPair(elementTuple);
            }
            // If exists at least one reference to the element
            else if(0 < elementTuple->first)
            {
                // We decrease the reference counter
                --elementTuple->first;
            }
        }
        
        void Clear()
        {
            TProxyIterator it, end;
            it = mm_proxy.begin();
            end = mm_proxy.end();
            for(; it!=end; ++it)
            {
                DeleteProxyPair(it->second);
            }
            
            mm_proxy.clear();
        }
        
        const bool Exists(const std::string& key) const
        {
            return mm_proxy.find(key) != mm_proxy.end();
        }
        
        const int Count(const std::string& key) const
        {
            // It returns the reference counter
            return Find(key)->first;
        }
        
        const int Count() const
        {
            return mm_proxy.size();
        }
        
        TProxyPair* Find(const std::string& key) const
        {
            TProxyConstIterator it = mm_proxy.find(key);
            assert(it != mm_proxy.end());
            return it->second;
        }
        
    private:
        
        void DeleteProxyPair(TProxyPair* elementTuple)
        {
            // We destroy the element stored
            delete elementTuple->second;
            elementTuple->second = 0;
            
            // The pair is destroyed too
            delete elementTuple;
            elementTuple = 0;
        }
        
    private:
        TProxyMap mm_proxy;
    };
}

#endif /* defined(__BitThemAll__bag__) */
