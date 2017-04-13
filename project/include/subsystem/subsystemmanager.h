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
		RTTI_DECLARATIONS(CSubsystemManager, IRunnableSubsystem)
	public:
		template <typename T>
		T* GetSubsystem();
		
		template <typename T, typename... Args>
		void AddSubsystem(Args&&... args);

	public:
		CSubsystemManager() {}
		~CSubsystemManager() {}

	public:
		void Initialize()	override;
		void Terminate()	override;
		
		void Run()			override;
		
	protected:
		void PrepareUpdate();
		void Update();
		void FinishUpdate();

	public:
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
		const auto identifier = T::TypeIdClass();
		for (ISubsystem* subsystem : m_subsystemList)
		{
			//printf("Type searched %s Type looked %s\n", identifier.name(), typeid(subsystem).name());
			//T* castedSubsystem = static_cast<T*>(subsystem);
			//printf("Type searched %s Type looked %s\n", T::TypeName(), subsystem->InstanceName());
			//printf("static id: %zu, instance id: %zu\n", T::TypeIdClass(), subsystem->TypeIdInstance());
			
			if(subsystem->Is(identifier))
			{
				return subsystem->DirectCast<T>();
			}
		}
		return 0;
	}
	
	template <typename T, typename... Args>
	inline
	void CSubsystemManager::AddSubsystem(Args&&... args)
	{
		T* newSubsystem = new T(std::forward<Args>(args)...);
		Add(newSubsystem);
	}
}

#endif /* CSubsystemManager_h */
