#pragma once

#include <functional>

#include "Utility/CommonClasses/CommonClasses.h"

class GameObject;
class Image;

#pragma region FactoryButton
class ButtonFactory
{
private:
protected:
public:
	static GameObject* GetObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"");
};
#pragma endregion FactoryButton

#pragma region FactoryBar
class BarFactory
{
private:
protected:
public:
	static GameObject* GetObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, int _margin, double _rate);
};
#pragma endregion FactoryBar

#pragma region FactoryPlayer
class PlayerFactory
{
public:
	static GameObject* GetObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe);
};
#pragma endregion FactoryPlayer

#pragma region FactoryPlatform
class PlatformFactory
{
public:
	static GameObject* GetObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe);
};
#pragma endregion FactoryPlatform
