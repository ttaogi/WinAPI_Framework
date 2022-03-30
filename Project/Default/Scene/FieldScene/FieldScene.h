#pragma once

#include "Scene/Scene.h"

class FieldScene : public Scene
{
private:
public:
	FieldScene();
	virtual ~FieldScene();

	virtual void OnNotify(Subject* _subject, EVENT _event) override;

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};
