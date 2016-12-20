/*
 * IInputManager.h
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#ifndef INPUT_KEYINPUTMANAGER_H_
#define INPUT_KEYINPUTMANAGER_H_

#include <unordered_map>
#include <forward_list>

#include "inputdefs.h"
#include "help/callbacks.h"

namespace dc
{
	class CKeyInputManager
	{
	// ===========================================================
	// Constant / Static fields / Enums / Typedefs
	// ===========================================================
	protected:
		// I have decided to use a forward_list because I'm afraid of the cost of the deletion operations
		// With this type of list we have an overhead on memory because of the links, but maybe
		// is not that bad
		typedef std::forward_list<TActionFunctor>				TActionList;
		typedef std::unordered_map<EKeyCode, TActionList> 		TCodeActionMap;

		typedef std::unordered_map<EKeyState, TActionList, std::hash<int>> 		TStateActionMap;
		typedef std::unordered_map<EKeyState, TCodeActionMap, std::hash<int>>	TStateCodeActionMap;

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Constructors
	// ===========================================================
	public:
		CKeyInputManager(){}
		virtual ~CKeyInputManager(){}

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================
	public:
		virtual void Initialize() = 0;
		virtual void Run() = 0;
		virtual void Terminate() = 0;

		void RegisterEvent(const EKeyState keyState, const TAction& action);
		void DeregisterEvent(const EKeyState keyState, const TAction& action);

		void RegisterEvent(const EKeyState keyState, const EKeyCode keyCode, const TAction& action);
		void DeregisterEvent(const EKeyState keyState, const EKeyCode keyCode, const TAction& action);

	protected:
		inline void DispatchActions(const EKeyState keyState);
		inline void DispatchActions(const EKeyState keyState, const EKeyCode keyCode);

	private:
		const TActionList FindActionList(const EKeyState keyState) const;
		const TActionList FindActionList(const EKeyState keyState, const EKeyCode keyCode) const;

		void RemoveAction(TActionList& actionList, const TAction& action);

	// ===========================================================
	// Fields
	// ===========================================================
	protected:

		TStateActionMap 	m_stateActionsMap;
		TStateCodeActionMap	m_stateCodeActionsMap;
	};

	inline
	void CKeyInputManager::DispatchActions(const EKeyState keyState)
	{
		TActionList actionList = m_stateActionsMap[keyState];
		for(TActionFunctor action : actionList)
		{
			action();
		}
	}

	inline
	void CKeyInputManager::DispatchActions(const EKeyState keyState, const EKeyCode keyCode)
	{
		// State only actions
		DispatchActions(keyState);

		// Key code actions
		TActionList actionList = FindActionList(keyState, keyCode);
		for(TAction action : actionList)
		{
			action();
		}
	}
}



#endif /* INPUT_KEYINPUTMANAGER_H_ */
