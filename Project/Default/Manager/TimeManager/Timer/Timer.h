#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class Timer {
private:
	double timeScale;
	double timeElapsed;
	bool isHardware;

	__int64 curTime;
	__int64 lastTime;
	__int64 periodFrequency;

	unsigned long frameRate;
	unsigned long FPSFrameCount;
	double FPSTimeElapsed;
	double worldTime;
public:
	Timer();
	~Timer();

	void Init();

	void Tick(double lockFPS = 0.0);
	unsigned long GetFrameRate(std::wstring& _str) const;
	inline double GetElapsedTime() const { return timeElapsed; }
	inline double GetWorldTime() const { return worldTime; }
};