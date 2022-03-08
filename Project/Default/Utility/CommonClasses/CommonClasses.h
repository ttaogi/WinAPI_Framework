#pragma once

struct D_POINT
{
	double x;
	double y;

	D_POINT& operator = (const POINT& _p);
	D_POINT operator + (const D_POINT& _p);
	D_POINT operator - (const D_POINT& _p);
	D_POINT operator * (const double& _f);
	D_POINT operator / (const double& _f);

	POINT ToPoint() const;
	double Length() const;
};

struct VELOCITY
{
	double x;
	double y;

	void SetX(double _speed) { x = _speed; }
	double GetX() const { return x; }
	void SetY(double _speed) { y = _speed; }
	double GetY() const { return y; }

	VELOCITY& operator = (const D_POINT& _p);
	VELOCITY operator + (const VELOCITY& _p);
	VELOCITY operator - (const VELOCITY& _p);
	VELOCITY operator * (const double& _f);
	VELOCITY operator / (const double& _f);

	void Accelerate(D_POINT _acc);
	void AddG();

	D_POINT ToFPoint() const;
	double Length() const;
};
