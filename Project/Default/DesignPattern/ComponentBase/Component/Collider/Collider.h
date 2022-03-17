#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/Behaviour.h"

class Collider;

struct Collision
{
	Collider* col1;
	Collider* col2;
};

class Collider : public Behaviour
{
private:
	bool isTrigger;
public:
	Collider();
	virtual ~Collider();

	virtual void Operation() override { }

	bool GetIsTrigger() const			{ return isTrigger; }
	void SetIsTrigger(bool _isTrigger)	{ isTrigger = _isTrigger; }

	void CheckCollision(std::vector<Collision>* _colVec, Collider* _col);
};
