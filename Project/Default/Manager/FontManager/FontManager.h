#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class FontManager : public SingletonBase<FontManager>
{
public:
	FontManager() {}
	virtual ~FontManager() {}

	void DrawText(
		HDC _hdc, int _destX, int _destY, wchar_t* _fontName,
		int _fontSize, int _fontWidth, wchar_t* _printString,
		int _length, COLORREF _color);
};