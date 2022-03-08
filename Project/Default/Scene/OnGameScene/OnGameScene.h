#pragma once

#include "Scene/Scene.h"

class OnGameScene : public Scene
{
private:
	std::wstring msg;

	int alpha;
	int bgSpeed;
	int bgOffsetX;
	int bgOffsetY;
public:
	OnGameScene();
	~OnGameScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};