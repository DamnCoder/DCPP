//
//  scenemanager.h
//  DCPPTest
//
//  Created by Jorge López on 21/1/17.
//
//

#ifndef scenemanager_h
#define scenemanager_h

#include <vector>

#include "scene.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TSceneList = std::vector<CScene*>;
	
	class CSceneManager
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
		const TSceneList& SceneList() const { return m_sceneList; }
		
		CScene* Scene(const char* name);
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CSceneManager() {}
		~CSceneManager() {}
		
		CSceneManager(const CSceneManager& copy) = delete;
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		void operator= (const CSceneManager& copy) = delete;
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Add(CScene* scene);
		
		void Remove(const char* name);
		void Remove(CScene* scene);
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		TSceneList	m_sceneList;
		
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* scenemanager_h */
