#pragma once

#include "DesignPattern/FactoryBase/Factory.h"
#include "Utility/CommonClasses/CommonClasses.h"
#include "Utility/Enums/Enums.h"

#pragma region AbstractFactoryButton
class AbstractFactoryButton
{
private:
protected:
public:
	static GameObject* GetObject(BUTTON_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"");
};
#pragma endregion AbstractFactoryButton

#pragma region AbstractFactoryBar
class AbstractFactoryBar
{
public:
	static GameObject* GetObject(BAR_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, int _margin, double _rate);
};
#pragma endregion AbstractFactoryBar

#pragma region AbstractFactoryPlayer
class AbstractFactoryPlayer
{
public:
	static GameObject* GetObject(PLAYER_FACTORY_TYPE _type,
		D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe);
};
#pragma endregion AbstractFactoryPlayer

#pragma region AbstractFactoryPlatform
class AbstractFactoryPlatform
{
public:
	static GameObject* GetObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe);
};
#pragma endregion AbstractFactoryPlatform
