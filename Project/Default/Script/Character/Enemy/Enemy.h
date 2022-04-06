#pragma once

#include "Script/Character/Character.h"

class Enemy : public Character
{
private:
	int movingDistCount;
public:
	Enemy();
	virtual ~Enemy() { }

	virtual void Update() override;

	virtual void StartMove();
};