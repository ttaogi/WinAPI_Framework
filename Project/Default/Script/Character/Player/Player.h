#pragma once

#include "Script/Character/Character.h"

class Player : public Character
{
private:
public:
	Player();
	virtual ~Player() { }

	virtual void Update() override;
};