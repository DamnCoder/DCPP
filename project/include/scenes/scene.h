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

#include "signals/signal.h"

namespace dc
{
	class CScene
	{
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
	public:
		CSignal<void(const TComponentList&)> OnComponentsAdded;
		
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
		const char*			Name()			const { return mp_name; }
		const unsigned int	RootCount()		const { return m_goList.size(); }
		const TGOList&		GameObjects()	const { return m_goList; }
		
		const bool			Exists(const CGameObject* gameObject);
		
		template<typename CT>
		std::vector<CT*> GetSceneComponents();
		
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
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
	template<typename CT>
	std::vector<CT*> CScene::GetSceneComponents()
	{
		const auto& componentsEntryIt = m_componentsMap.find(CT::TypeName());
		assert(componentsEntryIt != m_componentsMap.end() && "[CScene::GetSceneComponents] You shouldn't be asking for Components that doesn't exist");
		
		const TComponentList& componentList = componentsEntryIt->second;
		std::vector<CT*> castedComponentList(componentList.size());
		
		for(CComponent* component : componentList)
		{
			CT* castedComponent = component->DirectCast<CT>();
			castedComponentList.push_back(castedComponent);
		}
		
		return castedComponentList;
	}
}

#endif /* scene_h */
