/*
 * mouseinputmanager.cpp
 *
 *  Created on: 31 de jul. de 2016
 *      Author: jorge
 */

#include "input/mouseinputmanager.h"

namespace dc
{
	extern const bool IsMouseButtonEvent(Uint32 inputType);
	extern const bool IsMouseMotionEvent(Uint32 inputType);
	extern const bool IsMouseWheelEvent(Uint32 inputType);
	
	TMouseSignal& CMouseInputManager::GetSignal(const EMouseEvent event)
	{
		return m_eventMap[event];
	}
	
	void CMouseInputManager::CheckEvent(const SDL_Event& event)
	{
		for (auto& mouseEventEntry : m_eventMap)
		{
			const EMouseEvent mouseEvent = mouseEventEntry.first;
			if(mouseEvent == event.type)
			{
				TMouseSignal& signal = mouseEventEntry.second;
				if(IsMouseButtonEvent(event.type))
				{
					signal(Adapt(event.button));
				}
				else if(IsMouseMotionEvent(event.type))
				{
					signal(Adapt(event.motion));
				}
				else
				{
					signal(Adapt(event.wheel));
				}
			}
		}
	}
	
	const TMouseEvent CMouseInputManager::Adapt(const SDL_MouseButtonEvent& buttonEvent)
	{
		m_keyState = UpdateKeyState(buttonEvent.state, m_keyState);
		return TMouseEvent(m_keyState, buttonEvent.button, buttonEvent.clicks, buttonEvent.x, buttonEvent.y);
	}
	
	const TMouseEvent CMouseInputManager::Adapt(const SDL_MouseMotionEvent& motionEvent)
	{
		m_keyState = UpdateKeyState(motionEvent.state, m_keyState);
		return TMouseEvent(m_keyState, motionEvent.x, motionEvent.y, motionEvent.xrel, motionEvent.yrel);
	}
	
	const TMouseEvent CMouseInputManager::Adapt(const SDL_MouseWheelEvent& wheelEvent)
	{
		m_keyState = EKeyState::NONE;
		return TMouseEvent(wheelEvent.x, wheelEvent.y);
	}
	
	const EKeyState CMouseInputManager::UpdateKeyState(const Uint8 state, const EKeyState previousState)
	{
		if(previousState == EKeyState::RELEASE && state == SDL_RELEASED)
		{
			return EKeyState::NONE;
		}
		
		if(state == SDL_PRESSED)
		{
			if (previousState == EKeyState::NONE)
			{
				//printf("PRESS\n");
				return EKeyState::PRESS;
			}
			else if(previousState == EKeyState::PRESS || previousState == EKeyState::HOLD)
			{
				//printf("HOLD\n");
				return EKeyState::HOLD;
			}
		}
		else if(state == SDL_RELEASED && (previousState == EKeyState::PRESS || previousState == EKeyState::HOLD))
		{
			//printf("RELEASE\n");
			return EKeyState::RELEASE;
		}
		
		return EKeyState::NONE;
	}
} /* namespace dc */
