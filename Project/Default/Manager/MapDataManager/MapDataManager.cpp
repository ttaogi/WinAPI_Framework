#include "Stdafx/stdafx.h"

#include "Manager/MapDataManager/MapDataManager.h"

MapData::MapData()
{
	x = y = 0;
	mapVec.clear();
}

MapDataManager::MapDataManager() { }

MapDataManager::~MapDataManager() { }

HRESULT MapDataManager::Init() { return S_OK; }

void MapDataManager::Release() { }

bool MapDataManager::GetMapData(std::wstring _xmlFileName, MapData& _data)
{
	////////////////////////////////

	return true;
}
