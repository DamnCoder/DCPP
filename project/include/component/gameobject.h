//
//  gameobject.h
//  DCPP
//
//  Created by Jorge López González on 26/12/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __game_object__
#define __game_object__

#include "component.h"

#include "renderer/renderlayermanager.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
    class CGameObject
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
		const char*			Name()		const			{ return m_id; }
		void				Name(const char* name)		{ m_id = name; }
		
		const char*			LayerName() const			{ return m_layer; }
		void				LayerName(const char* name) { m_layer = name; }
		
		const unsigned int	ComponentsNum(const char* compId) const;
		
		/**
		 * Returns the first component of the specified type
		 */
		template<typename ComponentType>
		ComponentType*	GetComponent() const;
		
		/**
		 * Returns all the components of the specified type in an array
		 */
		template<typename ComponentType>
		TComponentList	GetComponents() const;

		const TComponentListTable&	ComponentsTable() const { return m_componentTable; }
		
	private:
		const TComponentList* GetComponentList(const char* compId) const;
		
		template<typename ComponentType>
		const TComponentList* GetComponentList() const;
		
		// ===========================================================
		// Constructors
		// ===========================================================
    public:
        CGameObject(const char* name):
            m_id(name),
			m_layer(CRenderLayerManager::DEFAULT_LAYER)
        {}
		
		CGameObject(const char* name, const char* layerName):
			m_id(name),
			m_layer(layerName)
		{}
		
		~CGameObject();
		
		CGameObject(const CGameObject& copy) = delete;
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void operator= (const CGameObject& copy) = delete;
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		/**
		 * Adds a previously created component
		 */
		CComponent* AddComponent(CComponent* component);
		
		/**
		 * Removes the component from the GameObject and returns its ownership to the caller
		 */
		CComponent* RemoveComponent(const char* name);
		CComponent* RemoveComponent(CComponent* component);
		
		/**
		 * Removes the component from the GameObject and destroys it
		 */
		void DestroyComponent(CComponent* component);
		
		/**
		 * Creates a component and adds it to the GameObject
		 */
		template<typename ComponentType>
		ComponentType* CreateComponent();
		
		/**
		 * Removes a component of the specified type from the GameObject and destroys it
		 */
		template<typename ComponentType>
		void DestroyComponent();
		
		// ===========================================================
		// Fields
		// ===========================================================
    private:
        
        const char*			m_id;
		const char*			m_layer;
		TComponentListTable	m_componentTable;
    };
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	using TGOList = std::vector<CGameObject*>;
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================

	template<typename ComponentType>
	ComponentType* CGameObject::GetComponent() const
	{
		CComponent* component = GetComponentList<ComponentType>()->front();
		return component->CComponent::template DirectCast<ComponentType>();
	}
	
	template<typename ComponentType>
	TComponentList CGameObject::GetComponents() const
	{
		TComponentList& componentList = *GetComponentList<ComponentType>();
		
		const unsigned int componentsCount = componentList.size();
		TComponentList castedComponentList(componentsCount);
		
		for(const CComponent* component : componentList)
		{
			castedComponentList.push_back(component->DirectCast<ComponentType>());
		}
		
		return castedComponentList;
	}
	
	template<typename ComponentType>
	const TComponentList* CGameObject::GetComponentList() const
	{
		return GetComponentList(ComponentType::TypeName());
	}
	
	template<typename ComponentType>
	ComponentType* CGameObject::CreateComponent()
	{
		ComponentType* component = new ComponentType();
		AddComponent(component);
		return component;
	}
	
	template<typename ComponentType>
	void CGameObject::DestroyComponent()
	{
		CComponent* component = RemoveComponent(ComponentType::TypeName());
		if(component)
		{
			delete component;
			component = 0;
		}
	}
}

#endif /* defined(__game_object__) */
