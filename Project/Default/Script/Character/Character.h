#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Subject.h"

class Character : public MonoBehaviour, public Subject
{
private:
	POINT gridPos;
public:
	Character();
	virtual ~Character() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override = 0;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	POINT	GetGridPos() const			{ return gridPos; }
	void	SetGridPos(POINT _gridPos)	{ gridPos = _gridPos; }
};