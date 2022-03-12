#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/Behaviour.h"

class MonoBehaviour : public Behaviour
{
protected:
public:
	MonoBehaviour();
	virtual ~MonoBehaviour() {}

	virtual void Operation() override;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
};
