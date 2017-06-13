//
//	timer
//	DCPP
//
//	Created by Jorge López González on 13/06/2017 13:54:30.
//

#include "timer.h"

namespace dc
{
	void CTimer::Start()
	{
		m_globalTime = std::chrono::high_resolution_clock::now();
		m_pause = false;
	}
	
	void CTimer::Finish()
	{
		m_pause = true;
	}
	
	void CTimer::Update()
	{
		if(!m_pause)
		{
			m_dt = TimeSpan<float>(m_previousTime);
			
			if(MaxLatency < m_dt)
			{
				m_dt = ThirtyFPS;
			}
			
			m_dt *= m_timeScale;
			
			m_previousTime = std::chrono::high_resolution_clock::now();
		}
	}
}
