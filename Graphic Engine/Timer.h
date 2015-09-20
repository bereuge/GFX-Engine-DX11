#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer();

	bool Initialize();
	void Run();

	double GetTime();
	float GetFrameTime();

private:
	LARGE_INTEGER frequency;
	double ticksPerSecond;
	LARGE_INTEGER startTime;
	double frameTime;
	INT64 frameTimeOld;
};