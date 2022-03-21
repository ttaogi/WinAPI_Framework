#pragma once

#include "Scene/Scene.h"

class Stage2Scene : public Scene
{
private:
public:
	Stage2Scene();
	virtual ~Stage2Scene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};
