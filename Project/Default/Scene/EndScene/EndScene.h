#pragma once

#include "Scene/Scene.h"

class EndScene : public Scene
{
private:
public:
	EndScene();
	virtual ~EndScene();

	virtual void OnNotify(Subject* _subject, EVENT _event) override { }

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void Render() override;
};