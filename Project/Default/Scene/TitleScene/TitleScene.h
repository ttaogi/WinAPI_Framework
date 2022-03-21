#pragma once

#include "Scene/Scene.h"

class TitleScene : public Scene
{
private:
public:
	TitleScene();
	virtual ~TitleScene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};