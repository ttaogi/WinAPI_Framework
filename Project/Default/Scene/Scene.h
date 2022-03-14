#pragma once

#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"
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

	static void ProcessCollision(std::vector<Collision>* _collisionVec);
};
