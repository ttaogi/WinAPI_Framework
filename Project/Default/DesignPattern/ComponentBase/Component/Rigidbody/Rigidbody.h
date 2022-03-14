#pragma once

#include "DesignPattern/ComponentBase/Component/Component.h"
#include "Utility/CommonClasses/CommonClasses.h"

class Rigidbody : public Component
{
private:
	double drag;
	double gravity;
	double mass;
	VELOCITY velocity;
public:
	Rigidbody();
	virtual ~Rigidbody();

	virtual void Operation() override { }

	double		GetMass() const			{ return mass;		}
	void		SetMass(double _mass)	{ mass = _mass;		}
	VELOCITY	GetVelocity() const		{ return velocity;	}
	void		SetVelocity(VELOCITY _v){ velocity = _v;	}

	void AddForce(D_POINT _f);
	void MovePosition(D_POINT _p);
	void MovePosition();
	void AdaptDrag();
	void AdaptGravity();
};
