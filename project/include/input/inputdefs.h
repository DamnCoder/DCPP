/*
 * inputdefs.h
 *
 *  Created on: 30 de jul. de 2016
 *      Author: jorge
 */

#ifndef INPUT_INPUTDEFS_H_
#define INPUT_INPUTDEFS_H_

#include <SDL2/SDL_keycode.h>

namespace dc
{
	enum EInputDevice
	{
		KEYBOARD,
		MOUSE,
		TOUCH,
		SWIPE,
	};

	// I will the prefix E (instead of T) to keep the naming similar
	typedef SDL_Keycode EKeyCode;

	//typedef int EKeyState;
	enum EKeyState
	{
		NONE = 0,
		PRESS,
		HOLD,
		RELEASE,
	};


}



#endif /* INPUT_INPUTDEFS_H_ */
