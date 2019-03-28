#pragma once
#include "Protocol.h"
#include <functional>

class Timer
{
public:
	Timer();
	~Timer();
	bool UpdateTimer(float p_delta, float p_max);
	float UpdateTimer1(float p_delta, float p_max);
	bool WaitForSeconds(int64_t p_millisecondsToWait); //wait for networkticks.
	bool WhileDuration(uint8_t p_millisecondsToLoop, std::function<void()> p_callback);
	void resetTimer();
private:
	float deltaTimeCurrent;
	float deltaTimeMax;

};