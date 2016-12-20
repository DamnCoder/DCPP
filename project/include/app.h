//
//  App.hpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include "subsystem/subsystemmanager.h"

namespace dc
{
	class CApp
	{
	public:
		void AskForTermination(const bool value) { m_terminationAsked = value; }

		template <typename T>
		T* GetSubsystem();

	public:
		CApp(): m_terminationAsked(false) {}
		virtual ~CApp() {}

	public:
		virtual void Create() = 0;
		virtual void Configure() = 0;
		void Run();

	protected:
		void Add(ISubsystem* subsystem);
		void Add(IRunnableSubsystem* subsystem);

	private:
		void Initialize();
		void Terminate();

	private:
		CSubsystemManager 	m_subsystemManager;
		bool				m_terminationAsked;
	};

	template<typename T>
	inline
	T* CApp::GetSubsystem()
	{
		return m_subsystemManager.GetSubsystem<T>();
	}
}

#endif /* App_hpp */
