#pragma once

#include <functional>

#include "Utility/CommonClasses/CommonClasses.h"
#include "Utility/Enums/Enums.h"

class GameObject;
class Image;
class Observer;

#pragma region ProductBaseButton
class ProductBaseButton
{
public:
	virtual GameObject* CreateObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"") = 0;
};
#pragma endregion ProductBaseButton


#pragma region ProductBasePlayer
class ProductBasePlayer
{
public:
	virtual GameObject* CreateObject(Observer* _observer, D_POINT _pos, POINT _gridPos) = 0;
};
#pragma endregion ProductBasePlayer


#pragma region ProductBaseEnemy
class ProductBaseEnemy
{
public:
	virtual GameObject* CreateObject(Observer* _observer, D_POINT _pos, POINT _gridPos) = 0;
};
#pragma endregion ProductBaseEnemy


#pragma region ProductBaseDialogViewer
class ProductBaseDialogViewer
{
public:
	virtual GameObject* CreateObject(Observer* _observer, std::wstring _spot, int _processivity) = 0;
};
#pragma endregion ProductBaseDialogViewer


#pragma region ProductBaseShopList
class ProductBaseShopList
{
public:
	virtual GameObject* CreateObject(Observer* _observer) = 0;
};
#pragma endregion ProductBaseShopList


#pragma region ProductBaseEquipChange
class ProductBaseEquipChange
{
public:
	virtual GameObject* CreateObject(Observer* _observer) = 0;
};
#pragma endregion ProductBaseEquipChange


#pragma region ProductBaseTile
class ProductBaseTile
{
public:
	virtual GameObject* CreateObject(TILE_TYPE _type, Observer* _observer, POINT _gridPos) = 0;
};
#pragma endregion ProductBaseTile


#pragma region ProductBaseEffect
class ProductBaseEffect
{
public:
	virtual GameObject* CreateObject(POINT _gridPos) = 0;
};
#pragma endregion ProductBaseEffect


#pragma region ProductBaseHpBar
class ProductBaseHpBar
{
public:
	virtual GameObject* CreateObject() = 0;
};
#pragma endregion ProductBaseHpBar
