#pragma once

#include "Scene/Scene.h"

class GuildScene : public Scene
{
private:
public:
	GuildScene();
	virtual ~GuildScene();

	virtual void OnNotify(Subject* _subject, EVENT _event) override;

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};