#include "Stdafx/stdafx.h"

#include "Manager/TimeManager/Timer/Timer.h"

Timer::Timer() { }

Timer::~Timer() { }

void Timer::Init() {
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		timeScale = 1.0 / periodFrequency;
	}
	else
	{
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 0.001;
	}

	frameRate = 0;
	FPSFrameCount = 0;
	FPSTimeElapsed = 0.0;
	worldTime = 0.0;
}

void Timer::Tick(double lockFPS) {
	if (isHardware)
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	else
		curTime = timeGetTime();

	timeElapsed = (curTime - lastTime) * timeScale;

	if (lockFPS > 0.0)
		while (timeElapsed < (1 / lockFPS))
		{
			if (isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			else
				curTime = timeGetTime();

			timeElapsed = (curTime - lastTime) * timeScale;
		}

	lastTime = curTime;
	FPSFrameCount++;
	FPSTimeElapsed += timeElapsed;
	worldTime += timeElapsed;

	if (FPSTimeElapsed > 1.0)
	{
		frameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPSTimeElapsed = 0.0;
	}
}

unsigned long Timer::GetFrameRate(wstring& _str) const {
	_str = L"FPS : " + to_wstring(frameRate);
	return frameRate;
}
