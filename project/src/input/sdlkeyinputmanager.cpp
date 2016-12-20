/*
 * sdlinputmanager.cpp
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#include "input/sdlkeyinputmanager.h"

#include <SDL2/SDL.h>
#include <cstdio>

namespace dc
{

	void CSDLKeyInputManager::Initialize()
	{
	}

	void CSDLKeyInputManager::Run()
	{
		SDL_Event inputEvent;
		while(SDL_PollEvent(&inputEvent))
		{
			switch(inputEvent.type)
			{
			case SDL_KEYDOWN:
				if (m_keyState == EKeyState::NONE)
				{
					printf("PRESS\n");
					m_keyState = EKeyState::PRESS;
					DispatchActions(m_keyState);
					DispatchActions(m_keyState, inputEvent.key.keysym.sym);
				}
				else
				{
					printf("HOLD\n");
					m_keyState = EKeyState::HOLD;
					DispatchActions(m_keyState);
					DispatchActions(m_keyState, inputEvent.key.keysym.sym);
				}

				break;

			case SDL_KEYUP:
				printf("RELEASE\n");
				m_keyState = EKeyState::RELEASE;
				DispatchActions(m_keyState);
				DispatchActions(m_keyState, inputEvent.key.keysym.sym);
				m_keyState = EKeyState::NONE;
				break;
			}
		}
	}

	void CSDLKeyInputManager::Terminate()
	{
	}
} /* namespace dc */
