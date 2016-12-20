/*
 * inputsubsystem.cpp
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#include "subsystem/inputsubsystem.h"

#include "input/inputmanagerfactory.h"
#include "help/deletehelp.h"

namespace dc
{

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
		for(CKeyInputManager* inputManager : m_inputManagerList)
		{
			inputManager->Run();
		}
	}

	void CInputSubsystem::Terminate()
	{
		for(CKeyInputManager* inputManager : m_inputManagerList)
		{
			inputManager->Terminate();
			SafeDelete(inputManager);
		}
		m_inputManagerList.clear();

		mp_keyInputManager = 0;
		mp_mouseInputManager = 0;
		mp_touchInputManager = 0;
		mp_swipeInputManager = 0;
	}

	void CInputSubsystem::Register(const EKeyState keyState, const TAction& action)
	{
		if(!mp_keyInputManager)
		{
			mp_keyInputManager = CInputManagerFactory::CreateKeyInputManager(EInputType::SDL);
			mp_keyInputManager->Initialize();

			m_inputManagerList.push_back(mp_keyInputManager);
		}

		mp_keyInputManager->RegisterEvent(keyState, action);
	}

} /* namespace dc */
