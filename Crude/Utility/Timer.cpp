#include "Timer.h"

namespace Crude {

	Timer::Timer(long double Tick) : m_StartTime(0), m_TargetTime(Tick) {
	}

	Timer::~Timer() {
	}

	void Timer::Stop() {
		m_StartTime = 0;
	}

	void Timer::Start() {
		m_StartTime = clock();
	}

	bool Timer::Finished() {
		if (m_StartTime == 0) return true;
		if ((m_StartTime + clock()) >= (m_StartTime + m_TargetTime))
			return true;
		return false;
	}

}