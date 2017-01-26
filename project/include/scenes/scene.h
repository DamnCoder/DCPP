//
//  scene.h
//  DCPPTest
//
//  Created by Jorge López on 20/1/17.
//
//

#ifndef scene_h
#define scene_h

#include <list>

#include "component/gameobject.h"

namespace dc
{
	class CScene
	{
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Constant / Enums / Typedefs
		// ===========================================================
		using GOList = std::list<GameObject*>;
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const char*			Name()				const { return mp_name; }
		const unsigned int	RootCount()			const { return m_goList.size(); }
		const GOList&		GameObjectList()	const { return m_goList; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CScene(const char* name) : mp_name(name) {}
		virtual ~CScene() {}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
		void Add(GameObject* gameObject)
		{
			m_goList.push_back(gameObject);
		}
		
		void Remove(GameObject* gameObject)
		{
			m_goList.remove(gameObject);
		}
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		const char*	mp_name;
		GOList		m_goList;
	};
}

#endif /* scene_h */
