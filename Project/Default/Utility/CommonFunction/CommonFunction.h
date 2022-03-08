#pragma once

class Component;
class MonoBehaviour;
class RenderedImage;

inline RECT MakeRectCWH(POINT _pos, int _width, int _height)
{
	return RECT{ _pos.x - _width / 2, _pos.y - _height / 2, _pos.x + _width / 2, _pos.y + _height / 2 };
}

inline void PaintRect(HDC _hdc, RECT _rc)
{
	Rectangle(_hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

bool PointEqual(POINT pos1, POINT pos2);

MonoBehaviour* IsDerivedFromMonoBehaviour(Component* _c);

std::string WcsToMbsKorean(std::wstring const& _wstr);
std::string WcsToMbsUtf8(std::wstring const& _wstr);
std::wstring MbsUtf8ToWcs(std::string const& _str);
