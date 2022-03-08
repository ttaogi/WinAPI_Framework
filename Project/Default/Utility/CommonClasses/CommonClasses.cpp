#include "Stdafx/stdafx.h"

#include "CommonClasses.h"

#pragma region	D_POINT
D_POINT& D_POINT::operator = (const POINT& _p)
{
	x = (double)_p.x;
	y = (double)_p.y;
	return *this;
}

D_POINT D_POINT::operator + (const D_POINT& _p)
{
	return D_POINT{ x + _p.x , y + _p.y };
}

D_POINT D_POINT::operator - (const D_POINT& _p)
{
	return D_POINT{ x - _p.x, y - _p.y };
}

D_POINT D_POINT::operator * (const double& _f)
{
	return D_POINT{ x * _f, y * _f };
}

D_POINT D_POINT::operator / (const double& _f)
{
	return D_POINT{ x / _f, y / _f };
}

POINT D_POINT::ToPoint() const
{
	return POINT{ (LONG)x, (LONG)y };
}

double D_POINT::Length() const
{
	return sqrt(x * x + y * y);
}
#pragma endregion	D_POINT


#pragma region	VELOCITY
VELOCITY& VELOCITY::operator = (const D_POINT& _p)
{
	x = _p.x;
	y = _p.y;
	return *this;
}

VELOCITY VELOCITY::operator + (const VELOCITY& _p)
{
	return VELOCITY{ x + _p.x, y + _p.y };
}

VELOCITY VELOCITY::operator - (const VELOCITY& _p)
{
	return VELOCITY{ x - _p.x, y - _p.y };
}

VELOCITY VELOCITY::operator * (const double& _f)
{
	return VELOCITY{ x * _f, y * _f };
}

VELOCITY VELOCITY::operator / (const double& _f)
{
	return VELOCITY{ x / _f, y / _f };
}

void VELOCITY::Accelerate(D_POINT _acc)
{
	x += _acc.x;
	y += _acc.y;
}

void VELOCITY::AddG()
{
	Accelerate(D_POINT{ 0, GRAVITY });
}

D_POINT VELOCITY::ToFPoint() const
{
	return D_POINT{ x, y };
}

double VELOCITY::Length() const
{
	return sqrt(x * x + y * y);
}
#pragma endregion	VELOCITY

