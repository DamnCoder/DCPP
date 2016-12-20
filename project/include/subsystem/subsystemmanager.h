//
//  CSubsystemManager.h
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef CSubsystemManager_h
#define CSubsystemManager_h

#include <unordered_map>
#include <vector>

#include "runnablesubsystem.h"

namespace dc
{
	class CSubsystemManager : public IRunnableSubsystem
	{
	public:
		template <typename T>
		T* GetSubsystem();

	public:
		CSubsystemManager(): IRunnableSubsystem() {}
		~CSubsystemManager() {}

	public:
		void Initialize() override;
		void Terminate() override;
		void Run() override;

		void Add(ISubsystem* subsystem);
		void Add(IRunnableSubsystem* runnableSubsystem);

	private:
		ISubsystem* Find(const int subsystemID) const;

	private:
		typedef std::vector<IRunnableSubsystem*> 			TRunnableSubsystemList;
		typedef std::vector<ISubsystem*> 					TSubsystemList;
		typedef std::unordered_map<const int, ISubsystem*> 	TSubsystemMap;

		TSubsystemList 			m_subsystemList;
		TRunnableSubsystemList	m_runnableSubsystemList;
	};

	template <typename T>
	inline
	T* CSubsystemManager::GetSubsystem()
	{
		for (ISubsystem* subsystem : m_subsystemList)
		{
			//printf("Type searched %s Type looked %s\n", typeid(T).name(), typeid(subsystem).name());
			//T* castedSubsystem = static_cast<T*>(subsystem);
			printf("Type searched %s Type looked %s\n", typeid(T).name(), subsystem->Type().name());
			if(subsystem->Type() == typeid(T))
			{
				printf("FOUND!\n");
				return static_cast<T*>(subsystem);
			}
		}
		return 0;
	}
}

#endif /* CSubsystemManager_h */
