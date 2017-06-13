//
//	timesubsystem
//	DCPP
//
//	Created by Jorge López González on 13/06/2017 17:40:03.
//

#ifndef CTIMESUBSYSTEM_H
#define CTIMESUBSYSTEM_H

#include "runnablesubsystem.h"

#include "help/timer.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	/**
	 * \class CTimeSubsystem
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */
class CTimeSubsystem : public IRunnableSubsystem
{
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================
	RTTI_DECLARATIONS(CTimeSubsystem, IRunnableSubsystem)
	
	// ===========================================================
	// Static fields / methods
	// ===========================================================
private:
	
	static CTimer ms_timer;
	
	static const CTimer& Timer()
	{
		return ms_timer;
	}

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Constructors
	// ===========================================================
public:
	CTimeSubsystem()
	{}

	~CTimeSubsystem()
	{}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
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
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* CTIMESUBSYSTEM_H */
