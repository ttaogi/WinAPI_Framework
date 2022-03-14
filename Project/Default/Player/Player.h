#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
//#include "StateMachine/PlayerStateMachine/PlayerStateMachine.h"

class Player : public MonoBehaviour
{
private:
	int hp;
public:
	Player();
	virtual ~Player();

	virtual void Operation() override;

	virtual void Init() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(Collision _col) override;
};