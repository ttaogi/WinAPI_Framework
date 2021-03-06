#include "Stdafx/stdafx.h"

#include "DesignPattern/FactoryMethodBase/FactoryMethod.h"

#include "DesignPattern/FactoryMethodBase/ProductBase/ConcreteProduct.h"

#pragma region FactoryMethodButton
FactoryMethodButton::FactoryMethodButton()
{
	defaultButton = new FactoryDefaultButton();
	buttonMouseOn = new FactoryButtonMouseOn();
}

FactoryMethodButton::~FactoryMethodButton()
{
	SAFE_DELETE(defaultButton);
	SAFE_DELETE(buttonMouseOn);
}

GameObject* FactoryMethodButton::CreateObject(
	BUTTON_FACTORY_TYPE _type,
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, Image* _image, std::wstring _str)
{
	GameObject* go = NULL;

	switch (_type)
	{
	case BUTTON_FACTORY_TYPE::DEFAULT:
		go = defaultButton->CreateObject(_callBack_v_CB_v, _pos, _rectWidth, _rectHeight, _image, _str);
		break;
	case BUTTON_FACTORY_TYPE::MOUSE_ON:
		go = buttonMouseOn->CreateObject(_callBack_v_CB_v, _pos, _rectWidth, _rectHeight, _image, _str);
		break;
	}

	return go;
}
#pragma endregion FactoryMethodButton


#pragma region FactoryMethodPlayer
FactoryMethodPlayer::FactoryMethodPlayer()
{
	al = new FactoryPlayerAl();
	karin = new FactoryPlayerKarin();
}

FactoryMethodPlayer::~FactoryMethodPlayer()
{
	SAFE_DELETE(al);
	SAFE_DELETE(karin);
}

GameObject* FactoryMethodPlayer::CreateObject(CHARACTER_ID _id, Observer* _observer, D_POINT _pos, POINT _gridPos)
{
	GameObject* go = NULL;

	switch (_id)
	{
	case CHARACTER_ID::AL:
		go = al->CreateObject(_observer, _pos, _gridPos);
		break;
	case CHARACTER_ID::KARIN:
		go = karin->CreateObject(_observer, _pos, _gridPos);
		break;
	}

	return go;
}
#pragma endregion FactoryMethodPlayer


#pragma region FactoryMethodEnemy
FactoryMethodEnemy::FactoryMethodEnemy()
{
	slime = new FactoryEnemySlime();
}

FactoryMethodEnemy::~FactoryMethodEnemy()
{
	SAFE_DELETE(slime);
}

GameObject* FactoryMethodEnemy::CreateObject(ENEMY_TYPE _type, Observer* _observer, D_POINT _pos, POINT _gridPos)
{
	GameObject* go = NULL;

	switch(_type)
	{
	case ENEMY_TYPE::SLIME:
		go = slime->CreateObject(_observer, _pos, _gridPos);
		break;
	}

	return go;
}
#pragma endregion FactoryMethodEnemy


#pragma region FactoryMethodDialogViewer
FactoryMethodDialogViewer::FactoryMethodDialogViewer()
{
	defaultDialogViewer = new FactoryDefaultDialogViewer();
}

FactoryMethodDialogViewer::~FactoryMethodDialogViewer()
{
	SAFE_DELETE(defaultDialogViewer);
}

GameObject* FactoryMethodDialogViewer::CreateObject(Observer* _observer, std::wstring _spot, int _processivity)
{
	GameObject* go = NULL;

	go = defaultDialogViewer->CreateObject(_observer, _spot, _processivity);

	return go;
}
#pragma endregion FactoryMethodDialogViewer


#pragma region FactoryMethodShopList
FactoryMethodShopList::FactoryMethodShopList()
{
	defaultShopList = new FactoryDefaultShopList();
}

FactoryMethodShopList::~FactoryMethodShopList()
{
	SAFE_DELETE(defaultShopList);
}

GameObject* FactoryMethodShopList::CreateObject(Observer* _observer)
{
	GameObject* go = NULL;
	
	go = defaultShopList->CreateObject(_observer);

	return go;
}
#pragma endregion FactoryMethodShopList


#pragma region FactoryMethodEquipChange
FactoryMethodEquipChange::FactoryMethodEquipChange()
{
	defaultEquipChange = new FactoryDefaultEquipChange();
}

FactoryMethodEquipChange::~FactoryMethodEquipChange()
{
	SAFE_DELETE(defaultEquipChange);
}

GameObject* FactoryMethodEquipChange::CreateObject(Observer* _observer)
{
	GameObject* go = NULL;

	go = defaultEquipChange->CreateObject(_observer);

	return go;
}
#pragma endregion FactoryMethodEquipChange


#pragma region FactoryMethodBaseTile
FactoryMethodTile::FactoryMethodTile()
{
	defaultTile = new FactoryDefaultTile();
}

FactoryMethodTile::~FactoryMethodTile()
{
	SAFE_DELETE(defaultTile);
}

GameObject* FactoryMethodTile::CreateObject(TILE_TYPE _type, Observer* _observer, POINT _gridPos)
{
	GameObject* go = NULL;

	go = defaultTile->CreateObject(_type, _observer, _gridPos);

	return go;
}
#pragma endregion FactoryMethodBaseTile


#pragma region FactoryMethodBaseEffect
FactoryMethodEffect::FactoryMethodEffect()
{
	flameBurst = new FactoryEffectFlameBurst();
}

FactoryMethodEffect::~FactoryMethodEffect()
{
	SAFE_DELETE(flameBurst);
}

GameObject* FactoryMethodEffect::CreateObject(EFFECT_FACTORY_TYPE _type, POINT _gridPos)
{
	GameObject* go = NULL;

	switch (_type)
	{
	case EFFECT_FACTORY_TYPE::FLAME_BURST:
		go = flameBurst->CreateObject(_gridPos);
		break;
	}

	return go;
}
#pragma endregion FactoryMethodBaseEffect


#pragma region FactoryMethodBaseHpBar
FactoryMethodHpBar::FactoryMethodHpBar()
{
	hpBar = new FactoryHpBar();
}

FactoryMethodHpBar::~FactoryMethodHpBar()
{
	SAFE_DELETE(hpBar);
}

GameObject* FactoryMethodHpBar::CreateObject()
{
	GameObject* go = NULL;

	go = hpBar->CreateObject();

	return go;
}
#pragma endregion FactoryMethodBaseHpBar

