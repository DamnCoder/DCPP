//
//  scene.h
//  DCPPTest
//
//  Created by Jorge López on 20/1/17.
//
//

#ifndef scene_h
#define scene_h

#include <vector>

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
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const char*			Name()				const { return mp_name; }
		const unsigned int	RootCount()			const { return m_goList.size(); }
		const TGOList&		GameObjectList()	const { return m_goList; }
		
		const bool			Exists(const CGameObject* gameObject);
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CScene(const char* name) : mp_name(name) {}
		~CScene() {}
		
		CScene(const CScene& copy) = delete;
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		void operator= (const CScene& copy) = delete;
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Update();
		
		void PrepareUpdate();
		void FinishUpdate();
		
		void Add(CGameObject* gameObject);
		
		void Remove(CGameObject* gameObject);
		
	private:
		void AddToScene(CGameObject* gameObject);
		void RemoveFromScene(CGameObject* gameObject);
		
		void AddComponents(const char* name, const TComponentList& componentList);
		void RemoveComponents(const char* name, const TComponentList& componentList);
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		const char*			mp_name;
		TGOList				m_goList;
		
		TGOList				m_newGOList;
		TGOList				m_oldGOList;
		
		TComponentListTable	m_componentsMap;
	};
}

#endif /* scene_h */
