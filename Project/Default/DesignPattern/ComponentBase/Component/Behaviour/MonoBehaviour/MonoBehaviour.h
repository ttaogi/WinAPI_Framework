#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/Behaviour.h"
#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"

class MonoBehaviour : virtual public Behaviour
{
protected:
public:
	MonoBehaviour();
	virtual ~MonoBehaviour() {}

	virtual void Operation() override;

	virtual void Init() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void OnCollision(Collision _col) = 0;
};
