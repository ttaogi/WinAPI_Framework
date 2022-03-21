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
	virtual ~OnGameScene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};