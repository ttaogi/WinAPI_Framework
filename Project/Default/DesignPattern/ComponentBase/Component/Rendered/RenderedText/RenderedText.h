#pragma once

#include "DesignPattern/ComponentBase/Component/Rendered/Rendered.h"

class RenderedText : public Rendered
{
private:
	std::wstring str;
public:
	RenderedText();
	virtual ~RenderedText();

	virtual void Operation() override;

	virtual void Render(HDC _hdc);

	std::wstring GetStr() const { return str; }
	void SetStr(std::wstring _str) { str = _str; }
};