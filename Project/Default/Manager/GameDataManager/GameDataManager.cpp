#include "Stdafx/stdafx.h"

#include "Manager/GameDataManager/GameDataManager.h"

GameDataManager::GameDataManager()
{
	stage1Clear = false;
	stage2Clear = false;
	stage3Clear = false;
	stage4Clear = false;
	volume = DEFAULT_SOUND_VOLUME;
}

GameDataManager::~GameDataManager() { }

HRESULT GameDataManager::Init()
{
	TiXmlDocument save;

	if (XmlManager::LoadFile(save, XML_DOC_SAVEDATA))
	{
		TiXmlElement* eleRoot = XmlManager::FirstChildElement(save, L"ROOT");
		TiXmlElement* eleClear = XmlManager::FirstChildElement(eleRoot, L"clear");
		TiXmlElement* eleVolume = XmlManager::FirstChildElement(eleRoot, L"volume");

		XmlManager::GetAttributeValueBool(eleClear, L"stage1", &stage1Clear);
		XmlManager::GetAttributeValueBool(eleClear, L"stage2", &stage2Clear);
		XmlManager::GetAttributeValueBool(eleClear, L"stage3", &stage3Clear);
		XmlManager::GetAttributeValueBool(eleClear, L"stage4", &stage4Clear);

		XmlManager::GetAttributeValueFloat(eleVolume, L"volume", &volume);
	}

	wcout << L"##### GAME DATA MANAGER #####" << endl;
	wcout << L"Stage1 : " << stage1Clear << endl;
	wcout << L"Stage2 : " << stage2Clear << endl;
	wcout << L"Stage3 : " << stage3Clear << endl;
	wcout << L"Stage4 : " << stage4Clear << endl;
	wcout << L"Volume : " << volume << endl;
	wcout << L"##### GAME DATA MANAGER #####" << endl;

	return S_OK;
}

void GameDataManager::Release()
{
	TiXmlDocument save;
	XmlManager::AddDeclaration(save, L"1.0", L"UTF-8", L"");

	TiXmlElement* eleRoot = XmlManager::CreateElement(L"ROOT");
	save.LinkEndChild(eleRoot);

	/*
	ROOT
		-clear (stage1, stage2, stage3, stage4)
		-volume
	*/
	TiXmlElement* eleClear = XmlManager::CreateElement(L"clear");
	eleRoot->LinkEndChild(eleClear);
	XmlManager::SetAttribute(eleClear, L"stage1", stage1Clear);
	XmlManager::SetAttribute(eleClear, L"stage2", stage2Clear);
	XmlManager::SetAttribute(eleClear, L"stage3", stage3Clear);
	XmlManager::SetAttribute(eleClear, L"stage4", stage4Clear);

	TiXmlElement* eleVolume = XmlManager::CreateElement(L"volume");
	eleRoot->LinkEndChild(eleVolume);
	XmlManager::SetAttribute(eleVolume, L"volume", volume);

	save.SaveFile(WcsToMbsUtf8(XML_DOC_SAVEDATA).c_str());

	wcout << L"##### GAME DATA MANAGER #####" << endl;
	wcout << L"Stage1 : " << stage1Clear << endl;
	wcout << L"Stage2 : " << stage2Clear << endl;
	wcout << L"Stage3 : " << stage3Clear << endl;
	wcout << L"Stage4 : " << stage4Clear << endl;
	wcout << L"Volume : " << volume << endl;
	wcout << L"##### GAME DATA MANAGER #####" << endl;
}
