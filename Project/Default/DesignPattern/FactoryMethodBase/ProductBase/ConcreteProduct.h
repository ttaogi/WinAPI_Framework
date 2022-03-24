#pragma once

#include "DesignPattern/FactoryMethodBase/ProductBase/ProductBase.h"

#pragma region ProductBaseButton
class FactoryDefaultButton : public ProductBaseButton
{
private:
protected:
public:
	virtual GameObject* CreateObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"") override;
};

class FactoryButtonMouseOn : public ProductBaseButton
{
private:
protected:
public:
	virtual GameObject* CreateObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"") override;
};
#pragma endregion ProductBaseButton


#pragma region ProductBaseBar
class FactoryDefaultBar : public ProductBaseBar
{
private:
protected:
public:
	virtual GameObject* CreateObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, int _margin, double _rate) override;
};
#pragma endregion ProductBaseBar


#pragma region ProductBasePlayer
class FactoryDefaultPlayer : public ProductBasePlayer
{
public:
	virtual GameObject* CreateObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite) override;
};
#pragma endregion ProductBasePlayer


#pragma region ProductBasePlatform
class FactoryDefaultPlatform : public ProductBasePlatform
{
public:
	virtual GameObject* CreateObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite) override;
};
#pragma endregion ProductBasePlatform
