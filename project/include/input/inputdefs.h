/*
 * inputdefs.h
 *
 *  Created on: 30 de jul. de 2016
 *      Author: jorge
 */

#ifndef INPUT_INPUTDEFS_H_
#define INPUT_INPUTDEFS_H_

#include <SDL2/SDL_events.h>

namespace dc
{
	enum EInputDevice
	{
		KEYBOARD,
		MOUSE,
		TOUCH,
		SWIPE,
	};

	// I will use the prefix E (instead of T) to keep the appearance that we are using enumerates
	typedef Uint32		EInputEvent;
	typedef SDL_Keycode	EKeyCode;

	//typedef Uint32		EKeyState;
	
	//typedef int EKeyState;

	enum EKeyState
	{
		NONE = 0,
		PRESS,
		HOLD,
		RELEASE,
	};
	/*
	enum EKeyCode
	{
		NONE = 0,
	};
	*/
	
	struct TKeyEvent
	{
		EKeyState	state;
		Uint32		keyCode;
		Uint16		keyModifier;
	};
}

#endif /* INPUT_INPUTDEFS_H_ */
