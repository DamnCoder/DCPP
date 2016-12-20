/*
 * inputmanager.cpp
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#include "input/keyinputmanager.h"
#include <algorithm>

namespace dc
{
	void CKeyInputManager::RegisterEvent(const EKeyState keyState, const TAction& action)
	{
		m_stateActionsMap[keyState].push_front(TActionFunctor(action));
	}

	void CKeyInputManager::DeregisterEvent(const EKeyState keyState, const TAction& action)
	{
		TActionList actionList = FindActionList(keyState);
		RemoveAction(actionList, action);
	}

	void CKeyInputManager::RegisterEvent(const EKeyState keyState, const EKeyCode keyCode, const TAction& action)
	{
		m_stateCodeActionsMap[keyState][keyCode].push_front(TActionFunctor(action));
	}

	void CKeyInputManager::DeregisterEvent(const EKeyState keyState, const EKeyCode keyCode, const TAction& action)
	{
		TActionList actionList = FindActionList(keyState, keyCode);
		RemoveAction(actionList, action);
	}

	const CKeyInputManager::TActionList CKeyInputManager::FindActionList(const EKeyState keyState) const
	{
		TStateActionMap::const_iterator it = m_stateActionsMap.find(keyState);

		if (it != m_stateActionsMap.end())
		{
			return it->second;
		}
		return TActionList();
	}

	const CKeyInputManager::TActionList CKeyInputManager::FindActionList(const EKeyState keyState, const EKeyCode keyCode) const
	{
		TStateCodeActionMap::const_iterator stateCodeActionIt = m_stateCodeActionsMap.find(keyState);
		if(stateCodeActionIt != m_stateCodeActionsMap.end())
		{
			TCodeActionMap codeActionMap = stateCodeActionIt->second;
			TCodeActionMap::iterator codeActionIt = codeActionMap.find(keyCode);
			if(codeActionIt != codeActionMap.end())
			{
				return codeActionIt->second;
			}
		}
		return TActionList();
	}

	void CKeyInputManager::RemoveAction(TActionList& actionList, const TAction& action)
	{
		const TActionList::iterator& end = actionList.end();
		TActionList::iterator it = std::find(actionList.begin(), end, action);

		if (it != end)
		{
			// Considering that deletion of callbacks is supposed to be made
			// in state changes maybe the drawback is not that bad
			actionList.remove(*it);
		}
	}
}
