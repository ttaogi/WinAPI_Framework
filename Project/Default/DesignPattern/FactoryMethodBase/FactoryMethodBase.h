#pragma once

#include <functional>

#include "Utility/CommonClasses/CommonClasses.h"
#include "Utility/Enums/Enums.h"

class GameObject;
class Image;

#pragma region FactoryMethodBaseButton
class FactoryMethodBaseButton
{
public:
	virtual GameObject* CreateObject(BUTTON_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"") = 0;
};
#pragma endregion FactoryMethodBaseButton


#pragma region FactoryMethodBaseBar
class FactoryMethodBaseBar
{
public:
	virtual GameObject* CreateObject(BAR_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, int _margin, double _rate) = 0;
};
#pragma endregion FactoryMethodBaseBar


#pragma region FactoryMethodBasePlayer
class FactoryMethodBasePlayer
{
public:
	virtual GameObject* CreateObject(PLAYER_FACTORY_TYPE _type,
		D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite) = 0;
};
#pragma endregion FactoryMethodBasePlayer


#pragma region FactoryMethodBasePlatform
class FactoryMethodBasePlatform
{
public:
	virtual GameObject* CreateObject(PLATFORM_FACTORY_TYPE _type,
		D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite) = 0;
};
#pragma endregion FactoryMethodBasePlatform
