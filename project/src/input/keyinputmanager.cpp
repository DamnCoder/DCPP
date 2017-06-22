/*
 * inputmanager.cpp
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#include "input/keyinputmanager.h"
#include "deletehelp.h"
#include <algorithm>

namespace dc
{
	/* Print modifier info */
	void PrintModifiers(const Uint16 mod)
	{
		printf( "Modifers: " );
		
		/* If there are none then say so and return */
		if( mod == KMOD_NONE )
		{
			printf( "None\n" );
			return;
		}
		
		/* Check for the presence of each SDLMod value */
		/* This looks messy, but there really isn't    */
		/* a clearer way.                              */
		if( mod & KMOD_NUM ) printf( "NUMLOCK " );
		if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
		if( mod & KMOD_LCTRL ) printf( "LCTRL " );
		if( mod & KMOD_RCTRL ) printf( "RCTRL " );
		if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
		if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
		if( mod & KMOD_RALT ) printf( "RALT " );
		if( mod & KMOD_LALT ) printf( "LALT " );
		if( mod & KMOD_CTRL ) printf( "CTRL " );
		if( mod & KMOD_SHIFT ) printf( "SHIFT " );
		if( mod & KMOD_ALT ) printf( "ALT " );
		printf( "\n" );
	}
	
	void PrintKeyInfo(const SDL_KeyboardEvent& key)
	{
		SDL_Scancode scanCode = key.keysym.scancode;
		SDL_Keycode keyCode = key.keysym.sym;
		const char* keyName = SDL_GetKeyName( keyCode );
		printf("Scancode: 0x%02X, Name: %s %u\n", scanCode, keyName, keyCode);
		
		PrintModifiers(key.keysym.mod);
	}
	
	void CKeyInputManager::CheckEvent(const SDL_Event& event)
	{
		const SDL_KeyboardEvent& keyEvent = event.key;
		
		PrintKeyInfo(keyEvent);
		
		m_keyState = UpdateKeyState(keyEvent.state, m_keyState);
		CheckKeyState(m_keyState, keyEvent);
	}
	
	TKeySignal* CKeyInputManager::GetSignal(const EKeyState keyState)
	{
		return GetSignal(keyState, SDLK_UNKNOWN);
	}
	
	TKeySignal* CKeyInputManager::GetSignal(const EKeyState keyState, const EKeyCode keyCode)
	{
		TStateCodeSignalMap::iterator itState = m_state2CodeMap.find(keyState);
		TKeySignal* signal = 0;
		
		if(itState != m_state2CodeMap.end())
		{
			TCodeSignalMap* code2SignalMap = &itState->second;
			TCodeSignalMap::iterator itCodeSignal = code2SignalMap->find(keyCode);
			
			if(itCodeSignal != code2SignalMap->end())
			{
				signal = itCodeSignal->second;
			}
			else
			{
				signal = new TKeySignal();
				code2SignalMap->insert(std::make_pair(keyCode, signal));
			}
		}
		else
		{
			signal = new TKeySignal();
			m_state2CodeMap[keyState][keyCode] = signal;
		}
		return signal;
	}
	
	void CKeyInputManager::Register(const EKeyState keyState, const TAction& event)
	{
		GetSignal(keyState)->Connect(event);
	}
	
	void CKeyInputManager::Register(const EKeyState keyState, const EKeyCode keyCode, const TAction& event)
	{
		GetSignal(keyState, keyCode)->Connect(event);
	}

	void CKeyInputManager::Deregister(const EKeyState keyState, const TAction& action)
	{
		Deregister(keyState, SDLK_UNKNOWN, action);
	}
	
	void CKeyInputManager::Deregister(const EKeyState keyState, const EKeyCode keyCode, const TAction& action)
	{
		TStateCodeSignalMap::iterator itState2Code = m_state2CodeMap.find(keyState);

		if(itState2Code != m_state2CodeMap.end())
		{
			TCodeSignalMap* code2SignalMap = &itState2Code->second;
			TCodeSignalMap::iterator itCode2Signal = code2SignalMap->find(keyCode);
			
			if(itCode2Signal != code2SignalMap->end())
			{
				TKeySignal* signal = itCode2Signal->second;
				signal->Disconnect(action);
				
				if(signal->IsEmpty())
				{
					code2SignalMap->erase(keyCode);
					
					delete signal;
					itCode2Signal->second = signal = 0;
				}
				
				if(0 < code2SignalMap->size())
				{
					m_state2CodeMap.erase(itState2Code);
				}
			}
		}
	}
	
	const EKeyState CKeyInputManager::UpdateKeyState(const Uint8 state, const EKeyState previousState)
	{
		/*
		if(previousState == EKeyState::RELEASE && state == SDL_RELEASED)
		{
			printf("NONE\n");
			return EKeyState::NONE;
		}
		*/
		if(state == SDL_PRESSED)
		{
			if (previousState == EKeyState::NONE || previousState == EKeyState::RELEASE)
			{
				printf("PRESS\n");
				return EKeyState::PRESS;
			}
			else if(previousState == EKeyState::PRESS || previousState == EKeyState::HOLD)
			{
				printf("HOLD\n");
				return EKeyState::HOLD;
			}
		}
		else if(state == SDL_RELEASED)
		{
			printf("RELEASE\n");
			return EKeyState::RELEASE;
		}
		
		printf("NONE\n");
		return EKeyState::NONE;
	}

	void CKeyInputManager::CheckKeyState(const EKeyState keyState, const SDL_KeyboardEvent& keyEvent)
	{
		for(const auto& stateEntry : m_state2CodeMap)
		{
			if(stateEntry.first == keyState)
			{
				CheckKeyCode(stateEntry.second, keyEvent);
			}
		}
	}

	void CKeyInputManager::CheckKeyCode(const TCodeSignalMap& code2signalMap, const SDL_KeyboardEvent& keyEvent)
	{
		for(const auto& codeEntry : code2signalMap)
		{
			if(codeEntry.first == SDLK_UNKNOWN || codeEntry.first == keyEvent.keysym.sym)
			{
				TKeySignal& signal = *codeEntry.second;
				signal();
				
			}
		}
	}
}
