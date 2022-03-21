#pragma once

#include "Scene/Scene.h"

class Stage1Scene : public Scene
{
private:
public:
	Stage1Scene();
	virtual ~Stage1Scene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};
