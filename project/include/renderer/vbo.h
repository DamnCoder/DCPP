//
//  vbo.hpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef vbo_h
#define vbo_h

#include <vector>
#include <map>

#include "containers/array.h"

#include "glwraps.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	template <typename ArrayType>
	class CVBO
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
	public:
		static CVBO<ArrayType> Create(CArray<ArrayType>& array, const unsigned int typeSize, const EVBOTarget target, const EVBOUsage usage);
		static void Destroy(const CVBO<ArrayType>& vbo);
		
		static void Submit(const CVBO<ArrayType>& vbo);
		static void Activate(const CVBO<ArrayType>& vbo);
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const unsigned int			Id()			const { return m_id; }
		const EVBOTarget			Target()		const { return m_target; }
		const EVBOUsage				Usage()			const { return m_usage; }
		const CArray<ArrayType>&	DataArray()		const { return m_dataArray; }
		const unsigned int			TypeSize()		const { return m_typeSize; }
		const size_t				MemorySize()	const { return m_dataArray.Size() * sizeof(ArrayType); }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CVBO ():
			m_id(0),
			m_typeSize(0),
			m_target(EVBOTarget::ARRAY),
			m_usage(EVBOUsage::STREAM_DRAW)
		{}
		
		CVBO (const unsigned int identifier, const EVBOTarget target, const EVBOUsage usage, CArray<ArrayType> dataArray, const unsigned int typeSize):
			m_id(identifier),
			m_typeSize(typeSize),
			m_target(target),
			m_usage(usage),
			m_dataArray(dataArray)
		{}

		CVBO (const CVBO<ArrayType>& vbo):
			m_id(vbo.m_id),
			m_typeSize(vbo.m_typeSize),
			m_target(vbo.m_target),
			m_usage(vbo.m_usage),
			m_dataArray(vbo.m_dataArray)
		{}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void operator= (const CVBO<ArrayType>& vbo);
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		unsigned int		m_id;
		unsigned int		m_typeSize;
		EVBOTarget			m_target;
		EVBOUsage			m_usage;
		CArray<ArrayType>	m_dataArray;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	template<typename ArrayType>
	using TVBOList = std::vector<CVBO<ArrayType>>;
	
	using TFloatVBOList = TVBOList<float>;
	using TUIntVBOList = TVBOList<unsigned int>;
	
	using TUIntVBO = CVBO<unsigned int>;
	using TFloatVBO = CVBO<float>;
	
	// ===========================================================
	// Template implementation
	// ===========================================================
	
	template<typename ArrayType>
	inline
	CVBO<ArrayType> CVBO<ArrayType>::Create(CArray<ArrayType>& array, const unsigned int typeSize, const EVBOTarget target, const EVBOUsage usage)
	{
		GLuint identifier;
		glGenBuffers(1, &identifier);
		return CVBO<ArrayType>((unsigned int)identifier, target, usage, array, typeSize);
	}
	
	template<typename ArrayType>
	inline
	void CVBO<ArrayType>::Destroy(const CVBO<ArrayType>& vbo)
	{
		const GLuint identifier = (GLuint)vbo.Id();
		glDeleteBuffers(1, &identifier);
	}
	
	template<typename ArrayType>
	inline
	void CVBO<ArrayType>::Submit(const CVBO<ArrayType>& vbo)
	{
		glBindBuffer(vbo.Target(), vbo.Id());
		glBufferData(vbo.Target(), vbo.MemorySize(), vbo.DataArray().Data(), vbo.Usage());
	}
	
	template<typename ArrayType>
	inline
	void CVBO<ArrayType>::Activate(const CVBO<ArrayType>& vbo)
	{
		const GLuint identifier = (GLuint)vbo.Id();
		glBindBuffer(vbo.Target(), identifier);
	}
	
	template<typename ArrayType>
	inline
	void CVBO<ArrayType>::operator= (const CVBO<ArrayType>& vbo)
	{
		m_id = vbo.m_id;
		m_typeSize = vbo.m_typeSize;
		m_target = vbo.m_target;
		m_usage = vbo.m_usage;
		m_dataArray = vbo.m_dataArray;
	}
}

#endif /* vbo_hpp */
