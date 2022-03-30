#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class GameObject;

class MapData
{
public:
	int x; // ¢Ù
	int y; // ¢×
	std::vector<std::vector<GameObject*>> mapVec;
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

	bool GetMapData(std::wstring _xmlFileName, MapData& _data);
};
