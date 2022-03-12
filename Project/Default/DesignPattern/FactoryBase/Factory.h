#pragma once

#include <functional>

#include "DesignPattern/SingletonBase/SingletonBase.h"
#include "Utility/CommonClasses/CommonClasses.h"

class GameObject;
class Image;

#pragma region ButtonFactory
class ButtonFactory : public SingletonBase<ButtonFactory>
{
private:
protected:
public:
	ButtonFactory();
	~ButtonFactory();

	GameObject* GetObject(std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"");
};
#pragma endregion ButtonFactory
