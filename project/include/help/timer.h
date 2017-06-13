//
//	timer
//	DCPP
//
//	Created by Jorge López González on 13/06/2017 13:54:30.
//

#ifndef CTIMER_H
#define CTIMER_H

#include <chrono>

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	/**
	 * \class CTimer
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */
class CTimer
{
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================
	
	// ===========================================================
	// Static fields / methods
	// ===========================================================
public:
	constexpr static const float ThirtyFPS = 1.f/30.f;
	constexpr static const float SixtyFPS = 1.f/60.f;
	
	constexpr static const float MaxLatency = 1.f/10.f;
	
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================
public:
	const float DT() const
	{
		return m_dt;
	}
	
	const double ElapsedTimeSinceStartUp() const
	{
		return TimeSpan<double>(m_globalTime);
	}
	
	void Pause(const bool pause)
	{
		m_pause = pause;
	}
	
	const bool Pause() const
	{
		return m_pause;
	}
	
private:
	template<typename T>
	const T TimeSpan(const std::chrono::high_resolution_clock::time_point& time) const;

	// ===========================================================
	// Constructors
	// ===========================================================
public:
	CTimer(): m_timeScale(1.0f), m_dt(0.f), m_pause(true)
	{}

	~CTimer()
	{}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================
public:
	void Start();
	void Finish();
	
	void Update();

	// ===========================================================
	// Fields
	// ===========================================================
	
private:
	std::chrono::high_resolution_clock::time_point	m_globalTime;
	std::chrono::high_resolution_clock::time_point	m_previousTime;
	float											m_timeScale;
	float											m_dt;
	bool											m_pause;
	
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
	template<typename T>
	inline
	const T CTimer::TimeSpan(const std::chrono::high_resolution_clock::time_point& time) const
	{
		std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<T> timeSpan = std::chrono::duration_cast<std::chrono::duration<T>>(currentTime - time);
		return timeSpan.count();
	}
}

#endif /* CTIMER_H */
