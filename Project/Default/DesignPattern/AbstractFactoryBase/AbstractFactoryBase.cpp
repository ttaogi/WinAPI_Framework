#include "Stdafx/stdafx.h"

#include "AbstractFactoryBase.h"

#pragma region AbstractFactoryButton
GameObject* AbstractFactoryButton::GetObject(
	BUTTON_FACTORY_TYPE _type,
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, Image* _image, std::wstring _str)
{
	GameObject* go = NULL;

	switch (_type)
	{
	case BUTTON_FACTORY_TYPE::DEFAULT:
		go = ButtonFactory::GetObject(_callBack_v_CB_v, _pos, _rectWidth, _rectHeight, _image, _str);
		break;
	}

	return go;
}
#pragma endregion AbstractFactoryButton

#pragma region AbstractFactoryBar
GameObject* AbstractFactoryBar::GetObject(
	BAR_FACTORY_TYPE _type,
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, int _margin, double _rate)
{
	GameObject* go = NULL;

	switch (_type)
	{
	case BAR_FACTORY_TYPE::DEFAULT:
		go = BarFactory::GetObject(_callBack_v_CB_v, _pos, _rectWidth, _rectHeight, _margin, _rate);
		break;
	}

	return go;
}
#pragma endregion AbstractFactoryBar

#pragma region AbstractFactoryPlayer
GameObject* AbstractFactoryPlayer::GetObject(PLAYER_FACTORY_TYPE _type, D_POINT _pos, int _rectWidth, int _rectHeight, Image * _stripe)
{
	GameObject* go = NULL;

	switch (_type)
	{
	case PLAYER_FACTORY_TYPE::DEFAULT:
		go = PlayerFactory::GetObject(_pos, _rectWidth, _rectHeight, _stripe);
		break;
	}

	return go;
}
#pragma endregion AbstractFactoryPlayer

#pragma region AbstractFactoryPlatform
GameObject* AbstractFactoryPlatform::GetObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe)
{
	GameObject* go = NULL;

	go = PlatformFactory::GetObject(_pos, _rectWidth, _rectHeight, _stripe);

	return go;
}
#pragma endregion AbstractFactoryPlatform
