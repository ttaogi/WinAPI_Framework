#pragma once

#include "Script/Character/Character.h"

class Enemy : public Character
{
private:
public:
	Enemy();
	virtual ~Enemy() { }

	virtual void Update() override;
};