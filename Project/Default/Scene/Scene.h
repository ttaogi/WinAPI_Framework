#pragma once

#include <functional>
#include <queue>

#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"
#include "DesignPattern/ComponentBase/Component/Rendered/Rendered.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "DesignPattern/ObserverBase/Observer.h"
#include "Image/Image.h"
#include "Utility/Enums/Enums.h"

class GameObject;
class Image;
class MainGame;
class MapData;
class Enemy;

class Scene : public Observer
{
protected:
	Image* backgroundImage;
	MapData mapData;
	GameObject* root;
	GameObject* selectedObj;
	std::vector<Enemy*> enemyVec;
public:
	Scene() { }
	virtual ~Scene() { }

	virtual void OnNotify(Subject* _subject, EVENT _event) override = 0;

	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	MapData* GetMapData() { return &mapData; }

	bool IsEmpty(POINT _gridPos);

	void LoadMapData(MapData* _mapData);
	static void ProcessCollision(std::vector<Collision>* _collisionVec);
	static void ProcessRender(HDC _hdc, priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr>* _queue);
};
