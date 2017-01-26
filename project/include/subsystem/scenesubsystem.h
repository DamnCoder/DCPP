//
//  scenemanagersubsystem.h
//  DCPPTest
//
//  Created by Jorge López on 21/1/17.
//
//

#ifndef scenemanagersubsystem_h
#define scenemanagersubsystem_h

#include "subsystem.h"

#include "scenes/scenemanager.h"

namespace dc
{
	class CSceneSubsystem : public ISubsystem
	{
		RTTI_DECLARATIONS(CSceneSubsystem, ISubsystem)
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Constant / Enums / Typedefs
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		CSceneManager* SceneManager() const { return mp_sceneManager; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CSceneSubsystem() {}
		CSceneSubsystem (const CSceneSubsystem& copy) = delete;
		
		virtual ~CSceneSubsystem() {}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void Initialize() override;
		
		void Terminate() override;
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CSceneManager* mp_sceneManager;

	};
}

#endif /* scenemanagersubsystem_h */
