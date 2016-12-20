//
//  HFSMSubsystem.hpp
//  dcpp
//
//  Created by Jorge López on 20/4/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef HFSMSubsystem_hpp
#define HFSMSubsystem_hpp

#include "runnablesubsystem.h"

#include "structures/composedstate.h"

namespace dc
{
	class CHFSMSubsystem: public IRunnableSubsystem
	{
	public:
		static const int ROOT_STATE = 0;

	public:
		const std::type_info& Type() const override { return typeid(CHFSMSubsystem); }

		void SetInitState(const int initState)
		{
			m_initState = initState;
		}

	public:
		CHFSMSubsystem(): IRunnableSubsystem(), mp_rootState(0), m_initState(-1)
		{
		}

		//CHFSMAppSubsystem(const CHFSMAppSubsystem& app) = delete;

		virtual ~CHFSMSubsystem()
		{
		}

	public:
		void Initialize() override;
		void Run () override;
		void Terminate() override;

	public:
		virtual void CreateStates() = 0;

		void CreateHFSM();
		void DestroyHFSM();
		void InitHFSM();

	private:
		CComposedState* mp_rootState;
		int m_initState;
	};
}

#endif /* HFSMSubsystem_hpp */
