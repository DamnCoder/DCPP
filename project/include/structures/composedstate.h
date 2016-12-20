/*
 * ComposedState.h
 *
 *  Created on: 06/04/2011
 *      Author: jorge
 */

#ifndef COMPOSEDSTATE_H_
#define COMPOSEDSTATE_H_

#include <stack>
#include <unordered_map>
#include <cassert>
#include "state.h"

namespace dc
{
	// Type definitions
	typedef std::unordered_map<int, CState*> TStatesMap;
	typedef std::stack<CState*> TStateStack;

	class CComposedState: public CState
	{
	public:

		const bool Exists(const CState* state) const
		{
			TStatesMap::const_iterator it = m_statesMap.find(state->Id());
			return it != m_statesMap.end();
		}

		CState* Find(const int identifier) const
		{
			TStatesMap::const_iterator it = m_statesMap.find(identifier);
			if (it != m_statesMap.end())
			{
				return it->second;
			}
			return 0;
		}

	private:

		const bool IsNextStateReady() const
		{
			return mp_nextState != 0 && mp_currentState != mp_nextState;
		}

	public:

		CComposedState(const int identifier) :
				CState(identifier), mp_currentState(0), mp_nextState(0)
		{
		}

		virtual ~CComposedState()
		{
		}

		CComposedState(const CComposedState& copy) = delete;

	public:

		virtual void OnActivate() override
		{
			if (mp_currentState)
			{
				mp_currentState->OnActivate();
			}
		}

		virtual void OnDeactivate() override
		{
			if (mp_currentState)
			{
				mp_currentState->OnDeactivate();
			}
		}

		virtual void OnDestroy() override
		{
			DestroyAllStates();
		}

		virtual void OnTick() override
		{
			if (IsNextStateReady())
			{
				SetNextState();
			}

			if (mp_currentState)
			{
				mp_currentState->OnTick();
			}
		}

	public:
		CState* Add(CState* state)
		{
			if (!state) return 0;

			if (!Exists(state))
			{
				m_statesMap[state->Id()] = state;
				state->OnCreate();
			}

			return state;
		}

		const bool Set(const int identifier)
		{
			mp_nextState = Find(identifier);

			return mp_nextState != 0;
		}

	private:

		void SetPreviousState()
		{
			if (m_previousStates.size() == 0) return;

			mp_nextState = m_previousStates.top();
			m_previousStates.pop();
		}

		void SetNextState()
		{
			if (mp_currentState)
			{
				mp_currentState->OnDeactivate();

				m_previousStates.push(mp_currentState);
			}

			mp_currentState = mp_nextState;
			mp_currentState->OnActivate();
		}

		void DestroyAllStates()
		{
			TStatesMap::iterator it(m_statesMap.begin()), end(m_statesMap.end());

			for (; it != end; ++it)
			{
				CState* state = it->second;
				state->OnDestroy();

				m_statesMap.erase(it);

				delete state;
				state = 0;
			}

			m_statesMap.clear();
			mp_currentState = mp_nextState = 0;
		}

	private:
		TStatesMap m_statesMap;
		TStateStack m_previousStates;

		CState* mp_currentState;
		CState* mp_nextState;
	};
}

#endif /* COMPOSEDSTATE_H_ */
