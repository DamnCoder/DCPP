#ifndef MESHTATICO_H
#define MESHTATICO_H

#include "containers/array.h"
#include "vertices.h"

#include <math/dcmath.h>

#include <map>

namespace dc
{
	class CMesh
	{
		// ===========================================================
		// Constant / Enums / Typedefs
		// ===========================================================
	private:
		using TFloatDataMap = std::map<const char*, TFloatArray>;
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
	public:
		
		static const char* VERTEX_ID;
		static const char* NORMAL_ID;
		static const char* UV0_ID;
		static const char* UV1_ID;
		static const char* COLOR_ID;
		
		static const char* INDICES_ID;
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const bool IsValid() const;
		
		const char* Name() const
		{
			return m_name;
		}
		
		const int IndexCount() const
		{
			return m_indexCount;
		}
		
		void IndexCount(const unsigned int indexCount)
		{
			m_indexCount = indexCount;
		}
		
		const int VertexCount() const
		{
			return m_vertexCount;
		}
		
		void VertexCount(const unsigned int vertexCount)
		{
			m_vertexCount = vertexCount;
		}
		
		const math::Vector3f& Center() const
		{
			return m_center;
		}

		const math::Vector3f& Size() const
		{
			return m_size;
		}

		TFloatArray& FloatDataArray(const char* id);
		
		void FloatDataArray(const char* id, TFloatArray& floatArray);
		
		void AddFloatDataArray(const char* id, TFloatArray& floatArray);
		
		const TUIntArray& IndexArray() const { return m_indexArray; }
		
		void IndexArray (const TUIntArray indexArray)
		{
			m_indexArray = indexArray;
		}
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CMesh(const char* name) :
				m_name(name), m_indexCount(0), m_vertexCount(0), m_center(), m_size()
		{}

		~CMesh()
		{}

		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:

		/**
		 * Resizes the mesh without modificate the current mesh data
		 */
		void Resize(const int vertexCount, const int indexCount);

		/**
		 * Merges this mesh with another one and stores the result in
		 * this mesh. The other mesh is not modified at all in the process.
		 * \param mesh the mesh you want to merge with this one.
		 */
		CMesh* MergeWith(const CMesh* mesh);

		/**
		 * Calculates size and center of this mesh.
		 */
		void CalculateMeshDimensions();

		// ===========================================================
		// Fields
		// ===========================================================
	private:
		const char*		m_name;
		
		unsigned int	m_indexCount;
		unsigned int	m_vertexCount;
		
		math::Vector3f	m_center;
		math::Vector3f	m_size;

		TFloatDataMap	m_floatDataMap;
		TUIntArray		m_indexArray;
	};
}

#endif

