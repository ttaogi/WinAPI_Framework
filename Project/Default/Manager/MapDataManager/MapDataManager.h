#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class GameObject;
class Observer;

class MapData
{
public:
	int x; // ¢Ù
	int y; // ¢×
	std::vector<std::vector<GameObject*>> tileVec;
	std::vector<GameObject*> enemyVec;
	std::vector<GameObject*> playerVec;
public:
	MapData();
};

class MapDataManager : public SingletonBase<MapDataManager>
{
private:
public:
	MapDataManager();
	virtual ~MapDataManager();

	HRESULT Init();
	void Release();

	bool GetMapData(std::wstring _xmlFileName, Observer* _observer, MapData& _data);
};
