#pragma once

#include "Scene/Scene.h"

class Stage4Scene : public Scene
{
private:
public:
	Stage4Scene();
	virtual ~Stage4Scene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};