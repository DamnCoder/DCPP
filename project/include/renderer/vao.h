//
//  vao.h
//  DCPPTest
//
//  Created by Jorge López on 26/4/17.
//
//

#ifndef vao_h
#define vao_h

#include <map>

#include "mesh/mesh.h"

#include "vertexproperty.h"
#include "vbo.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	using TBufferMap = std::map<const CVertexProperty*, TFloatVBO>;
	
	/**
	 * \class
	 * \brief
	 * \author Jorge Lopez Gonzalez
	 *
	 * Description.
	 */
	class CVAO
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
	public:
		static CVAO Create(CMesh* mesh, const TVertexPropertyMap& vertexPropertyMap);
		
		static void	Submit(CVAO& vao);
		
		static void Activate(const CVAO& vao);
		
		static void Deactivate();
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const unsigned int	Id()		const { return m_id; }
		
		const TUIntVBO&		IndexVBO()	const { return m_indexVBO; }
		
		const TBufferMap&	BufferMap()	const { return m_bufferMap; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CVAO():
			m_id (0)
		{}
		
		CVAO(const unsigned int identifier, TUIntVBO indexVBO, TBufferMap bufferMap):
			m_id (identifier),
			m_indexVBO(indexVBO),
			m_bufferMap(bufferMap)
		{}
		
		~CVAO()
		{}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		unsigned int	m_id;
		
		TUIntVBO		m_indexVBO;
		TBufferMap		m_bufferMap;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	using TVAOList = std::vector<CVAO>;
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}


#endif /* vao_hpp */
