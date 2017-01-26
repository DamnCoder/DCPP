/*
 * IInputManager.h
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#ifndef INPUT_KEYINPUTMANAGER_H_
#define INPUT_KEYINPUTMANAGER_H_

#include <map>
#include <SDL2/SDL_events.h>

#include "inputdefs.h"
#include "signals/signal.h"
#include "help/callbacks.h"

namespace dc
{
	using TKeySignal = CSignal<void(void)>;
	
	class CKeyInputManager
	{
		// ===========================================================
		// Constant / Static fields / Enums / Typedefs
		// ===========================================================
	protected:
		using TCodeSignalMap = std::map<EKeyCode, TKeySignal*>;
		using TStateCodeSignalMap = std::map<EKeyState, TCodeSignalMap>;

		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================

		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const bool HasSignals() const
		{
			return m_state2CodeMap.size();
		}
		
		// Looks for a signal associated to the key state if it doesn't find it creates one and returns it
		TKeySignal* GetSignal(const EKeyState keyState);
		TKeySignal* GetSignal(const EKeyState keyState, const EKeyCode keyCode);
		

		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CKeyInputManager(): m_keyState(EKeyState::NONE){}
		virtual ~CKeyInputManager(){}

		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void CheckEvent(const SDL_Event& keyEvent);

		void Register(const EKeyState keyState, const TAction& action);
		void Register(const EKeyState keyState, const EKeyCode keyCode, const TAction& action);
		
		void Deregister(const EKeyState keyState, const TAction& action);
		void Deregister(const EKeyState keyState, const EKeyCode keyCode, const TAction& action);

	protected:
		const EKeyState UpdateKeyState(const Uint8 state, const EKeyState previousState);
		
		void CheckKeyState(const EKeyState keyState, const SDL_KeyboardEvent& keyEvent);
		
		void CheckKeyCode(const TCodeSignalMap& code2signalMap, const SDL_KeyboardEvent& keyEvent);

		// ===========================================================
		// Fields
		// ===========================================================
	protected:
		EKeyState			m_keyState;
		TStateCodeSignalMap	m_state2CodeMap;
	};
}



#endif /* INPUT_KEYINPUTMANAGER_H_ */
