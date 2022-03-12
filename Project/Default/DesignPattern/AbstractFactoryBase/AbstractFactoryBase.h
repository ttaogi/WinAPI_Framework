#pragma once

#include "DesignPattern/FactoryBase/Factory.h"
#include "Utility/CommonClasses/CommonClasses.h"
#include "Utility/Enums/Enums.h"

#pragma region AbstractFactoryButton
class AbstractFactoryButton : public SingletonBase<AbstractFactoryButton>
{
private:
protected:
public:
	AbstractFactoryButton();
	~AbstractFactoryButton();

	GameObject* GetObject(BUTTON_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v, D_POINT _pos,
		int _rectWidth, int _rectHeight, Image* _image, std::wstring _str = L"");
};
#pragma endregion AbstractFactoryButton
