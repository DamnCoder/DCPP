//
//  Array.h
//  BitThemAll
//
//  Created by Jorge López González on 30/07/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef BitThemAll_Array_h
#define BitThemAll_Array_h

#include <assert.h>
#include <algorithm>

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================

    template<class T>
    class CArray
    {
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		const unsigned int GROW_NUM = 10;
		
		using iterator = T*;
		using const_iterator = const T*;
		
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
		operator		T	*()			const { return mp_data; }
		const unsigned int	MaxSize()	const { return m_maxSize; }
		const unsigned int	Size()		const { return m_currentSize; }
		const T*            Data()		const { return mp_data; }
		const bool			Empty()		const { return m_currentSize == 0; }
		const bool          IsValid()	const { return m_maxSize >= 0 && m_currentSize >= 0 && mp_data != 0; }

		iterator begin() { return &mp_data[0]; }
		iterator end() { return &mp_data[m_currentSize]; }
		
		const_iterator begin() const { return &mp_data[0]; }
		const_iterator end() const { return &mp_data[m_currentSize]; }
		
		
		inline
		const bool			IsInside(const unsigned int i) const
		{
			return (0<=i && i<m_maxSize);
		}
		
	private:
		inline const bool	IsOutOfBounds(const unsigned int length)
		{
			return (m_maxSize < length);
		}
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CArray():
			m_maxSize(GROW_NUM),
			m_currentSize(0),
			mp_data(new T[GROW_NUM])
		{};
		
		CArray(const unsigned int maxSize):
			m_maxSize(maxSize),
			m_currentSize(0),
			mp_data(new T[m_maxSize])
		{
			assert(0 < m_maxSize);
		};
		
		CArray(const CArray<T>& copy):
			m_maxSize(copy.m_maxSize),
			m_currentSize(0),
			mp_data(new T[m_maxSize])
		{
			Append(copy.mp_data, copy.m_currentSize);
		}
		
		~CArray()
		{
			m_currentSize = 0;
			m_maxSize = 0;
			
			delete [] mp_data;
			mp_data = 0;
		};

		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void operator= (const CArray<T>& copy)
		{
			m_maxSize = copy.m_maxSize;
			m_currentSize = 0;
			mp_data = new T[m_maxSize];
			
			Append(copy.mp_data, copy.m_currentSize);
		}
		
		T& operator[] (const unsigned int index)
		{
			return mp_data[index];
		}
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Init(const int maxSize)
		{
			// We cannot initialize an array currently initialized
			assert(0 < maxSize && mp_data == 0);
			m_maxSize = maxSize;
			m_currentSize = 0;
			mp_data = new T[maxSize];
		}
		
		/**
		 * Returns a member of the array
		 */
		T& At(const unsigned int index) const
		{
			assert(IsInside(index));
			return mp_data[index];
		};
		
		/**
		 * Returns a sub array of data
		 */
		const T* At(const unsigned int index, const unsigned int dataLength) const
		{
			assert(IsInside(index + dataLength - 1));
			T* outputData = new T[dataLength];
			std::copy(mp_data + index, mp_data + index + dataLength, outputData);
			return outputData;
		};
		
		void Set(const unsigned int index, const T& value)
		{
			assert(IsInside(index));
			mp_data[index] = value;
			m_currentSize = std::max(m_currentSize, index + 1);
		}
		
		void Set(const unsigned int index, const T* data, const unsigned int dataLength)
		{
			unsigned int newLength = index + dataLength;
			if(IsOutOfBounds(newLength))
			{
				unsigned int lengthAddition = newLength - m_maxSize;
				Resize(lengthAddition);
			}
			std::copy(data, data + dataLength, mp_data+index);
			m_currentSize = std::max<unsigned int>(m_currentSize, index + dataLength);
		}
		
		void Append(const T& value)
		{
			unsigned int newLength = m_currentSize + 1;
			if(IsOutOfBounds(newLength))
			{
				Resize(GROW_NUM);
			}
			mp_data[m_currentSize++] = value;
		}
		
		void Append(const T* data, const unsigned int dataLength)
		{
			unsigned int newLength = m_currentSize + dataLength;
			if(IsOutOfBounds(newLength))
			{
				unsigned int lengthAddition = newLength - m_maxSize;
				Resize(lengthAddition);
			}
			
			std::copy(data, data + dataLength, mp_data + m_currentSize);
			m_currentSize += dataLength;
		}
		
		void Resize(const unsigned int growthAddition)
		{
			assert(0 < growthAddition);
			m_maxSize += growthAddition;
			T* newStorage = new T[m_maxSize];
			std::copy(mp_data, mp_data + m_currentSize, newStorage);
			delete [] mp_data;
			mp_data = newStorage;
		}
		
		void Merge(const CArray<T>& array)
		{
			Resize(array.MaxSize());
			Append(array.Data(), array.Size());
		}
		
		void Clear()
		{
			m_currentSize = 0;
			// We can optimize a bit just by not deleting the data yet, and keeping the memory to be reused
		}

		// ===========================================================
		// Fields
		// ===========================================================
    private:
        unsigned int	m_maxSize;
        unsigned int	m_currentSize;
        T*              mp_data;
        
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	using TFloatArray	= CArray<float>;
	using TUIntArray	= CArray<unsigned int>;
	using TUShortArray	= CArray<unsigned short>;
}
#endif
