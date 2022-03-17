#pragma once

#include "DesignPattern/FactoryMethodBase/ProductBase/ConcreteProduct.h"
#include "DesignPattern/FactoryMethodBase/FactoryMethodBase.h"
#include "DesignPattern/SingletonBase/SingletonBase.h"

#pragma region FactoryMethodButton
class FactoryMethodButton : public FactoryMethodBaseButton, public SingletonBase<FactoryMethodButton>
{
private:
	FactoryDefaultButton* defaultButton;
protected:
	virtual ~FactoryMethodButton();
public:
	FactoryMethodButton();

	GameObject* CreateObject(BUTTON_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"");
};
#pragma endregion FactoryMethodButton


#pragma region FactoryMethodBar
class FactoryMethodBar : public FactoryMethodBaseBar, public SingletonBase<FactoryMethodBar>
{
private:
	FactoryDefaultBar* defaultBar;
protected:
	virtual ~FactoryMethodBar();
public:
	FactoryMethodBar();

	GameObject* CreateObject(BAR_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, int _margin, double _rate);
};
#pragma endregion FactoryMethodBar


#pragma region FactoryMethodPlayer
class FactoryMethodPlayer : public FactoryMethodBasePlayer, public SingletonBase<FactoryMethodPlayer>
{
private:
	FactoryDefaultPlayer* defaultPlayer;
protected:
	virtual ~FactoryMethodPlayer();
public:
	FactoryMethodPlayer();

	GameObject* CreateObject(PLAYER_FACTORY_TYPE _type,
		D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe);
};
#pragma endregion FactoryMethodPlayer


#pragma region FactoryMethodPlatform
class FactoryMethodPlatform : public FactoryMethodBasePlatform, public SingletonBase<FactoryMethodPlatform>
{
private:
	FactoryDefaultPlatform* defaultPlatform;
protected:
	virtual ~FactoryMethodPlatform();
public:
	FactoryMethodPlatform();

	GameObject* CreateObject(PLATFORM_FACTORY_TYPE _type,
		D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe);
};
#pragma endregion FactoryMethodPlatform
