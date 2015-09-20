#include "Timer.h"

Timer::Timer() { }

bool Timer::Initialize()
{
	QueryPerformanceFrequency(&frequency);
	if (frequency.QuadPart == 0)
	{
		return false;
	}

	ticksPerSecond = (double)(frequency.QuadPart);

	QueryPerformanceCounter(&startTime);

	return true;
}

void Timer::Run()
{
	/*INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - startTime);

	frameTime = timeDifference / ticksPerMs;

	startTime = currentTime;*/
}

double Timer::GetTime()
{
	//return frameTime;
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart - startTime.QuadPart) / ticksPerSecond;
}

float Timer::GetFrameTime()
{
	LARGE_INTEGER currentTime;
	INT64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount = currentTime.QuadPart - frameTimeOld;
	frameTimeOld = currentTime.QuadPart;

	if (tickCount < 0.0f)
		tickCount = 0.0f;

	return float(tickCount) / ticksPerSecond;
}