#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class Timer;

class TimeManager : public SingletonBase<TimeManager> {
private:
	Timer* timer;
public:
	TimeManager();
	~TimeManager();

	HRESULT Init();
	void Release();
	void Update(double _lock = 0.0);
	void Render(HDC _hdc);

	double GetWorldTime() const;
	double GetElapsedTime() const;
};
