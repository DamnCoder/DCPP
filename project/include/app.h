//
//  App.hpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include "structures/singleton.h"
#include "subsystem/subsystemmanager.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	class CApp : public CSingleton<CApp>
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		friend class CSingleton<CApp>;
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		void AskForTermination(const bool value) { m_terminationAsked = value; }

		template <typename T>
		T* GetSubsystem();

		// ===========================================================
		// Constructors
		// ===========================================================
	protected:
		CApp(): m_terminationAsked(false) {}
		virtual ~CApp() {}

		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		virtual void Create() = 0;
		virtual void Configure() = 0;
		
	protected:
		virtual void Initialize();
		virtual void Terminate();
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Run();

	protected:
		void Add(ISubsystem* subsystem);
		void Add(IRunnableSubsystem* subsystem);
		
	private:
		void RunSubsystems();

		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CSubsystemManager 	m_subsystemManager;
		bool				m_terminationAsked;
	};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
	template<typename T>
	inline
	T* CApp::GetSubsystem()
	{
		return m_subsystemManager.GetSubsystem<T>();
	}
}

#endif /* App_hpp */
