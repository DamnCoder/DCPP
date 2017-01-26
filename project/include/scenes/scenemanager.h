//
//  scenemanager.h
//  DCPPTest
//
//  Created by Jorge López on 21/1/17.
//
//

#ifndef scenemanager_h
#define scenemanager_h

#include <list>

#include "scene.h"

namespace dc
{
	using TSceneList = std::list<CScene*>;
	
	class CSceneManager
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
		const TSceneList& SceneList() const { return m_sceneList; }
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CSceneManager() {}
		virtual ~CSceneManager() {}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Add(CScene* scene);
		void Remove(CScene* scene);
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		TSceneList	m_sceneList;
		
	};
}

#endif /* scenemanager_h */
