#include "Stdafx/stdafx.h"

#include "Manager/GameDataManager/GameDataManager.h"

GameDataManager::GameDataManager()
{
	processivity = 0;
	volume = DEFAULT_SOUND_VOLUME;
	characterInfoVec.clear();
	characterInfoVec.reserve((int)CHARACTER_ID::CHARACTER_ID_NUM);
	equipInfoVec.clear();
	equipInfoVec.reserve((int)EQUIP_ID::EQUIP_ID_NUM);

	for (int i = 0; i < (int)CHARACTER_ID::CHARACTER_ID_NUM; ++i) characterInfoVec.push_back(CharacterInfo());

	characterInfoVec[(int)CHARACTER_ID::AL].id = CHARACTER_ID::AL;
	characterInfoVec[(int)CHARACTER_ID::KARIN].id = CHARACTER_ID::KARIN;

	for (int i = 0; i < (int)EQUIP_ID::EQUIP_ID_NUM; ++i) equipInfoVec.push_back(EquipInfo());
}

GameDataManager::~GameDataManager() { }

HRESULT GameDataManager::Init()
{
	wcout << L"##### GAME DATA MANAGER #####" << endl;

	TiXmlDocument save;

	if (XmlManager::LoadFile(save, XML_DOC_SAVEDATA))
	{
		TiXmlElement* eleRoot = XmlManager::FirstChildElement(save, L"ROOT");
		TiXmlElement* eleProcessivity = XmlManager::FirstChildElement(eleRoot, L"processivity");
		TiXmlElement* eleVolume = XmlManager::FirstChildElement(eleRoot, L"volume");
		TiXmlElement* eleGold = XmlManager::FirstChildElement(eleRoot, L"gold");
		TiXmlElement* eleCharacterInfo = XmlManager::FirstChildElement(eleRoot, L"characterInfo");
		TiXmlElement* eleEquipInfo = XmlManager::FirstChildElement(eleRoot, L"equipInfo");
		TiXmlElement* eleInventory = XmlManager::FirstChildElement(eleRoot, L"inventory");

		XmlManager::GetAttributeValueInt(eleProcessivity, L"processivity", &processivity);
		XmlManager::GetAttributeValueFloat(eleVolume, L"volume", &volume);
		XmlManager::GetAttributeValueInt(eleGold, L"gold", &gold);

		int equip = 0;
		TiXmlElement* eleCharAl = XmlManager::FirstChildElement(eleCharacterInfo, L"al");
		XmlManager::GetAttributeValueBool(eleCharAl, L"isMember", &characterInfoVec[(int)CHARACTER_ID::AL].isMember);
		XmlManager::GetAttributeValueInt(eleCharAl, L"level", &characterInfoVec[(int)CHARACTER_ID::AL].level);
		XmlManager::GetAttributeValueInt(eleCharAl, L"hp", &characterInfoVec[(int)CHARACTER_ID::AL].hp);
		XmlManager::GetAttributeValueInt(eleCharAl, L"hpMax", &characterInfoVec[(int)CHARACTER_ID::AL].hpMax);
		XmlManager::GetAttributeValueInt(eleCharAl, L"str", &characterInfoVec[(int)CHARACTER_ID::AL].str);
		XmlManager::GetAttributeValueInt(eleCharAl, L"mgc", &characterInfoVec[(int)CHARACTER_ID::AL].mgc);
		XmlManager::GetAttributeValueInt(eleCharAl, L"def", &characterInfoVec[(int)CHARACTER_ID::AL].def);
		XmlManager::GetAttributeValueInt(eleCharAl, L"mDef", &characterInfoVec[(int)CHARACTER_ID::AL].mDef);
		XmlManager::GetAttributeValueInt(eleCharAl, L"dex", &characterInfoVec[(int)CHARACTER_ID::AL].dex);
		XmlManager::GetAttributeValueInt(eleCharAl, L"exp", &characterInfoVec[(int)CHARACTER_ID::AL].exp);
		XmlManager::GetAttributeValueInt(eleCharAl, L"expMax", &characterInfoVec[(int)CHARACTER_ID::AL].expMax);
		XmlManager::GetAttributeValueInt(eleCharAl, L"weapon", &equip);
		characterInfoVec[(int)CHARACTER_ID::AL].weapon = (EQUIP_ID)equip;
		XmlManager::GetAttributeValueInt(eleCharAl, L"armor", &equip);
		characterInfoVec[(int)CHARACTER_ID::AL].armor = (EQUIP_ID)equip;

		TiXmlElement* eleCharKarin = XmlManager::FirstChildElement(eleCharacterInfo, L"karin");
		XmlManager::GetAttributeValueBool(eleCharKarin, L"isMember", &characterInfoVec[(int)CHARACTER_ID::KARIN].isMember);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"level", &characterInfoVec[(int)CHARACTER_ID::KARIN].level);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"hp", &characterInfoVec[(int)CHARACTER_ID::KARIN].hp);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"hpMax", &characterInfoVec[(int)CHARACTER_ID::KARIN].hpMax);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"str", &characterInfoVec[(int)CHARACTER_ID::KARIN].str);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"mgc", &characterInfoVec[(int)CHARACTER_ID::KARIN].mgc);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"def", &characterInfoVec[(int)CHARACTER_ID::KARIN].def);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"mDef", &characterInfoVec[(int)CHARACTER_ID::KARIN].mDef);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"dex", &characterInfoVec[(int)CHARACTER_ID::KARIN].dex);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"exp", &characterInfoVec[(int)CHARACTER_ID::KARIN].exp);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"expMax", &characterInfoVec[(int)CHARACTER_ID::KARIN].expMax);
		XmlManager::GetAttributeValueInt(eleCharKarin, L"weapon", &equip);
		characterInfoVec[(int)CHARACTER_ID::KARIN].weapon = (EQUIP_ID)equip;
		XmlManager::GetAttributeValueInt(eleCharKarin, L"armor", &equip);
		characterInfoVec[(int)CHARACTER_ID::KARIN].armor = (EQUIP_ID)equip;

		//eleEquipInfo
		for (int i = 0; i < (int)EQUIP_ID::EQUIP_ID_NUM; ++i)
		{
			wstring key = L"equip_" + to_wstring(i);
			TiXmlElement* equip = XmlManager::FirstChildElement(eleEquipInfo, key);

			EquipInfo info;
			int idRaw = 0;
			XmlManager::GetAttributeValueInt(equip, L"id", &idRaw);
			info.id = (EQUIP_ID)idRaw;
			XmlManager::GetAttributeValue(equip, L"name", info.name);
			int typeRaw = 0;
			XmlManager::GetAttributeValueInt(equip, L"type", &typeRaw);
			info.type = (EQUIP_TYPE)typeRaw;
			XmlManager::GetAttributeValueInt(equip, L"priceBuy", &info.priceBuy);
			XmlManager::GetAttributeValueInt(equip, L"priceSell", &info.priceSell);
			XmlManager::GetAttributeValueInt(equip, L"level", &info.level);
			XmlManager::GetAttributeValueInt(equip, L"str", &info.str);
			XmlManager::GetAttributeValueInt(equip, L"mgc", &info.mgc);
			XmlManager::GetAttributeValueInt(equip, L"def", &info.def);
			XmlManager::GetAttributeValueInt(equip, L"mDef", &info.mDef);

			equipInfoVec[idRaw] = info;
		}

		int inventorySize = 0;
		XmlManager::GetAttributeValueInt(eleInventory, L"size", &inventorySize);
		for (int i = 0; i < inventorySize; ++i)
		{
			wstring key = L"item_" + to_wstring(i);
			TiXmlElement* item = XmlManager::FirstChildElement(eleInventory, key);

			if (!item) continue;

			EquipInfo e;
			int idRaw = 0;
			EQUIP_ID id = EQUIP_ID::NONE;
			XmlManager::GetAttributeValueInt(item, L"id", &idRaw);
			id = (EQUIP_ID)idRaw;

			if (id == EQUIP_ID::NONE || id == EQUIP_ID::EQUIP_ID_NUM) continue;

			e = GetEquipInfo(id);
			inventory.push_back(e);
		}
	}

	//wcout << L"Processivity : " << processivity << endl;
	//wcout << L"Volume : " << volume << endl;
	//wcout << L"Gold : " << gold << endl;
	//wcout << L"Character info : " << endl;
	//wcout << L"Al : " << endl;
	//characterInfoVec[(int)CHARACTER_ID::AL].Print();
	//wcout << L"Karin : " << endl;
	//characterInfoVec[(int)CHARACTER_ID::KARIN].Print();
	//wcout << L"Equip info : " << endl;
	//for (EquipInfo ei : equipInfoVec) ei.Print();
	//wcout << L"Inventory : " << endl;
	//for (EquipInfo ei : inventory) ei.Print();
	wcout << L"##### GAME DATA MANAGER #####" << endl;

	return S_OK;
}

void GameDataManager::Release()
{
	wcout << L"##### GAME DATA MANAGER #####" << endl;

	TiXmlDocument save;
	XmlManager::AddDeclaration(save, L"1.0", L"UTF-8", L"");

	TiXmlElement* eleRoot = XmlManager::CreateElement(L"ROOT");
	save.LinkEndChild(eleRoot);

	TiXmlElement* eleProcessivity = XmlManager::CreateElement(L"processivity");
	eleRoot->LinkEndChild(eleProcessivity);
	XmlManager::SetAttribute(eleProcessivity, L"processivity", processivity);

	TiXmlElement* eleVolume = XmlManager::CreateElement(L"volume");
	eleRoot->LinkEndChild(eleVolume);
	XmlManager::SetAttribute(eleVolume, L"volume", volume);

	TiXmlElement* eleGold = XmlManager::CreateElement(L"gold");
	eleRoot->LinkEndChild(eleGold);
	XmlManager::SetAttribute(eleGold, L"gold", gold);

	TiXmlElement* eleCharacterInfo = XmlManager::CreateElement(L"characterInfo");
	eleRoot->LinkEndChild(eleCharacterInfo);

	TiXmlElement* eleCharAl = XmlManager::CreateElement(L"al");
	eleCharacterInfo->LinkEndChild(eleCharAl);
	XmlManager::SetAttribute(eleCharAl, L"isMember", (int)characterInfoVec[(int)CHARACTER_ID::AL].isMember);
	XmlManager::SetAttribute(eleCharAl, L"level", characterInfoVec[(int)CHARACTER_ID::AL].level);

	XmlManager::SetAttribute(eleCharAl, L"hp", characterInfoVec[(int)CHARACTER_ID::AL].hp);
	XmlManager::SetAttribute(eleCharAl, L"hpMax", characterInfoVec[(int)CHARACTER_ID::AL].hpMax);
	XmlManager::SetAttribute(eleCharAl, L"str", characterInfoVec[(int)CHARACTER_ID::AL].str);
	XmlManager::SetAttribute(eleCharAl, L"mgc", characterInfoVec[(int)CHARACTER_ID::AL].mgc);
	XmlManager::SetAttribute(eleCharAl, L"def", characterInfoVec[(int)CHARACTER_ID::AL].def);
	XmlManager::SetAttribute(eleCharAl, L"mDef", characterInfoVec[(int)CHARACTER_ID::AL].mDef);
	XmlManager::SetAttribute(eleCharAl, L"dex", characterInfoVec[(int)CHARACTER_ID::AL].dex);
	XmlManager::SetAttribute(eleCharAl, L"exp", characterInfoVec[(int)CHARACTER_ID::AL].exp);
	XmlManager::SetAttribute(eleCharAl, L"expMax", characterInfoVec[(int)CHARACTER_ID::AL].expMax);
	XmlManager::SetAttribute(eleCharAl, L"weapon", (int)characterInfoVec[(int)CHARACTER_ID::AL].weapon);
	XmlManager::SetAttribute(eleCharAl, L"armor", (int)characterInfoVec[(int)CHARACTER_ID::AL].armor);

	TiXmlElement* eleCharKarin = XmlManager::CreateElement(L"karin");
	eleCharacterInfo->LinkEndChild(eleCharKarin);
	XmlManager::SetAttribute(eleCharKarin, L"isMember", (int)characterInfoVec[(int)CHARACTER_ID::KARIN].isMember);
	XmlManager::SetAttribute(eleCharKarin, L"level", characterInfoVec[(int)CHARACTER_ID::KARIN].level);

	XmlManager::SetAttribute(eleCharKarin, L"hp", characterInfoVec[(int)CHARACTER_ID::KARIN].hp);
	XmlManager::SetAttribute(eleCharKarin, L"hpMax", characterInfoVec[(int)CHARACTER_ID::KARIN].hpMax);
	XmlManager::SetAttribute(eleCharKarin, L"str", characterInfoVec[(int)CHARACTER_ID::KARIN].str);
	XmlManager::SetAttribute(eleCharKarin, L"mgc", characterInfoVec[(int)CHARACTER_ID::KARIN].mgc);
	XmlManager::SetAttribute(eleCharKarin, L"def", characterInfoVec[(int)CHARACTER_ID::KARIN].def);
	XmlManager::SetAttribute(eleCharKarin, L"mDef", characterInfoVec[(int)CHARACTER_ID::KARIN].mDef);
	XmlManager::SetAttribute(eleCharKarin, L"dex", characterInfoVec[(int)CHARACTER_ID::KARIN].dex);
	XmlManager::SetAttribute(eleCharKarin, L"exp", characterInfoVec[(int)CHARACTER_ID::KARIN].exp);
	XmlManager::SetAttribute(eleCharKarin, L"expMax", characterInfoVec[(int)CHARACTER_ID::KARIN].expMax);
	XmlManager::SetAttribute(eleCharKarin, L"weapon", (int)characterInfoVec[(int)CHARACTER_ID::KARIN].weapon);
	XmlManager::SetAttribute(eleCharKarin, L"armor", (int)characterInfoVec[(int)CHARACTER_ID::KARIN].armor);

	TiXmlElement* eleEquipInfo = XmlManager::CreateElement(L"equipInfo");
	eleRoot->LinkEndChild(eleEquipInfo);

	for (int i = 0; i < equipInfoVec.size(); ++i)
	{
		wstring key = L"equip_" + to_wstring((int)equipInfoVec[i].id);
		TiXmlElement* equip = XmlManager::CreateElement(key);
		eleEquipInfo->LinkEndChild(equip);

		XmlManager::SetAttribute(equip, L"id", (int)equipInfoVec[i].id);
		XmlManager::SetAttribute(equip, L"name", equipInfoVec[i].name);
		XmlManager::SetAttribute(equip, L"type", (int)equipInfoVec[i].type);
		XmlManager::SetAttribute(equip, L"priceBuy", equipInfoVec[i].priceBuy);
		XmlManager::SetAttribute(equip, L"priceSell", equipInfoVec[i].priceSell);
		XmlManager::SetAttribute(equip, L"level", equipInfoVec[i].level);
		XmlManager::SetAttribute(equip, L"str", equipInfoVec[i].str);
		XmlManager::SetAttribute(equip, L"mgc", equipInfoVec[i].mgc);
		XmlManager::SetAttribute(equip, L"def", equipInfoVec[i].def);
		XmlManager::SetAttribute(equip, L"mDef", equipInfoVec[i].mDef);
	}

	TiXmlElement* eleInventory = XmlManager::CreateElement(L"inventory");
	eleRoot->LinkEndChild(eleInventory);
	XmlManager::SetAttribute(eleInventory, L"size", (int)inventory.size());

	for (int i = 0; i < inventory.size(); ++i)
	{
		wstring key = L"item_" + to_wstring(i);
		TiXmlElement* item = XmlManager::CreateElement(key);
		eleInventory->LinkEndChild(item);

		XmlManager::SetAttribute(item, L"id", (int)inventory[i].id);
	}

	save.SaveFile(WcsToMbsUtf8(XML_DOC_SAVEDATA).c_str());

	//wcout << L"Processivity : " << processivity << endl;
	//wcout << L"Volume : " << volume << endl;
	//wcout << L"Gold : " << gold << endl;
	//wcout << L"Character info : " << endl;
	//wcout << L"Al : " << endl;
	//characterInfoVec[(int)CHARACTER_ID::AL].Print();
	//wcout << L"Karin : " << endl;
	//characterInfoVec[(int)CHARACTER_ID::KARIN].Print();
	//wcout << L"Equip info : " << endl;
	//for (EquipInfo ei : equipInfoVec) ei.Print();
	//wcout << L"Inventory : " << endl;
	//for (EquipInfo ei : inventory) ei.Print();
	wcout << L"##### GAME DATA MANAGER #####" << endl;
}

CharacterInfo GameDataManager::GetCharacterInfo(CHARACTER_ID _id) const
{
	if ((int)_id < characterInfoVec.size()) return characterInfoVec[(int)_id];

	CharacterInfo info;
	info.id = CHARACTER_ID::CHARACTER_ID_NUM;

	return info;
}

void GameDataManager::SetCharacterInfo(CHARACTER_ID _id, CharacterInfo _info)
{
	if ((int)_id < characterInfoVec.size()) characterInfoVec[(int)_id] = _info;
}

EquipInfo GameDataManager::GetEquipInfo(EQUIP_ID _id) const
{
	EquipInfo info;
	info.id = EQUIP_ID::NONE;

	for (auto iter = equipInfoVec.begin(); iter != equipInfoVec.end(); ++iter)
		if (iter->id == _id)
		{
			info = *iter;
			break;
		}

	return info;
}

bool GameDataManager::AddItem(EquipInfo _item)
{
	inventory.push_back(_item);

	return true;
}

bool GameDataManager::RemoveItem(EquipInfo _item)
{
	for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
		if (iter->id == _item.id)
		{
			inventory.erase(iter);
			return true;
		}

	return false;
}
