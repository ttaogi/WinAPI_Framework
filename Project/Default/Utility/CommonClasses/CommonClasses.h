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

	VELOCITY& operator = (const D_POINT& _p);
	VELOCITY operator + (const VELOCITY& _p);
	VELOCITY operator - (const VELOCITY& _p);
	VELOCITY operator * (const double& _d);
	VELOCITY operator / (const double& _d);

	void Accelerate(D_POINT _acc);

	D_POINT ToDPoint() const;
	double Length() const;
};
