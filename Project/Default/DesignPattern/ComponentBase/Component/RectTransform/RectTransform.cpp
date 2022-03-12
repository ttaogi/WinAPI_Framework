#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

RectTransform::RectTransform()
	: Component((const Component_ID)typeid(RectTransform).name())
{
	width = height = 0;
}

void RectTransform::Operation() { }

RECT RectTransform::GetScreenRect() const
{
	Transform* t = NULL;

	if (gameObject == NULL)
		return RECT{ 0, 0, 0, 0 };

	t = gameObject->GetComponent<Transform>();
	if (t == NULL)
		return RECT{ 0, 0, 0, 0 };

	POINT pos = t->GetPosition().ToPoint();

	long left = pos.x - width / 2;
	long top = pos.y - height / 2;

	return RECT{ left, top, left + width, top + height };
}
