#include "Stdafx/stdafx.h"

#include "Manager/DialogManager/DialogManager.h"

#pragma region DialogInfo
DialogInfo::DialogInfo()
{
	upper = false;
	spriteKey = name = text = L"";
}

DialogInfo::DialogInfo(bool _upper, std::wstring _spriteKey, std::wstring _name, std::wstring _text)
{
	upper = _upper;
	spriteKey = _spriteKey;
	name = _name;
	text = _text;
}

void DialogInfo::Print() const
{
	wcout << L"\t\t\tupper : " << upper << " name : " << name
		<< " text : " << text << " spriteKey : " << spriteKey << endl;
}
#pragma endregion DialogInfo


#pragma region DialogCycle
DialogCycle::DialogCycle()
{
	cycleIdx = 0;
	cycleName = L"";
	cycle.clear();
}

void DialogCycle::Print() const
{
	wcout << "\t\tcycle name : " << cycleName << endl;
	for (auto iter = cycle.begin(); iter != cycle.end(); ++iter)
		iter->Print();
}
#pragma endregion DialogCycle


#pragma region DialogProcessivityMap
DialogProcessivityMap::DialogProcessivityMap()
{
	defaultDialog = DialogCycle();
}

DialogCycle DialogProcessivityMap::GetDialogCycle(int _processivity)
{
	auto iter = dialogMap.find(_processivity);

	if (iter == dialogMap.end()) return defaultDialog;
	else return iter->second;
}
void DialogProcessivityMap::Print() const
{
	wcout << L"\tdialog map" << endl;
	
	defaultDialog.Print();
	for (auto iter = dialogMap.begin(); iter != dialogMap.end(); ++iter)
		iter->second.Print();
}
#pragma endregion DialogProcessivityMap


#pragma region DialogManager
DialogManager::DialogManager() { }

DialogManager::~DialogManager() { }

HRESULT DialogManager::Init()
{
	wcout << L"##### DIALOG MANAGER #####" << endl;

	TiXmlDocument doc;

	if (XmlManager::LoadFile(doc, XML_DOC_DIALOG))
	{
		TiXmlElement* eleRoot = XmlManager::FirstChildElement(doc, L"ROOT");
		TiXmlElement* eleGuild = XmlManager::FirstChildElement(eleRoot, DIALOG_SPOT_GUILD);
		TiXmlElement* eleShop = XmlManager::FirstChildElement(eleRoot, DIALOG_SPOT_SHOP);
		TiXmlElement* eleField = XmlManager::FirstChildElement(eleRoot, DIALOG_SPOT_FIELD);

		// guild.
		DialogProcessivityMap guildDPMap;
		
		TiXmlElement* guildDefaultDialog = XmlManager::FirstChildElement(eleGuild, L"default");
		DialogCycle guildDefaultCycle;
		int guildDefaultCycleSize = 0;

		XmlManager::GetAttributeValueInt(guildDefaultDialog, L"cycleSize", &guildDefaultCycleSize);
		XmlManager::GetAttributeValue(guildDefaultDialog, L"cycleName", guildDefaultCycle.cycleName);

		for (int i = 0; i < guildDefaultCycleSize; ++i)
		{
			wstring key = L"dialog_" + to_wstring(i);
			TiXmlElement* dialog = XmlManager::FirstChildElement(guildDefaultDialog, key);

			bool upper;
			wstring spriteKey;
			wstring name;
			wstring text;

			XmlManager::GetAttributeValueBool(dialog, L"upper", &upper);
			XmlManager::GetAttributeValue(dialog, L"spriteKey", spriteKey);
			XmlManager::GetAttributeValue(dialog, L"name", name);
			XmlManager::GetAttributeValue(dialog, L"text", text);

			guildDefaultCycle.cycle.push_back(DialogInfo(upper, spriteKey, name, text));
		}

		guildDPMap.defaultDialog = guildDefaultCycle;

		int mapSize = 0;
		XmlManager::GetAttributeValueInt(eleGuild, L"mapSize", &mapSize);

		for (int i = 0; i < mapSize; ++i)
		{
			wstring key = L"dialogCycle_" + to_wstring(i);
			TiXmlElement* dialogCycle = XmlManager::FirstChildElement(eleGuild, key);

			int processivity = 0;
			int cycleSize = 0;
			wstring cycleName = L"";

			XmlManager::GetAttributeValueInt(dialogCycle, L"processivity", &processivity);
			XmlManager::GetAttributeValueInt(dialogCycle, L"cycleSize", &cycleSize);
			XmlManager::GetAttributeValue(dialogCycle, L"cycleName", cycleName);

			DialogCycle cycle;
			cycle.cycleName = cycleName;

			for (int j = 0; j < cycleSize; ++j)
			{
				wstring key = L"dialog_" + to_wstring(j);
				TiXmlElement* dialog = XmlManager::FirstChildElement(dialogCycle, key);

				bool upper;
				wstring spriteKey;
				wstring name;
				wstring text;

				XmlManager::GetAttributeValueBool(dialog, L"upper", &upper);
				XmlManager::GetAttributeValue(dialog, L"spriteKey", spriteKey);
				XmlManager::GetAttributeValue(dialog, L"name", name);
				XmlManager::GetAttributeValue(dialog, L"text", text);

				cycle.cycle.push_back(DialogInfo(upper, spriteKey, name, text));
			}

			guildDPMap.dialogMap[processivity] = cycle;
		}

		dialogDB[DIALOG_SPOT_GUILD] = guildDPMap;

		// shop.
		DialogProcessivityMap shopDPMap;

		TiXmlElement* shopDefaultDialog = XmlManager::FirstChildElement(eleShop, L"default");
		DialogCycle shopDefaultCycle;
		int shopDefaultCycleSize = 0;

		XmlManager::GetAttributeValueInt(shopDefaultDialog, L"cycleSize", &shopDefaultCycleSize);
		XmlManager::GetAttributeValue(shopDefaultDialog, L"cycleName", shopDefaultCycle.cycleName);

		for (int i = 0; i < shopDefaultCycleSize; ++i)
		{
			wstring key = L"dialog_" + to_wstring(i);
			TiXmlElement* dialog = XmlManager::FirstChildElement(shopDefaultDialog, key);

			bool upper;
			wstring spriteKey;
			wstring name;
			wstring text;

			XmlManager::GetAttributeValueBool(dialog, L"upper", &upper);
			XmlManager::GetAttributeValue(dialog, L"spriteKey", spriteKey);
			XmlManager::GetAttributeValue(dialog, L"name", name);
			XmlManager::GetAttributeValue(dialog, L"text", text);

			shopDefaultCycle.cycle.push_back(DialogInfo(upper, spriteKey, name, text));
		}

		shopDPMap.defaultDialog = shopDefaultCycle;

		mapSize = 0;
		XmlManager::GetAttributeValueInt(eleShop, L"mapSize", &mapSize);

		for (int i = 0; i < mapSize; ++i)
		{
			wstring key = L"dialogCycle_" + to_wstring(i);
			TiXmlElement* dialogCycle = XmlManager::FirstChildElement(eleShop, key);

			int processivity = 0;
			int cycleSize = 0;
			wstring cycleName = L"";

			XmlManager::GetAttributeValueInt(dialogCycle, L"processivity", &processivity);
			XmlManager::GetAttributeValueInt(dialogCycle, L"cycleSize", &cycleSize);
			XmlManager::GetAttributeValue(dialogCycle, L"cycleName", cycleName);

			DialogCycle cycle;
			cycle.cycleName = cycleName;

			for (int j = 0; j < cycleSize; ++j)
			{
				wstring key = L"dialog_" + to_wstring(j);
				TiXmlElement* dialog = XmlManager::FirstChildElement(dialogCycle, key);

				bool upper;
				wstring spriteKey;
				wstring name;
				wstring text;

				XmlManager::GetAttributeValueBool(dialog, L"upper", &upper);
				XmlManager::GetAttributeValue(dialog, L"spriteKey", spriteKey);
				XmlManager::GetAttributeValue(dialog, L"name", name);
				XmlManager::GetAttributeValue(dialog, L"text", text);

				cycle.cycle.push_back(DialogInfo(upper, spriteKey, name, text));
			}

			shopDPMap.dialogMap[processivity] = cycle;
		}

		dialogDB[DIALOG_SPOT_SHOP] = shopDPMap;

		// field.
		DialogProcessivityMap fieldDPMap;

		TiXmlElement* fieldDefaultDialog = XmlManager::FirstChildElement(eleField, L"default");
		DialogCycle fieldDefaultCycle;
		int fieldDefaultCycleSize = 0;

		XmlManager::GetAttributeValueInt(fieldDefaultDialog, L"cycleSize", &fieldDefaultCycleSize);
		XmlManager::GetAttributeValue(fieldDefaultDialog, L"cycleName", fieldDefaultCycle.cycleName);

		for (int i = 0; i < fieldDefaultCycleSize; ++i)
		{
			wstring key = L"dialog_" + to_wstring(i);
			TiXmlElement* dialog = XmlManager::FirstChildElement(fieldDefaultDialog, key);

			bool upper;
			wstring spriteKey;
			wstring name;
			wstring text;

			XmlManager::GetAttributeValueBool(dialog, L"upper", &upper);
			XmlManager::GetAttributeValue(dialog, L"spriteKey", spriteKey);
			XmlManager::GetAttributeValue(dialog, L"name", name);
			XmlManager::GetAttributeValue(dialog, L"text", text);

			fieldDefaultCycle.cycle.push_back(DialogInfo(upper, spriteKey, name, text));
		}

		fieldDPMap.defaultDialog = fieldDefaultCycle;

		dialogDB[DIALOG_SPOT_FIELD] = fieldDPMap;
	}

	Print();

	wcout << L"##### DIALOG MANAGER #####" << endl;

	return S_OK;
}

void DialogManager::Release() { }

DialogCycle DialogManager::GetDialogCycle(std::wstring _spot, int _processivity)
{
	auto iter = dialogDB.find(_spot);

	if (iter == dialogDB.end()) return DialogCycle();

	return iter->second.GetDialogCycle(_processivity);
}

void DialogManager::Print() const
{
	wcout << L"***** DIALOG MANAGER *****" << endl;
	for (auto iter = dialogDB.begin(); iter != dialogDB.end(); ++iter)
	{
		wcout << L"spot : " << iter->first << endl;
		iter->second.Print();
	}
	wcout << L"***** DIALOG MANAGER *****" << endl;
}
#pragma endregion DialogManager

