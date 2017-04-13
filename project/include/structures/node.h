//
//	#FILENAME
//	#PROJECT_NAME
//
//	Created by #AUTHOR on #DATE.
//

#ifndef node_h
#define node_h

#include "help/deletehelp.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	template<typename T>
	class CNode
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
		CNode<T>* Link() const
		{
			return mp_link;
		}
		
		const T& Data() const
		{
			return m_data;
		}
		
		void Connect(CNode* node)
		{
			mp_link = node;
		}
		
		void Data(const T& data)
		{
			m_data = data;
		}
		
		const bool Connected() const { return mp_link != 0; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CNode() :
			mp_link (0)
		{}
		
		CNode(const T& data) :
			mp_link (0),
			m_data (data)
		{}
		
		CNode(const T& data, CNode<T>* link) :
			mp_link (link),
			m_data (data)
		{}
		
		~CNode()
		{
			SafeDelete(mp_link);
		}
		
		CNode(const CNode<T>& copy):
			mp_link(copy.mp_link),
			m_data(copy.data)
		{}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void operator= (const CNode<T>& copy)
		{
			this(copy);
		}
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	public:
		CNode*	mp_link;
		T		m_data;
	};

	// ===========================================================
	// Class typedefs
	// ===========================================================
}

#endif /* #CLASS_NAME */
