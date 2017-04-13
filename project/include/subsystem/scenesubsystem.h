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

#include "rendersubsystem.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	class CSceneSubsystem : public IRunnableSubsystem
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		RTTI_DECLARATIONS(CSceneSubsystem, IRunnableSubsystem)
		
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
		CSceneManager* SceneManager() const { return mp_sceneManager; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CSceneSubsystem():
			mp_sceneManager(0),
			mp_currentScene(0),
			mp_renderSubsystem(0)
		{}
		
		CSceneSubsystem (const CSceneSubsystem& copy) = delete;
		
		virtual ~CSceneSubsystem() {}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void Initialize()	override;
		void Terminate()	override;
		
		void Run()			override;
		
	protected:
		void PrepareUpdate();
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		CScene* CreateScene(const char* name);
		
		void SetCurrentScene(const char* name);
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CSceneManager*		mp_sceneManager;
		
		CScene*				mp_currentScene;
		
		CRenderSubsystem*	mp_renderSubsystem;

	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* scenemanagersubsystem_h */
