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

namespace dc
{
	class CInputSubsystem : public IRunnableSubsystem
	{
	public:
		const std::type_info& Type() const override { return typeid(CInputSubsystem); }

	public:
		CInputSubsystem();
		virtual ~CInputSubsystem();

	public:

	public:
		void Initialize() override;
		void Run() override;
		void Terminate() override;

	public:
		void Register(const EKeyState keyState, const TAction& action);
		void Deregister(const EKeyState keyState, const TAction& action);

	private:
		std::vector<CKeyInputManager*> m_inputManagerList;

		// I have the four pointers so I can check its existence when I try to register
		// an event. It would be cool not to have them so if there were the need to add
		// a new one, with creating it and adding it would be enough. But here are some
		// thoughts...
		// - How to check fast its existence?
		// - How to iterate fast through the list?
		CKeyInputManager* mp_keyInputManager;
		CKeyInputManager* mp_mouseInputManager;
		CKeyInputManager* mp_touchInputManager;
		CKeyInputManager* mp_swipeInputManager;

	};

} /* namespace dc */

#endif /* SUBSYSTEM_INPUTSUBSYSTEM_H_ */
