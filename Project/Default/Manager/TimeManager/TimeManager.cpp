#include "Stdafx/stdafx.h"

#include "Manager/TimeManager/TimeManager.h"

#include "Manager/TimeManager/Timer/Timer.h"

TimeManager::TimeManager()
{
	timeScale = 1;
}

TimeManager::~TimeManager()
{
	Release();
}

HRESULT TimeManager::Init()
{
	timer = new Timer();
	timer->Init();

	return S_OK;
}

void TimeManager::Release() {
	SAFE_DELETE(timer);
}

void TimeManager::Update(double _lock)
{
	if (timer) timer->Tick(_lock);
}

void TimeManager::Render(HDC _hdc) {
	std::wstring str;

	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(255, 255, 255));

#ifdef _DEBUG
	if (timer) {
		timer->GetFrameRate(str);
		TextOut(_hdc, 0, 0, str.c_str(), (int)str.length());
		str = to_wstring(timer->GetElapsedTime());
		TextOut(_hdc, 0, 20, str.c_str(), (int)str.length());
		str = to_wstring(timer->GetWorldTime());
		TextOut(_hdc, 0, 40, str.c_str(), (int)str.length());

		str = to_wstring(timeScale);
		TextOut(_hdc, 0, 60, str.c_str(), (int)str.length());
		str = to_wstring(timeScale * timer->GetElapsedTime());
		TextOut(_hdc, 0, 80, str.c_str(), (int)str.length());
	}
#else
	if (timer) {
		timer->GetFrameRate(str);
		TextOut(_hdc, 0, 0, str.c_str(), (int)str.length());
	}
#endif
	SetTextColor(_hdc, RGB(0, 0, 0));
	SetBkMode(_hdc, OPAQUE);
}

double TimeManager::GetWorldTime() const { return timer->GetWorldTime(); }

double TimeManager::GetElapsedTime() const { return timer->GetElapsedTime(); }

double TimeManager::GetScaledElapsedTime() const { return timeScale * timer->GetElapsedTime(); }
