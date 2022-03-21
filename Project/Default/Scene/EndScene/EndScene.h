#pragma once

#include "Scene/Scene.h"

class EndScene : public Scene
{
private:
public:
	EndScene();
	virtual ~EndScene();

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void Render() override;
};