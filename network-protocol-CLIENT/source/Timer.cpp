#include "stdafx.h"
#include "Timer.h"
#include "types.h"
#include <iostream>

Timer::Timer()
{
	deltaTimeCurrent = 0.0f;
	deltaTimeMax = 0.0f;
}

Timer::~Timer()
{
}

bool Timer::WhileDuration(uint8_t p_millisecondsToLoop, std::function<void()> p_callback) {
	int64_t waitTime = p_millisecondsToLoop + network::get_ticks();
	while (network::get_ticks() < waitTime) {
		p_callback();
	}
	return true;
}
bool Timer::WaitForSeconds(int64_t p_millisecondsToWait) {
	int64_t waitTime = p_millisecondsToWait + network::get_ticks();
	while (network::get_ticks() < waitTime) {
	}
	return true;
}

bool Timer::UpdateTimer(float p_delta, float p_max)
{
	deltaTimeCurrent += p_delta;
	if (deltaTimeCurrent >= p_max) {
		deltaTimeCurrent -= p_max;
		return true;
	}
	return false;
}

float Timer::UpdateTimer1(float p_delta, float p_max)
{

	if (deltaTimeCurrent < p_max)
	{
		deltaTimeCurrent += p_delta;
	}
	else
	{
		deltaTimeCurrent = 1;
	}
	return  deltaTimeCurrent;
}

void Timer::resetTimer()
{
	deltaTimeCurrent = 0;
}