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


#pragma region FactoryMethodBar
FactoryMethodBar::FactoryMethodBar()
{
	defaultBar = new FactoryDefaultBar();
}

FactoryMethodBar::~FactoryMethodBar()
{
	SAFE_DELETE(defaultBar);
}

GameObject* FactoryMethodBar::CreateObject(
	BAR_FACTORY_TYPE _type,
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, int _margin, double _rate)
{
	GameObject* go = NULL;

	switch (_type)
	{
	case BAR_FACTORY_TYPE::DEFAULT:
		go = defaultBar->CreateObject(_callBack_v_CB_v, _pos, _rectWidth, _rectHeight, _margin, _rate);
		break;
	}

	return go;
}
#pragma endregion FactoryMethodBar


#pragma region FactoryMethodPlayer
FactoryMethodPlayer::FactoryMethodPlayer()
{
	defaultPlayer = new FactoryDefaultPlayer();
}

FactoryMethodPlayer::~FactoryMethodPlayer()
{
	SAFE_DELETE(defaultPlayer);
}

GameObject* FactoryMethodPlayer::CreateObject(PLAYER_FACTORY_TYPE _type, D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite)
{
	GameObject* go = NULL;

	switch (_type)
	{
	case PLAYER_FACTORY_TYPE::DEFAULT:
		go = defaultPlayer->CreateObject(_pos, _rectWidth, _rectHeight, _sprite);
		break;
	}

	return go;
}
#pragma endregion FactoryMethodPlayer


#pragma region FactoryMethodPlatform
FactoryMethodPlatform::FactoryMethodPlatform()
{
	defaultPlatform = new FactoryDefaultPlatform();
}

FactoryMethodPlatform::~FactoryMethodPlatform()
{
	SAFE_DELETE(defaultPlatform);
}

GameObject* FactoryMethodPlatform::CreateObject(PLATFORM_FACTORY_TYPE _type, D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite)
{
	GameObject* go = NULL;

	switch(_type)
	{
	case PLATFORM_FACTORY_TYPE::DEFAULT:
		go = defaultPlatform->CreateObject(_pos, _rectWidth, _rectHeight, _sprite);
		break;
	}

	return go;
}
#pragma endregion FactoryMethodPlatform


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
