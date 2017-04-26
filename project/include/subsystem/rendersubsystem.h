//
//  rendersubsystem.hpp
//  DCPPTest
//
//  Created by Jorge López on 1/4/17.
//
//

#ifndef rendersubsystem_h
#define rendersubsystem_h

#include "runnablesubsystem.h"

#include "windowsubsystem.h"
#include "renderer/renderer.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	class CRenderSubsystem : public IRunnableSubsystem
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		RTTI_DECLARATIONS(CRenderSubsystem, IRunnableSubsystem)
		
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
		CRenderer* Renderer() const { return mp_renderer; }
	
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CRenderSubsystem() : mp_renderer(0)
		{}
		
		~CRenderSubsystem()
		{}
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void Initialize()		override;
		void Terminate()		override;
		
		void Run()				override;
		void PrepareUpdate()	override;
		void FinishUpdate()		override;

		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		CRenderer*			mp_renderer;
		
		CWindowSubsystem*	mp_windowSubsystem;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}



#endif /* rendersubsystem_hpp */
