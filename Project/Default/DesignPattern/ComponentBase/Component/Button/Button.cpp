#include "Stdafx/stdafx.h"

#include "Button.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#pragma region Button
Button::Button(wstring _str) : Component((const Component_ID)typeid(Button).name())
{
	callBack_v_CB_v = NULL;
	str = _str;
}

Button::~Button() { }

void Button::Operation() { }

void Button::Init() { }

void Button::Update()
{
	if (!enabled) return;

	if (MOUSE_CLICKED)
	{
		RectTransform* rcT = gameObject->GetComponent<RectTransform>();
		if (rcT == NULL) return;
		RECT rc = rcT->GetScreenRect();
		if (PtInRect(&rc, POINT_MOUSE) && callBack_v_CB_v)
			callBack_v_CB_v();
	}
}

void Button::LateUpdate() { }

void Button::SetCallBack_v_CB_v(std::function<void()> _callBack)
{
	callBack_v_CB_v = std::move(_callBack);
}
#pragma endregion Button
