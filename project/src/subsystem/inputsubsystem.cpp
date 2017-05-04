/*
 * inputsubsystem.cpp
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#include "subsystem/inputsubsystem.h"

#include "input/inputmanagerfactory.h"
#include "help/deletehelp.h"

#include <SDL2/SDL_events.h>

namespace dc
{
	const bool IsKeyboardEvent(Uint32 inputType)
	{
		return inputType == SDL_KEYDOWN || inputType == SDL_KEYUP;
	}
	
	const bool IsMouseButtonEvent(Uint32 inputType)
	{
		return inputType == SDL_MOUSEBUTTONDOWN
			|| inputType == SDL_MOUSEBUTTONUP;
	}
	
	const bool IsMouseMotionEvent(Uint32 inputType)
	{
		return inputType == SDL_MOUSEMOTION;
	}
	
	const bool IsMouseWheelEvent(Uint32 inputType)
	{
		return inputType == SDL_MOUSEWHEEL;
	}
	
	const bool IsMouseEvent(Uint32 inputType)
	{
		return IsMouseButtonEvent(inputType)
			|| IsMouseMotionEvent(inputType)
			|| IsMouseWheelEvent(inputType);
	}

	CInputSubsystem::CInputSubsystem() :
			IRunnableSubsystem(),
			mp_keyInputManager(0),
			mp_mouseInputManager(0),
			mp_touchInputManager(0),
			mp_swipeInputManager(0)
	{}

	CInputSubsystem::~CInputSubsystem() {}

	void CInputSubsystem::Initialize()
	{
	}

	void CInputSubsystem::Run()
	{
		SDL_Event inputEvent;
		while(SDL_PollEvent(&inputEvent))
		{
			Uint32 inputType = inputEvent.type;
			
			if(IsKeyboardEvent(inputType))
			{
				if(mp_keyInputManager && mp_keyInputManager->HasSignals())
				{
					mp_keyInputManager->CheckEvent(inputEvent);
				}
			}
			else if(IsMouseEvent(inputType))
			{
				if(mp_mouseInputManager && mp_mouseInputManager->HasSignals())
				{
					mp_mouseInputManager->CheckEvent(inputEvent);
				}
			}
		}
	}

	void CInputSubsystem::Terminate()
	{
		SafeDelete(mp_keyInputManager);
		SafeDelete(mp_mouseInputManager);
		
		m_inputManagerList.clear();

		mp_keyInputManager = 0;
		mp_mouseInputManager = 0;
		mp_touchInputManager = 0;
		mp_swipeInputManager = 0;
	}
	
	CKeyInputManager* CInputSubsystem::CreateKeyInputManager()
	{
		if(!mp_keyInputManager)
		{
			mp_keyInputManager = new CKeyInputManager();
			
			m_inputManagerList.push_back(mp_keyInputManager);
		}
		return mp_keyInputManager;
	}
	
	CMouseInputManager* CInputSubsystem::CreateMouseInputManager()
	{
		if(!mp_mouseInputManager)
		{
			mp_mouseInputManager = new CMouseInputManager();
		}
		return mp_mouseInputManager;
	}

} /* namespace dc */
