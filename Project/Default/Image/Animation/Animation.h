#pragma once

#include "Utility/Enums/Enums.h"

class Animation
{
private:
	int frameIdx;
	double frameUpdateSec;
	double elapsedSec;
	bool loop;

	CHARACTER_STATE state;
	Image* image;
	POINT coordinateRevision;
	std::vector<POINT> frameVec;
	std::vector<int> playVec;
public:
	Animation();
	~Animation() { Release(); }

	HRESULT Init(std::wstring _imageKey, POINT _coordinateRevision,
		CHARACTER_STATE _state, bool _loop = false,
		bool _reverse = false, double _fps = 60.0);

	void Reset() { frameIdx = 0; elapsedSec = 0.0; }
	void Release() { }
	void AnimationUpdate(bool _isPlay = true);
	void AnimationRender(HDC _hdc, POINT _pos);
	bool IsEnd() const;

	int GetFrameIdx() const { return frameIdx; }
	void SetDefaultPlayFrame(bool _reverse = false, bool _loop = false);
	void SetPlayFrame(int* _playArr = nullptr, int _arrLen = 0);
	void SetPlayFrame(int _start, int _end, bool _reverse = false, bool _loop = false);
	void SetFPS(double _fps) { frameUpdateSec = 1.0 / _fps; }
};