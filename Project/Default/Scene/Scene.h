#pragma once

#include "Utility/Enums/Enums.h"

class GameObject;
class Image;
class MainGame;

class Scene
{
protected:
	Image* backgroundImage;
	std::vector<GameObject*> gameObjects;
	GameObject* root;
public:
	Scene() { }
	~Scene() { }

	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	GameObject* GetObjectByName(std::wstring _name);
};
