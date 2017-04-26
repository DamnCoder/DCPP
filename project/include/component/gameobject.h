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
		const char*					Name()		const			{ return m_id; }
		void						Name(const char* name)		{ m_id = name; }
		
		const char*					LayerName() const			{ return m_layer; }
		void						LayerName(const char* name) { m_layer = name; }
		
		const unsigned int			ComponentsNum(const char* compId) const;

		const TComponentListTable&	ComponentsTable() const { return m_componentTable; }
		
		/**
		 * Returns the first component of the specified type
		 */
		template<typename ComponentType>
		ComponentType*				GetComponent() const;
		
		/**
		 * Returns all the components of the specified type in an array
		 */
		template<typename ComponentType>
		std::vector<ComponentType*>	GetComponents() const;

	private:
		const TComponentList&		GetComponents(const char* compId) const;
		
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
		 * Creates a component and adds it to the GameObject
		 */
		CComponent* AddComponent(CComponent* component);

		template<typename ComponentType>
		ComponentType* AddComponent();
		
		/**
		 * Removes a component of the specified type from the GameObject and destroys it
		 */
		void RemoveComponent(const char* name);

		template<typename ComponentType>
		void RemoveComponent();

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
		ComponentType* component = GetComponents<ComponentType>().front();
		return component;
	}
	
	template<typename ComponentType>
	std::vector<ComponentType*> CGameObject::GetComponents() const
	{
		const TComponentList& componentList = GetComponents(ComponentType::TypeName());
		
		std::vector<ComponentType*> castedComponentList;
		castedComponentList.reserve(componentList.size());
		
		for(CComponent* component : componentList)
		{
			ComponentType* castedComponent = component->DirectCast<ComponentType>();
			castedComponentList.push_back(castedComponent);
		}
		
		return castedComponentList;
	}
	
	template<typename ComponentType>
	ComponentType* CGameObject::AddComponent()
	{
		ComponentType* component = new ComponentType();
		AddComponent(component);
		return component;
	}
	
	template<typename ComponentType>
	void CGameObject::RemoveComponent()
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
