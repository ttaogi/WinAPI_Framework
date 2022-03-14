#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Bar/Bar.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

Bar::Bar()
	: Component((const Component_ID)typeid(Bar).name())
{
	rate = 0;
	callBack_v_CB_v = NULL;
}

Bar::~Bar() { }

void Bar::Operation() { }

void Bar::Init() { }

void Bar::FixedUpdate() { }

void Bar::Update()
{
	if (!enabled) return;

	if (MOUSE_CLICKED)
	{
		RectTransform* rcT = gameObject->GetComponent<RectTransform>();
		if (rcT == NULL) return;
		RECT rc = rcT->GetScreenRect();
		if (PtInRect(&rc, POINT_MOUSE) && callBack_v_CB_v)
		{
			int width = rc.right - rc.left;
			rate = (double)(POINT_MOUSE.x - rc.left) / width;
			callBack_v_CB_v();
		}
	}
}

void Bar::LateUpdate() { }

void Bar::OnCollision(Collision _col) { }

void Bar::SetRate(double _rate)
{
	GameObject* guage = gameObject->GetGameObjectByName(SKIG_BAR_GUAGE);
	GameObject* Background = gameObject->GetGameObjectByName(SKIG_BAR_BACKGROUND);

	if (guage && Background)
	{
		long newWidth, fullWidth;
		fullWidth = Background->GetComponent<RectTransform>()->GetWidth();
		newWidth = (long)(fullWidth * _rate);

		D_POINT newPos;
		D_POINT barPos = Background->GetComponent<Transform>()->GetPosition();
		newPos.y = barPos.y;
		newPos.x = barPos.x - (fullWidth - newWidth) / 2;

		rate = _rate;
		guage->GetComponent<Transform>()->SetPosition(newPos);
		guage->GetComponent<RectTransform>()->SetWidth(newWidth);
	}
}
