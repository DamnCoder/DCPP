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
    // Forward declarations
	template <class T>
    class CArray;
    
    typedef CArray<float>           TFloatArray;
    typedef CArray<unsigned int>    TUIntArray;
    typedef CArray<unsigned short>  TUShortArray;
    
    // Class declaration
    template<class T>
    class CArray
    {
    // Constructors
    public:
        CArray():
            m_id(0),
            m_maxSize(0),
            m_currentSize(0),
            mp_data(0)
        {};
        
        CArray(const unsigned int maxSize):
            m_id(0),
            m_maxSize(maxSize),
            m_currentSize(0),
            mp_data(new T[m_maxSize])
        {
            assert(0 < m_maxSize);
        };
		
		CArray(const CArray<T>& copy):
			m_id(copy.m_id),
			m_maxSize(copy.m_maxSize),
			m_currentSize(0),
			mp_data(new T[m_maxSize])
		{
			Append(copy.mp_data, copy.m_currentSize);
		}
        
        ~CArray()
        {
            delete [] mp_data;
        };
        
        void Init(const int maxSize)
        {
            // We cannot initialize an array currently initialized
            assert(0 < maxSize && mp_data == 0);
            m_maxSize = maxSize;
            m_currentSize = 0;
            mp_data = new T[maxSize];
        }
        
    // Accesors
    public:
		operator		T	*()			const { return mp_data; }
        const unsigned int	Id()		const { return m_id; }
        const unsigned int	MaxSize()	const { return m_maxSize; }
        const unsigned int	Size()		const { return m_currentSize; }
        const T*            Data()		const { return mp_data; }
        const bool          IsValid()	const { return m_currentSize > 0; }
        
        void SetId(const unsigned int identifier) { m_id = identifier; }
		
		inline const bool IsInsideLimits(const unsigned int i) const
		{
			return (0<=i && i<m_maxSize);
		}
		
	private:
		inline const bool IsOutOfBounds(const unsigned int length)
		{
			return (m_maxSize < length);
		}
		
    // Public interface
    public:
		
        T& operator[] (const unsigned int index)
        {
            return mp_data[index];
        }
        
        /**
         * Returns a member of the array
         */
        T& At(const unsigned int index) const
        {
            assert(IsInsideLimits(index));
            return mp_data[index];
        };
        
        /**
         * Returns a sub array of data
         */
        const T* At(const unsigned int index, const unsigned int dataLength) const
        {
            assert(IsInsideLimits(index + dataLength));
            T* outputData = new T[dataLength];
            std::copy(mp_data + index, mp_data + index + dataLength, outputData);
            return outputData;
        };
        
        void Set(const unsigned int index, const T& value)
        {
            assert(IsInsideLimits(index));
            mp_data[index] = value;
            m_currentSize = std::max(m_currentSize, index);
        }
        
        void Set(const unsigned int index, const T* data, const unsigned int dataLength)
        {
            assert(IsInsideLimits(index + dataLength));
            std::copy(data, data + dataLength, mp_data+index);
            m_currentSize = std::max<unsigned int>(m_currentSize, index + dataLength);
        }
        
        void Append(const T& value)
        {
            assert(m_currentSize < m_maxSize);
            mp_data[m_currentSize++] = value;
        }
        
        void Append(const T* data, const unsigned int dataLength)
        {
            assert(!IsOutOfBounds(m_currentSize + dataLength));
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
            m_maxSize = 0;
            
            delete [] mp_data;
            mp_data = 0;
        }
        
    private:
        // Atributes
        unsigned int    m_id;
        unsigned int	m_maxSize;
        unsigned int	m_currentSize;
        T*              mp_data;
        
	};
}
#endif
