#pragma once

#include "DesignPattern/ComponentBase/Component/Component.h"

class RectTransform : public Component
{
private:
	long width;
	long height;
protected:
public:
	RectTransform();
	virtual ~RectTransform() { };

	virtual void Operation() override;

	RECT GetRect() const { return RECT{ 0, 0, width, height }; }
	void SetRect(long _width, long _height) { width = _width; height = _height; }
	void SetRect(RECT _rect)
	{
		width = _rect.right - _rect.left;
		height = _rect.bottom - _rect.top;
	}
	RECT GetScreenRect() const;
	long GetWidth() const { return width; }
	void SetWidth(long _width) { width = _width; }
	long GetHeight() const { return height; }
	void SetHeight(long _height) { height = _height; }
};
