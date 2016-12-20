/*
 * sdlinputmanager.h
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#ifndef INPUT_SDLKEYINPUTMANAGER_H_
#define INPUT_SDLKEYINPUTMANAGER_H_

#include <input/keyinputmanager.h>

namespace dc
{

class CSDLKeyInputManager : public CKeyInputManager
{
public:
	CSDLKeyInputManager():m_keyState(EKeyState::NONE){}
	~CSDLKeyInputManager(){}

public:
	void Initialize() override;
	void Run() override;
	void Terminate() override;

private:
	EKeyState m_keyState;
};

} /* namespace dc */

#endif /* INPUT_SDLKEYINPUTMANAGER_H_ */
