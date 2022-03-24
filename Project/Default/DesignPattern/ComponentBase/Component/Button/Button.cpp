#include "Stdafx/stdafx.h"

#include "Button.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#pragma region Button
Button::Button(wstring _str)
	: Component((const Component_ID)typeid(Button).name())
{
	callBack_v_CB_v = NULL;
	str = _str;
}

Button::~Button() { }

void Button::Operation() { }

void Button::Init() { }

void Button::FixedUpdate() { }

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

void Button::OnCollision(Collision _col) { }

void Button::SetCallBack_v_CB_v(std::function<void()> _callBack)
{
	callBack_v_CB_v = std::move(_callBack);
}
#pragma endregion Button

#pragma region ButtonMouseOn
ButtonMouseOn::ButtonMouseOn(std::wstring _str)
	: Component((const Component_ID)typeid(ButtonMouseOn).name())
{
	callBack_v_CB_v = NULL;
	str = _str;
}

ButtonMouseOn::~ButtonMouseOn() { }

void ButtonMouseOn::Operation() { }

void ButtonMouseOn::Init() { }

void ButtonMouseOn::FixedUpdate() { }

void ButtonMouseOn::Update()
{
	if (!enabled) return;

	RenderedImage* rImg = gameObject->GetComponent<RenderedImage>();
	RectTransform* rcT = gameObject->GetComponent<RectTransform>();
	if (rcT == NULL) return;
	RECT rc = rcT->GetScreenRect();

	if (rImg)
		if (PtInRect(&rc, POINT_MOUSE)) rImg->SetEnabled(true);
		else rImg->SetEnabled(false);

	if (MOUSE_CLICKED)
		if (PtInRect(&rc, POINT_MOUSE) && callBack_v_CB_v)
			callBack_v_CB_v();
}

void ButtonMouseOn::LateUpdate() { }

void ButtonMouseOn::OnCollision(Collision _col) { }
#pragma endregion ButtonMouseOn
