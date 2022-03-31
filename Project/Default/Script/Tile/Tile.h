#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Subject.h"

class Tile : public MonoBehaviour, public Subject
{
private:
	POINT gridPos;
protected:
public:
	Tile();
	virtual ~Tile() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update();
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	POINT	GetGridPos() const			{ return gridPos; }
	void	SetGridPos(POINT _gridPos)	{ gridPos = _gridPos; }
};

class TileFocus : public Tile
{
private:
public:
	TileFocus();
	virtual ~TileFocus() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update();
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};
