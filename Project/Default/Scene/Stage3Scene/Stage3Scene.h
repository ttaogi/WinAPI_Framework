#pragma once

#include "Scene/Scene.h"

class Stage3Scene : public Scene
{
private:
public:
	Stage3Scene();
	virtual ~Stage3Scene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};
