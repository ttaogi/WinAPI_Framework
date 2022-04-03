#pragma once

#include "Script/Character/Character.h"

class Player : public Character
{
private:
public:
	Player();
	virtual ~Player() { }

	virtual void Update() override;

	void StartMove(POINT _moveGridPos);
	void StartAttack(DIRECTION _dir);
	void Stay();
};