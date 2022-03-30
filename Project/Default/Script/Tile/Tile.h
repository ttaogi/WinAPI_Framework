#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Subject.h"

class Tile : public MonoBehaviour, public Subject
{
private:
public:
	Tile();
	virtual ~Tile() { }

	virtual void Operation() override { }

	virtual void Init() { }
	virtual void FixedUpdate() { }
	virtual void Update();
	virtual void LateUpdate() { }
	virtual void OnCollision(Collision _col) { }
};
