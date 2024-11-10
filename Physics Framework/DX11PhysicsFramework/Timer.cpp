#include "Timer.h"

Timer::Timer()
{
	// m_StartTime = GetTickCount64();
	m_LastFrame = steady_clock::now();
}

float Timer::GetDeltaTime() // Delta Time
{
	return duration<float>(steady_clock::now() - m_LastFrame).count();
}

void Timer::Tick()
{
	m_LastFrame = steady_clock::now(); // Set the Last frame to the current frame
}
