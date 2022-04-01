#include "Stdafx/stdafx.h"

#include "Script/Character/Enemy/Enemy.h"

Enemy::Enemy()
	: Component((const Component_ID)typeid(Enemy).name()) { }

void Enemy::Update()
{
}
