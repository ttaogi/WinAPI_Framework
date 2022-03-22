#include "Stdafx/stdafx.h"

#include "Manager/MapDataManager/MapDataManager.h"

MapData::MapData()
{
	goVec.clear();
	normalBgmKey = L"";
	bossBgmKey = L"";
}

MapDataManager::MapDataManager() { }

MapDataManager::~MapDataManager() { }

HRESULT MapDataManager::Init() { return S_OK; }

void MapDataManager::Release() { }

void MapDataManager::GetMapData(std::wstring _xmlFileName, MapData& _data)
{
	_data.goVec.clear();
	_data.normalBgmKey = _data.bossBgmKey = L"";

	TiXmlDocument doc;

	if (XmlManager::LoadFile(doc, _xmlFileName))
	{
		//wcout << L"load file" << endl;
		TiXmlElement* eleRoot = XmlManager::FirstChildElement(doc, L"ROOT");

		TiXmlElement* elePlatform	= XmlManager::FirstChildElement(eleRoot, L"platform");
		TiXmlElement* eleObject		= XmlManager::FirstChildElement(eleRoot, L"object");
		TiXmlElement* eleEnemy		= XmlManager::FirstChildElement(eleRoot, L"enemy");
		TiXmlElement* eleBoss		= XmlManager::FirstChildElement(eleRoot, L"boss");
		TiXmlElement* eleBgm		= XmlManager::FirstChildElement(eleRoot, L"bgm");

		// platform.
		int platformSize = 0;
		XmlManager::GetAttributeValueInt(elePlatform, L"size", &platformSize);

		for (int i = 0; i < platformSize; ++i)
		{
			wstring key = L"p_" + to_wstring(i);
			TiXmlElement* platform = XmlManager::FirstChildElement(elePlatform, key);

			int typeRaw = 0;
			PLATFORM_FACTORY_TYPE type = PLATFORM_FACTORY_TYPE::DEFAULT;
			int x = 0;
			int y = 0;
			int width = 0;
			int height = 0;
			wstring spriteKey = L"";

			XmlManager::GetAttributeValueInt(platform, L"type", &typeRaw);
			type = (PLATFORM_FACTORY_TYPE)typeRaw;
			XmlManager::GetAttributeValueInt(platform, L"x", &x);
			XmlManager::GetAttributeValueInt(platform, L"y", &y);
			XmlManager::GetAttributeValueInt(platform, L"width", &width);
			XmlManager::GetAttributeValueInt(platform, L"height", &height);
			XmlManager::GetAttributeValue(platform, L"sprite", spriteKey);

			GameObject* go = FACTORY_METHOD_PLATFORM->CreateObject(type, D_POINT{ (double)x, (double)y }, width, height, IMG->FindImage(spriteKey));

			/*wcout << L"type raw : " << typeRaw << endl;
			wcout << L"x : " << x << endl;
			wcout << L"y : " << y << endl;
			wcout << L"width : " << width << endl;
			wcout << L"height : " << height << endl;
			wcout << L"sprite key : " << spriteKey << endl;
			wcout << L"sprite point : " << IMG->FindImage(spriteKey) << endl;
			wcout << L">>> go : " << go << endl;*/
			_data.goVec.push_back(go);
		}

		// object.

		// enemy.

		// boss.

		// bgm.
		TiXmlElement* normalBgm = XmlManager::FirstChildElement(eleBgm, L"normal");
		XmlManager::GetAttributeValue(normalBgm, L"key", _data.normalBgmKey);
		TiXmlElement* bossBgm = XmlManager::FirstChildElement(eleBgm, L"boss");
		XmlManager::GetAttributeValue(bossBgm, L"key", _data.bossBgmKey);

		/*wcout << L"vec size : " << _data.goVec.size() << endl;
		wcout << L"normal bgm : " << _data.normalBgmKey << endl;
		wcout << L"boss bgm : " << _data.bossBgmKey << endl;*/
	}
}
