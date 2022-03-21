#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class Timer;

class TimeManager : public SingletonBase<TimeManager> {
private:
	double timeScale;
	Timer* timer;
public:
	TimeManager();
	virtual ~TimeManager();

	HRESULT Init();
	void Release();
	void Update(double _lock = 0.0);
	void Render(HDC _hdc);

	double GetWorldTime() const;
	double GetElapsedTime() const;
	double GetScaledElapsedTime() const;
	double	GetTimeScale() const			{ return timeScale; }
	void	SetTimeScale(double _timeScale)	{ timeScale = _timeScale; }
};
