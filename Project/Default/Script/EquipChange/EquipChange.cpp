#include "Stdafx/stdafx.h"

#include "Script/EquipChange/EquipChange.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedText/RenderedText.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#pragma region EquipChange
EquipChange::EquipChange()
	: Component((const Component_ID)typeid(EquipChange).name()) { }

void EquipChange::Update() { }

void EquipChange::OnNotify(Subject* _subject, EVENT _event)
{
}

void EquipChange::Renew()
{
	if (curCharacter == CHARACTER_ID::AL)
		chPortrait->SetImage(IMG->FindImage(KEY_UI_PORTRAIT_AL_DEFAULT_SPRITE));
	else
		chPortrait->SetImage(IMG->FindImage(KEY_UI_PORTRAIT_KARIN_DEFAULT_SPRITE));

	CharacterInfo cInfo = GAMEDATA->GetCharacterInfo(curCharacter);
	EquipInfo weapon = GAMEDATA->GetEquipInfo(cInfo.weapon);
	EquipInfo armor = GAMEDATA->GetEquipInfo(cInfo.armor);

	chLevel->SetStr(cInfo.name + L"\t\t\tL" + to_wstring(cInfo.level));
	chAbilFigure->SetStr(
		to_wstring(cInfo.hp) + L"/" +
		to_wstring(cInfo.hpMax) + L"\n" +
		L"-/-\n" + 
		to_wstring(cInfo.str) + L"(+ " + to_wstring(weapon.str + armor.str) + L")\n" +
		to_wstring(cInfo.def) + L"(+ " + to_wstring(weapon.def + armor.def) + L")\n" +
		to_wstring(cInfo.mgc) + L"(+ " + to_wstring(weapon.mgc + armor.mgc) + L")\n" +
		to_wstring(cInfo.mDef) + L"(+ " + to_wstring(weapon.mDef + armor.mDef) + L")\n" +
		to_wstring(cInfo.dex) + L"(+ 0)\n"
	);
	weaponText->SetStr(weapon.name);
	armorText->SetStr(armor.name);

	vector<EquipInfo> invenCopy = GAMEDATA->GetInventory();
	vector<EquipInfo> candidateVec;

	for (auto iter = invenCopy.begin(); iter != invenCopy.end(); ++iter)
		if ((*iter).type == selectedEquipType) candidateVec.push_back(*iter);

	for (auto iter = equipInInvenPanelVec.begin(); iter != equipInInvenPanelVec.end(); ++iter)
	{
		if (!candidateVec.empty())
		{
			(*iter)->SetEquipId(candidateVec.front().id);
			candidateVec.erase(candidateVec.begin());
		}
		else
			(*iter)->SetEquipId(EQUIP_ID::NONE);
	}

	if (curTab == TAB::ABILITY)
	{
		abilPanel->SetActive(true);
		equipPanel->SetActive(false);
	}
	else
	{
		abilPanel->SetActive(false);
		equipPanel->SetActive(true);
	}
}
#pragma endregion EquipChange


#pragma region ECCharacterPanel
ECCharacterPanel::ECCharacterPanel()
	: Component((const Component_ID)typeid(ECCharacterPanel).name()) { }

void ECCharacterPanel::Update()
{
}
#pragma endregion ECCharacterPanel


#pragma region ECAbilityTabPanel
ECAbilityTabPanel::ECAbilityTabPanel()
	: Component((const Component_ID)typeid(ECAbilityTabPanel).name()) { }

void ECAbilityTabPanel::Update()
{
}
#pragma endregion ECAbilityTabPanel


#pragma region ECEquipTabPanel
ECEquipTabPanel::ECEquipTabPanel()
	: Component((const Component_ID)typeid(ECEquipTabPanel).name()) { }

void ECEquipTabPanel::Update()
{
}
#pragma endregion ECEquipTabPanel


#pragma region ECWeaponText
ECWeaponText::ECWeaponText()
	: Component((const Component_ID)typeid(ECWeaponText).name()) { }

void ECWeaponText::Update()
{
}
#pragma endregion ECWeaponText


#pragma region ECArmorText
ECArmorText::ECArmorText()
	: Component((const Component_ID)typeid(ECArmorText).name()) { }

void ECArmorText::Update()
{
}
#pragma endregion ECWeaponName


#pragma region ECEquipInInvenPanel
ECEquipInInvenPanel::ECEquipInInvenPanel()
	: Component((const Component_ID)typeid(ECEquipInInvenPanel).name()) { }

void ECEquipInInvenPanel::Update()
{
}

void ECEquipInInvenPanel::SetEquipId(EQUIP_ID _equipId)
{
	equipId = _equipId;

	gameObject->GetComponent<RenderedText>()->SetStr(
		GAMEDATA->GetEquipInfo(equipId).name
	);
}
#pragma endregion ECEquipInInvenPanel


#pragma region ToShopListButton
ToShopListButton::ToShopListButton()
	: Component((const Component_ID)typeid(ToShopListButton).name()) { }

void ToShopListButton::Update()
{
}
#pragma endregion ToShopListButton


#pragma region EquipChangeButton
EquipChangeButton::EquipChangeButton()
	: Component((const Component_ID)typeid(EquipChangeButton).name()) { }

void EquipChangeButton::Update()
{
}
#pragma endregion EquipChangeButton

