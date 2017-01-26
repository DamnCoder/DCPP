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

#include <map>
#include <forward_list>
#include <vector>

namespace dc
{
	using GOID = std::string;
    using TComponentList = std::forward_list<Component*>;
	
    class GameObject
    {
	private:
		using TComponentsEntry = std::pair<unsigned int, TComponentList>;
		using TComponentListTable = std::map<const CompId, TComponentsEntry>;
		
	public:
		const unsigned int ComponentsNum(const CompId& compId) const;
		
    public:
        GameObject(const GOID& id):
            m_id(id)
        {}
        
        ~GameObject()
        {}
		
	public:
		/**
		 * Adds a previously created component
		 */
		Component* AddComponent(Component* component);
		
		/**
		 * Removes the component from the GameObject and returns its ownership to the caller
		 */
		Component* RemoveComponent(const CompId& name);
		Component* RemoveComponent(Component* component);
		
		/**
		 * Removes the component from the GameObject and destroys it
		 */
		void DestroyComponent(Component* component);
		
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
		
		/**
		 * Returns the first component of the specified type
		 */
		template<typename ComponentType>
		ComponentType* GetComponent() const;
		
		/**
		 * Returns all the components of the specified type in an array
		 */
		template<typename ComponentType>
		std::vector<ComponentType*> GetComponents() const;
		
	private:
		const TComponentsEntry* GetComponentsEntry(const CompId& compId) const;
		
		template<typename ComponentType>
		const TComponentsEntry* GetComponentsEntry() const;

    private:
        
        GOID				m_id;
		TComponentListTable	m_componentTable;
    };
	
	template<typename ComponentType>
	ComponentType* GameObject::CreateComponent()
	{
		ComponentType* component = new ComponentType();
		AddComponent(component);
		return component;
	}
	
	template<typename ComponentType>
	void GameObject::DestroyComponent()
	{
		Component* component = RemoveComponent(ComponentType::TypeName());
		if(component)
		{
			delete component;
			component = 0;
		}
	}
	
	template<typename ComponentType>
	ComponentType* GameObject::GetComponent() const
	{
		Component* component = GetComponentsEntry<ComponentType>()->second.front();
		return component->Component::template DirectCast<ComponentType>();
	}
	
	template<typename ComponentType>
	std::vector<ComponentType*> GameObject::GetComponents() const
	{
		TComponentsEntry* componentsEntry = GetComponentsEntry<ComponentType>();
		
		unsigned int componentsCount = componentsEntry->first;
		std::vector<ComponentType*> castedComponentList(componentsCount);
		
		TComponentList& componentList = componentsEntry->second;
		for(const Component* component : componentList)
		{
			castedComponentList.push_back(component->DirectCast<ComponentType>());
		}
		
		return castedComponentList;
	}
	
	template<typename ComponentType>
	const GameObject::TComponentsEntry* GameObject::GetComponentsEntry() const
	{
		return GetComponentsEntry(ComponentType::TypeName());
	}
}

#endif /* defined(__game_object__) */
