#include "Stdafx/stdafx.h"

#include "Manager/MapDataManager/MapDataManager.h"

MapData::MapData()
{
	x = y = 0;
	tileVec.clear();
}

MapDataManager::MapDataManager() { }

MapDataManager::~MapDataManager() { }

HRESULT MapDataManager::Init() { return S_OK; }

void MapDataManager::Release() { }

/*
ROOT
	tile(int x, int y)
		x_m
			y_n(TILE_TYPE type)
*/
bool MapDataManager::GetMapData(std::wstring _xmlFileName, Observer* _observer, MapData& _data)
{
	wcout << L">>>> Load Map Data : " << _xmlFileName << endl;

	TiXmlDocument doc;

	if (XmlManager::LoadFile(doc, _xmlFileName))
	{
		TiXmlElement* eleRoot = XmlManager::FirstChildElement(doc, L"ROOT");

		// tile.
		TiXmlElement* eleTile = XmlManager::FirstChildElement(eleRoot, L"tile");
		XmlManager::GetAttributeValueInt(eleTile, L"x", &(_data.x));
		XmlManager::GetAttributeValueInt(eleTile, L"y", &(_data.y));

		_data.tileVec.clear();
		_data.tileVec.reserve(_data.x);
		for (int i = 0; i < _data.x; ++i)
		{
			vector<GameObject*> colVec;
			colVec.reserve(_data.y);
			for (int j = 0; j < _data.y; ++j) colVec.push_back(NULL);
			_data.tileVec.push_back(colVec);
		}

		for (int i = 0; i < _data.x; ++i)
		{
			wstring key = L"x_" + to_wstring(i);
			TiXmlElement* eleCol = XmlManager::FirstChildElement(eleTile, key);
			if (!eleCol) return false;

			for (int j = 0; j < _data.y; ++j)
			{
				wstring key = L"y_" + to_wstring(j);
				TiXmlElement* eleTile = XmlManager::FirstChildElement(eleCol, key);
				if (!eleTile) return false;
				int tileTypeRaw = 0;
				XmlManager::GetAttributeValueInt(eleTile, L"type", &tileTypeRaw);
				TILE_TYPE tileType = (TILE_TYPE)tileTypeRaw;
				GameObject* tile = FACTORY_METHOD_TILE->CreateObject(tileType, _observer, POINT{ i, j });

				_data.tileVec[i][j] = tile;
			}
		}

		// enemy.

		// player.

	}
	else
		return false;

	return true;
}
