#pragma once

#include "Scene/Scene.h"

class LobbyScene : public Scene
{
private:
public:
	LobbyScene();
	virtual ~LobbyScene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};
