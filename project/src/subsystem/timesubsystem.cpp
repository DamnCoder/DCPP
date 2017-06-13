//
//	timesubsystem
//	DCPP
//
//	Created by Jorge López González on 13/06/2017 17:40:03.
//

#include "timesubsystem.h"

#include <stdio.h>

namespace dc
{
	CTimer CTimeSubsystem::ms_timer;
	
	void CTimeSubsystem::Initialize()
	{
		ms_timer.Start();
	}
	
	void CTimeSubsystem::Terminate()
	{
		ms_timer.Finish();
	}
	
	void CTimeSubsystem::Run()
	{
	}
	
	void CTimeSubsystem::PrepareUpdate()
	{
		ms_timer.Update();
		//printf("Total time: %f DT %f\n", ms_timer.ElapsedTimeSinceStartUp(), ms_timer.DT());
	}
	
	void CTimeSubsystem::FinishUpdate()
	{
		
	}

}
