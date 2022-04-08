#pragma once

#include "Script/Character/Character.h"

class Player : public Character
{
private:
	CHARACTER_ID id;
public:
	Player();
	virtual ~Player() { }

	virtual void Update() override;

	virtual void Attacked(Damage _dmg, DIRECTION _dir) override;

	CHARACTER_ID	GetId() const			{ return id; }
	void			SetId(CHARACTER_ID _id)	{ id = _id; }

	void StartMove(POINT _moveGridPos);
	void NoMove();
	void StartAttack(DIRECTION _dir);
	void Stay();
};