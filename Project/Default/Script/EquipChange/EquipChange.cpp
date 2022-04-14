#include "Stdafx/stdafx.h"

#include "Script/EquipChange/EquipChange.h"

#pragma region EquipChange
EquipChange::EquipChange()
	: Component((const Component_ID)typeid(EquipChange).name()) { }

void EquipChange::Update()
{
}

void EquipChange::OnNotify(Subject* _subject, EVENT _event)
{
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

