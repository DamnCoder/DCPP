/*
 * inputsubsystem.h
 *
 *  Created on: 29 de may. de 2016
 *      Author: jorge
 */

#ifndef SUBSYSTEM_INPUTSUBSYSTEM_H_
#define SUBSYSTEM_INPUTSUBSYSTEM_H_

#include <vector>

#include "runnablesubsystem.h"
#include "input/keyinputmanager.h"
#include "input/mouseinputmanager.h"

namespace dc
{
	class CInputSubsystem : public IRunnableSubsystem
	{
		RTTI_DECLARATIONS(CInputSubsystem, IRunnableSubsystem)
		
	public:
		CKeyInputManager* KeyInputManager() const { return mp_keyInputManager; }
		
	public:
		CInputSubsystem();
		virtual ~CInputSubsystem();

	public:

	public:
		void Initialize()		override;
		void Terminate()		override;
		
		void Run()				override;
		void PrepareUpdate()	override {}
		void FinishUpdate()		override {}

	public:
		CKeyInputManager* CreateKeyInputManager();
		CMouseInputManager* CreateMouseInputManager();

	private:
		std::vector<CKeyInputManager*> m_inputManagerList;

		// I have the four pointers so I can check its existence when I try to register
		// an event. It would be cool not to have them so if there were the need to add
		// a new one, with creating it and adding it would be enough. But here are some
		// thoughts...
		// - How to check fast its existence?
		// - How to iterate fast through the list?
		CKeyInputManager*	mp_keyInputManager;
		CMouseInputManager*	mp_mouseInputManager;
		
		CKeyInputManager* mp_touchInputManager;
		CKeyInputManager* mp_swipeInputManager;

	};

} /* namespace dc */

#endif /* SUBSYSTEM_INPUTSUBSYSTEM_H_ */
