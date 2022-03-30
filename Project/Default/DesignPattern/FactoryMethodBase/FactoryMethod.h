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


#pragma region FactoryMethodBar
class FactoryMethodBar : public FactoryMethodBaseBar, public SingletonBase<FactoryMethodBar>
{
private:
	FactoryDefaultBar* defaultBar;
public:
	FactoryMethodBar();
	virtual ~FactoryMethodBar();

	virtual GameObject* CreateObject(BAR_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, int _margin, double _rate) override;
};
#pragma endregion FactoryMethodBar


#pragma region FactoryMethodPlayer
class FactoryMethodPlayer : public FactoryMethodBasePlayer, public SingletonBase<FactoryMethodPlayer>
{
private:
	FactoryDefaultPlayer* defaultPlayer;
public:
	FactoryMethodPlayer();
	virtual ~FactoryMethodPlayer();

	virtual GameObject* CreateObject(PLAYER_FACTORY_TYPE _type,
		D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite) override;
};
#pragma endregion FactoryMethodPlayer


#pragma region FactoryMethodPlatform
class FactoryMethodPlatform : public FactoryMethodBasePlatform, public SingletonBase<FactoryMethodPlatform>
{
private:
	FactoryDefaultPlatform* defaultPlatform;
public:
	FactoryMethodPlatform();
	virtual ~FactoryMethodPlatform();

	virtual GameObject* CreateObject(PLATFORM_FACTORY_TYPE _type,
		D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite) override;
};
#pragma endregion FactoryMethodPlatform


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
