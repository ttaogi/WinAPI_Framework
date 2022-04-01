#include "Stdafx/stdafx.h"

#include "Script/Character/Character.h"

Character::Character()
	: Component((const Component_ID)typeid(Character).name()) { }
