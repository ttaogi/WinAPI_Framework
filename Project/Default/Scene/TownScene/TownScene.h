#pragma once

#include "Scene/Scene.h"

class TownScene : public Scene
{
private:
public:
	TownScene();
	virtual ~TownScene();

	virtual void OnNotify(Subject* _subject, EVENT _event) override { }

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};