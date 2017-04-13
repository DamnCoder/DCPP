//
//  scenemanagersubsystem.h
//  DCPPTest
//
//  Created by Jorge López on 21/1/17.
//
//

#ifndef scenemanagersubsystem_h
#define scenemanagersubsystem_h

#include "runnablesubsystem.h"

#include "scenes/scenemanager.h"

namespace dc
{
	class CSceneSubsystem : public IRunnableSubsystem
	{
		RTTI_DECLARATIONS(CSceneSubsystem, IRunnableSubsystem)
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
		void Initialize()	override;
		void Run()			override;
		void Terminate()	override;
		
		// ===========================================================
		// Methods
		// ===========================================================
		CScene* CreateScene(const char* name);
		
		void SetCurrentScene(const char* name);
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CSceneManager*	mp_sceneManager;
		
		CScene*			mp_currentScene;

	};
}

#endif /* scenemanagersubsystem_h */
