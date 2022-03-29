#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedText/RenderedText.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

RenderedText::RenderedText()
	: Component((const Component_ID)typeid(RenderedText).name())
{
	str = L"";
}

RenderedText::~RenderedText() { }

void RenderedText::Operation() { }

void RenderedText::Render(HDC _hdc)
{
	if (enabled && str != L"")
	{
		RectTransform* rcT = gameObject->GetComponent<RectTransform>();
		if (rcT)
		{
			RECT rc = rcT->GetScreenRect();

			FONT->DrawText(_hdc, rc.left, rc.top, (wchar_t*)L"Arial", 24, 24, (wchar_t*)str.c_str(), (int)str.length(), RGB(15, 15, 15));
		}
	}
}
