#pragma once

#include "DesignPattern/FactoryMethodBase/ProductBase/ConcreteProduct.h"
#include "DesignPattern/FactoryMethodBase/FactoryMethodBase.h"
#include "DesignPattern/SingletonBase/SingletonBase.h"

#pragma region FactoryMethodButton
class FactoryMethodButton : public FactoryMethodBaseButton, public SingletonBase<FactoryMethodButton>
{
private:
	FactoryDefaultButton* defaultButton;
	FactoryButtonMouseOn* buttonMouseOn;
public:
	FactoryMethodButton();
	virtual ~FactoryMethodButton();

	virtual GameObject* CreateObject(BUTTON_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"") override;
};
#pragma endregion FactoryMethodButton


#pragma region FactoryMethodPlayer
class FactoryMethodPlayer : public FactoryMethodBasePlayer, public SingletonBase<FactoryMethodPlayer>
{
private:
	FactoryPlayerAl* al;
	FactoryPlayerKarin* karin;
public:
	FactoryMethodPlayer();
	virtual ~FactoryMethodPlayer();

	virtual GameObject* CreateObject(CHARACTER_ID _id,
		Observer* _observer, D_POINT _pos, POINT _gridPos) override;
};
#pragma endregion FactoryMethodPlayer


#pragma region FactoryMethodEnemy
class FactoryMethodEnemy : public FactoryMethodBaseEnemy, public SingletonBase<FactoryMethodEnemy>
{
private:
	FactoryEnemySlime* slime;
public:
	FactoryMethodEnemy();
	virtual ~FactoryMethodEnemy();

	virtual GameObject* CreateObject(ENEMY_TYPE _type,
		Observer* _observer, D_POINT _pos, POINT _gridPos) override;
};
#pragma endregion FactoryMethodEnemy


#pragma region FactoryMethodDialogViewer
class FactoryMethodDialogViewer : public FactoryMethodBaseDialogViewer, public SingletonBase<FactoryMethodDialogViewer>
{
private:
	FactoryDefaultDialogViewer* defaultDialogViewer;
public:
	FactoryMethodDialogViewer();
	virtual ~FactoryMethodDialogViewer();

	virtual GameObject* CreateObject(Observer* _observer, std::wstring _spot, int _processivity) override;
};
#pragma endregion FactoryMethodDialogViewer


#pragma region FactoryMethodShopList
class FactoryMethodShopList : public FactoryMethodBaseShopList, public SingletonBase<FactoryMethodShopList>
{
private:
	FactoryDefaultShopList* defaultShopList;
public:
	FactoryMethodShopList();
	virtual ~FactoryMethodShopList();

	virtual GameObject* CreateObject(Observer* _observer) override;
};
#pragma endregion FactoryMethodShopList


#pragma region FactoryMethodEquipChange
class FactoryMethodEquipChange : public FactoryMethodBaseEquipChange, public SingletonBase< FactoryMethodEquipChange>
{
private:
	FactoryDefaultEquipChange* defaultEquipChange;
public:
	FactoryMethodEquipChange();
	virtual ~FactoryMethodEquipChange();

	virtual GameObject* CreateObject(Observer* _observer) override;
};
#pragma endregion FactoryMethodEquipChange


#pragma region FactoryMethodBaseTile
class FactoryMethodTile : public FactoryMethodBaseTile, public SingletonBase<FactoryMethodTile>
{
private:
	FactoryDefaultTile* defaultTile;
public:
	FactoryMethodTile();
	virtual ~FactoryMethodTile();

	virtual GameObject* CreateObject(TILE_TYPE _type, Observer* _observer, POINT _gridPos) override;
};
#pragma endregion FactoryMethodBaseTile


#pragma region FactoryMethodBaseEffect
class FactoryMethodEffect : public FactoryMethodBaseEffect, public SingletonBase<FactoryMethodEffect>
{
private:
	FactoryEffectFlameBurst* flameBurst;
public:
	FactoryMethodEffect();
	virtual ~FactoryMethodEffect();

	virtual GameObject* CreateObject(EFFECT_FACTORY_TYPE _type, POINT _gridPos);
};
#pragma endregion FactoryMethodBaseEffect


#pragma region FactoryMethodBaseHpBar
class FactoryMethodHpBar : public FactoryMethodBaseHpBar, public SingletonBase<FactoryMethodHpBar>
{
private:
	FactoryHpBar* hpBar;
public:
	FactoryMethodHpBar();
	virtual ~FactoryMethodHpBar();

	virtual GameObject* CreateObject();
};
#pragma endregion FactoryMethodBaseHpBar
