#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class GameObject;

class MapData
{
public:
	std::vector<GameObject*> goVec;
	std::wstring normalBgmKey;
	std::wstring bossBgmKey;
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

	void GetMapData(std::wstring _xmlFileName, MapData& _data);
};
