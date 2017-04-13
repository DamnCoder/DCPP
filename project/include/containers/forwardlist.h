//
//  forwardlist
//
//  A forward list
//  Created by Jorge López González on 30/07/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef forwardlist_h
#define forwardlist_h

#include <assert.h>
#include <algorithm>

#include "structures/node.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
    template<class T>
    class CForwardList
    {
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		
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
		const unsigned int	Size()		const { return m_size; }
		const bool			Empty()		const { return m_size == 0; }
		
		const bool			IsInside(const unsigned int i) const
		{
			return 0 <= i && i < m_size;
		}
		
		const T&			First()		const
		{
			assert(mp_node);
			return mp_node->Data();
		}
		
		CNode<T>*			FirstNode()	const { return mp_node; }
		CNode<T>*			LastNode()	const
		{
			CNode<T>* node = mp_node;
			while(node->Connected())
			{
				node = node->Link();
			}
			return node;
		}

		// ===========================================================
		// Constructors
		// ===========================================================
    public:
		CForwardList() :
			m_size(0),
			mp_node(0)
        {}
		
		CForwardList(const CForwardList<T>& copy):
			m_size(copy.m_size),
			mp_node(copy.mp_node)
		{
		}
        
        ~CForwardList()
        {
        }
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		void operator= (const CForwardList<T>& copy)
		{
			this(copy);
		}
		
		// ===========================================================
		// Methods
		// ===========================================================
    public:
        
        /**
         * Returns a member of the array
         */
        T& At(const unsigned int index) const
        {
            assert(IsInside(index) && mp_node);
			CNode<T> currentNode = 0;
			CNode<T> nextNode = mp_node;
			for(unsigned int i=0; i<=index; ++i)
			{
				currentNode = nextNode;
				nextNode = nextNode->Link();
			}
            return currentNode->Data();
        };
        
        void AppendLast(const T& value)
        {
			++m_size;
			CNode<T> newNode = new CNode<T>(value);
			if(!mp_node)
			{
				mp_node = newNode;
			}
			else
			{
				CNode<T>* node = LastNode();
				node->Connect(new CNode<T>(value));
			}
		}
		
		void AppendFirst(const T& value)
		{
			++m_size;
			if(!mp_node)
			{
				mp_node = new CNode<T>(value);
			}
			else
			{
				CNode<T>* node = mp_node;
				mp_node = new CNode<T>(value, node);
			}
		}
		
		void Remove(const unsigned int index)
		{
			assert(IsInside(index) && mp_node);
			CNode<T> previousNode = 0;
			CNode<T> currentNode = 0;
			CNode<T> nextNode = mp_node;
			for(unsigned int i=0; i<=index; ++i)
			{
				currentNode = nextNode;
				nextNode = nextNode->Link();
				
				if(i == (index-1))
				{
					previousNode = currentNode;
				}
			}
			
			delete currentNode;
			previousNode->Connect(nextNode);
			--m_size;
		}
		
        void Merge(const CForwardList<T>& forwardList)
        {
			
		}
        
        void Clear()
        {
        }
		
		// ===========================================================
		// Fields
		// ===========================================================
    private:
        // Atributes
		unsigned int	m_size;
		CNode<T>*		mp_node;
        
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
}
#endif
