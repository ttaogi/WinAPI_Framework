#pragma once

#include <functional>

#include "Utility/CommonClasses/CommonClasses.h"

class GameObject;
class Image;

#pragma region ProductBaseButton
class ProductBaseButton
{
private:
protected:
public:
	virtual GameObject* CreateObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"") = 0;
};
#pragma endregion ProductBaseButton


#pragma region ProductBaseBar
class ProductBaseBar
{
private:
protected:
public:
	virtual GameObject* CreateObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, int _margin, double _rate) = 0;
};
#pragma endregion ProductBaseBar


#pragma region ProductBasePlayer
class ProductBasePlayer
{
public:
	virtual GameObject* CreateObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe) = 0;
};
#pragma endregion ProductBasePlayer


#pragma region ProductBasePlatform
class ProductBasePlatform
{
public:
	virtual GameObject* CreateObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe) = 0;
};
#pragma endregion ProductBasePlatform
