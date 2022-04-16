#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedText/RenderedText.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

RenderedText::RenderedText()
	: Component((const Component_ID)typeid(RenderedText).name())
{
	str = L"";
	fontSize = 24;
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
			RECT rc;

			if (byCamera)	rc = rcT->GetScreenRectByCamera();
			else			rc = rcT->GetScreenRect();

			//FONT->DrawText(_hdc, rc.left, rc.top, (wchar_t*)L"Arial", fontSize, 24, (wchar_t*)str.c_str(), (int)str.length(), RGB(15, 15, 15));

			wstring tmp;
			vector<wstring> tokens;
			wstringstream wss(str);
			while (getline(wss, tmp, L'\n'))
				tokens.push_back(tmp);

			for(int i = 0; i < tokens.size(); ++i)
				FONT->DrawText(_hdc, rc.left, rc.top + i * fontSize, (wchar_t*)L"Arial", fontSize, 24, (wchar_t*)tokens[i].c_str(), (int)tokens[i].length(), RGB(15, 15, 15));
		}
	}
}

void RenderedText::SetStr(wstring _str)
{
	str = _str;
}
