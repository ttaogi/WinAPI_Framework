#include "Stdafx/stdafx.h"

#include "Script/Character/Player/Player.h"

Player::Player()
	: Component((const Component_ID)typeid(Player).name()) { }

void Player::Update()
{
}
