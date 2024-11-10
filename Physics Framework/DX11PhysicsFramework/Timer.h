#pragma once

#ifndef TIMER_H
#define TIMER_H

#include "Constants.h"
#include "Structures.h"
#include <chrono>

using namespace std::chrono;

class Timer
{
private:

	steady_clock::time_point m_StartTime;
	steady_clock::time_point m_LastFrame;

public:

	// CLASS FUNCTION(s)
	Timer();

	~Timer() { };

	// BASE FUNCTION(s)
	float GetDeltaTime();
	void Tick();

};

#endif

