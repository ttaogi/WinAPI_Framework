#include "Stdafx/stdafx.h"

#include "AbstractFactoryBase.h"

#pragma region AbstractFactoryButton
AbstractFactoryButton::AbstractFactoryButton() { }

AbstractFactoryButton::~AbstractFactoryButton() { }

GameObject* AbstractFactoryButton::GetObject(
	BUTTON_FACTORY_TYPE _type,
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, Image* _image, std::wstring _str)
{
	GameObject* go = NULL;

	switch (_type)
	{
	case BUTTON_FACTORY_TYPE::DEFAULT:
		go = ButtonFactory::GetSingleton()
			->GetObject(_callBack_v_CB_v, _pos, _rectWidth, _rectHeight, _image, _str);
		break;
	}

	return go;
}
#pragma endregion AbstractFactoryButton
