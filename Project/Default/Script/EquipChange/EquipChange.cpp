#include "Stdafx/stdafx.h"

#include "Script/EquipChange/EquipChange.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedText/RenderedText.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#pragma region EquipChange
EquipChange::EquipChange()
	: Component((const Component_ID)typeid(EquipChange).name()) { }

void EquipChange::Init() { Renew(); }

void EquipChange::OnNotify(Subject* _subject, EVENT _event)
{
	switch (_event)
	{
	case EVENT::EQUIP_CHANGE_CHARACTER_PANEL_CLICK:
	{
		curCharacter = ((ECCharacterPanel*)_subject)->GetCharacterId();
		Renew();
	}
		break;
	case EVENT::EQUIP_CHANGE_ABILITY_TAB_PANEL_CLICK:
	{
		curTab = TAB::ABILITY;
		Renew();
	}
		break;
	case EVENT::EQUIP_CHANGE_EQUIP_TAB_PANEL_CLICK:
	{
		curTab = TAB::EQUIP;
		Renew();
	}
		break;
	case EVENT::EQUIP_CHANGE_EQUIP_WEAPON_TEXT_CLICK:
	{
		selectedEquipType = EQUIP_TYPE::WEAPON;
		Renew();
	}
		break;
	case EVENT::EQUIP_CHANGE_EQUIP_ARMOR_TEXT_CLICK:
	{
		selectedEquipType = EQUIP_TYPE::ARMOR;
		Renew();
	}
		break;
	case EVENT::EQUIP_CHANGE_EQUIP_IN_INVEN_PANEL_CLICK:
	{
		selectedEquip = ((ECEquipInInvenPanel*)_subject)->GetEquipId();
		Renew();
	}
		break;
	case EVENT::EQUIP_CHANGE_TO_SHOP_LIST_BUTTON_CLICK:
	{
		Notify(EVENT::EQUIP_CHANGE_TO_SHOP_LIST_BUTTON_CLICK);
	}
		break;
	case EVENT::EQUIP_CHANGE_EQUIP_CHANGE_BUTTON_CLICK:
	{
		if (GAMEDATA->GetEquipInfo(selectedEquip).type == selectedEquipType)
		{
			EquipInfo chEquip;
			CharacterInfo chInfo = GAMEDATA->GetCharacterInfo(curCharacter);

			if (selectedEquipType == EQUIP_TYPE::WEAPON)
			{
				chEquip = GAMEDATA->GetEquipInfo(chInfo.armor);
				chInfo.weapon = selectedEquip;
			}
			else
			{
				chEquip = GAMEDATA->GetEquipInfo(chInfo.weapon);
				chInfo.armor = selectedEquip;
			}

			GAMEDATA->SetCharacterInfo(curCharacter, chInfo);

			GAMEDATA->RemoveItem(GAMEDATA->GetEquipInfo(selectedEquip));
			GAMEDATA->AddItem(chEquip);
		}
		Renew();
	}
		break;
	}
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

	chLevel->SetStr(cInfo.name + L"   L" + to_wstring(cInfo.level));

	chAbilHpFigure->SetStr(to_wstring(cInfo.hpMax));
	chAbilMpFigure->SetStr(L"-");
	chAbilStrFigure->SetStr(to_wstring(cInfo.str) + L"(+ " + to_wstring(weapon.str + armor.str) + L")");
	chAbilDefFigure->SetStr(to_wstring(cInfo.def) + L"(+ " + to_wstring(weapon.def + armor.def) + L")");
	chAbilMgcFigure->SetStr(to_wstring(cInfo.mgc) + L"(+ " + to_wstring(weapon.mgc + armor.mgc) + L")");
	chAbilMDefFigure->SetStr(to_wstring(cInfo.mDef) + L"(+ " + to_wstring(weapon.mDef + armor.mDef) + L")");
	chAbilDexFigure->SetStr(to_wstring(cInfo.dex));
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
	if (!enabled) return;

	RECT rc = gameObject->GetComponent<RectTransform>()->GetScreenRect();

	if (MOUSE_CLICKED && PtInRect(&rc, POINT_MOUSE))
	{
		Notify(EVENT::EQUIP_CHANGE_CHARACTER_PANEL_CLICK);
		MOUSE_CLICKED = false;
	}
}
#pragma endregion ECCharacterPanel


#pragma region ECAbilityTabPanel
ECAbilityTabPanel::ECAbilityTabPanel()
	: Component((const Component_ID)typeid(ECAbilityTabPanel).name()) { }

void ECAbilityTabPanel::Update()
{
	if (!enabled) return;

	RECT rc = gameObject->GetComponent<RectTransform>()->GetScreenRect();

	if (MOUSE_CLICKED && PtInRect(&rc, POINT_MOUSE))
	{
		Notify(EVENT::EQUIP_CHANGE_ABILITY_TAB_PANEL_CLICK);
		MOUSE_CLICKED = false;
	}
}
#pragma endregion ECAbilityTabPanel


#pragma region ECEquipTabPanel
ECEquipTabPanel::ECEquipTabPanel()
	: Component((const Component_ID)typeid(ECEquipTabPanel).name()) { }

void ECEquipTabPanel::Update()
{
	if (!enabled) return;

	RECT rc = gameObject->GetComponent<RectTransform>()->GetScreenRect();

	if (MOUSE_CLICKED && PtInRect(&rc, POINT_MOUSE))
	{
		Notify(EVENT::EQUIP_CHANGE_EQUIP_TAB_PANEL_CLICK);
		MOUSE_CLICKED = false;
	}
}
#pragma endregion ECEquipTabPanel


#pragma region ECWeaponText
ECWeaponText::ECWeaponText()
	: Component((const Component_ID)typeid(ECWeaponText).name()) { }

void ECWeaponText::Update()
{
	if (!enabled) return;

	RECT rc = gameObject->GetComponent<RectTransform>()->GetScreenRect();

	if (MOUSE_CLICKED && PtInRect(&rc, POINT_MOUSE))
	{
		Notify(EVENT::EQUIP_CHANGE_EQUIP_WEAPON_TEXT_CLICK);
		MOUSE_CLICKED = false;
	}
}
#pragma endregion ECWeaponText


#pragma region ECArmorText
ECArmorText::ECArmorText()
	: Component((const Component_ID)typeid(ECArmorText).name()) { }

void ECArmorText::Update()
{
	if (!enabled) return;

	RECT rc = gameObject->GetComponent<RectTransform>()->GetScreenRect();

	if (MOUSE_CLICKED && PtInRect(&rc, POINT_MOUSE))
	{
		Notify(EVENT::EQUIP_CHANGE_EQUIP_ARMOR_TEXT_CLICK);
		MOUSE_CLICKED = false;
	}
}
#pragma endregion ECWeaponName


#pragma region ECEquipInInvenPanel
ECEquipInInvenPanel::ECEquipInInvenPanel()
	: Component((const Component_ID)typeid(ECEquipInInvenPanel).name()) { }

void ECEquipInInvenPanel::Update()
{
	if (!enabled) return;

	RECT rc = gameObject->GetComponent<RectTransform>()->GetScreenRect();

	if (MOUSE_CLICKED && PtInRect(&rc, POINT_MOUSE) &&
		equipId != EQUIP_ID::NONE && equipId != EQUIP_ID::EQUIP_ID_NUM
		)
	{
		Notify(EVENT::EQUIP_CHANGE_EQUIP_IN_INVEN_PANEL_CLICK);
		MOUSE_CLICKED = false;
	}
}

void ECEquipInInvenPanel::SetEquipId(EQUIP_ID _equipId)
{
	equipId = _equipId;

	if (_equipId != EQUIP_ID::NONE && _equipId != EQUIP_ID::EQUIP_ID_NUM)
		gameObject->GetComponent<RenderedText>()->SetStr(
			GAMEDATA->GetEquipInfo(equipId).name
		);
	else
		gameObject->GetComponent<RenderedText>()->SetStr(L"");
}
#pragma endregion ECEquipInInvenPanel


#pragma region ToShopListButton
ToShopListButton::ToShopListButton()
	: Component((const Component_ID)typeid(ToShopListButton).name()) { }

void ToShopListButton::Update()
{
	if (!enabled) return;

	RECT rc = gameObject->GetComponent<RectTransform>()->GetScreenRect();

	if (MOUSE_CLICKED && PtInRect(&rc, POINT_MOUSE))
	{
		Notify(EVENT::EQUIP_CHANGE_TO_SHOP_LIST_BUTTON_CLICK);
		MOUSE_CLICKED = false;
	}
}
#pragma endregion ToShopListButton


#pragma region EquipChangeButton
EquipChangeButton::EquipChangeButton()
	: Component((const Component_ID)typeid(EquipChangeButton).name()) { }

void EquipChangeButton::Update()
{
	if (!enabled) return;

	RECT rc = gameObject->GetComponent<RectTransform>()->GetScreenRect();

	if (MOUSE_CLICKED && PtInRect(&rc, POINT_MOUSE))
	{
		Notify(EVENT::EQUIP_CHANGE_EQUIP_CHANGE_BUTTON_CLICK);
		MOUSE_CLICKED = false;
	}
}
#pragma endregion EquipChangeButton

