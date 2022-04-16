#pragma once

#include <functional>

#include "DesignPattern/ObserverBase/Observer.h"
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


#pragma region FactoryMethodBasePlayer
class FactoryMethodBasePlayer
{
public:
	virtual GameObject* CreateObject(CHARACTER_ID _id,
		Observer* _observer, D_POINT _pos, POINT _gridPos) = 0;
};
#pragma endregion FactoryMethodBasePlayer


#pragma region FactoryMethodBaseEnemy
class FactoryMethodBaseEnemy
{
public:
	virtual GameObject* CreateObject(ENEMY_TYPE _type,
		Observer* _observer, D_POINT _pos, POINT _gridPos) = 0;
};
#pragma endregion FactoryMethodBaseEnemy


#pragma region FactoryMethodBaseDialogViewer
class FactoryMethodBaseDialogViewer
{
public:
	virtual GameObject* CreateObject(Observer* _observer, std::wstring _spot, int _processivity) = 0;
};
#pragma endregion FactoryMethodBaseDialogViewer


#pragma region FactoryMethodBaseShopList
class FactoryMethodBaseShopList
{
public:
	virtual GameObject* CreateObject(Observer* _observer) = 0;
};
#pragma endregion FactoryMethodBaseShopList


#pragma region FactoryMethodBaseEquipChange
class FactoryMethodBaseEquipChange
{
public:
	virtual GameObject* CreateObject(Observer* _observer) = 0;
};
#pragma endregion FactoryMethodBaseEquipChange


#pragma region FactoryMethodBaseTile
class FactoryMethodBaseTile
{
public:
	virtual GameObject* CreateObject(TILE_TYPE _type, Observer* _observer, POINT _gridPos) = 0;
};
#pragma endregion FactoryMethodBaseTile


#pragma region FactoryMethodBaseEffect
class FactoryMethodBaseEffect
{
public:
	virtual GameObject* CreateObject(EFFECT_FACTORY_TYPE _type, POINT _gridPos) = 0;
};
#pragma endregion FactoryMethodBaseEffect


#pragma region FactoryMethodBaseHpBar
class FactoryMethodBaseHpBar
{
public:
	virtual GameObject* CreateObject() = 0;
};
#pragma endregion FactoryMethodBaseHpBar
