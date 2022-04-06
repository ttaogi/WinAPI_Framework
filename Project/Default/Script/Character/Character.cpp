#include "Stdafx/stdafx.h"

#include "Script/Character/Character.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"

Character::Character()
	: Component((const Component_ID)typeid(Character).name()) { }

void Character::ChangeAnimMoveToIdle(CHARACTER_STATE _animState, RenderedAnimator* _rAnim)
{
	switch (_animState)
	{
	case CHARACTER_STATE::MOVE_LEFT_BOTTOM:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
		break;
	case CHARACTER_STATE::MOVE_LEFT_TOP:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_TOP);
		break;
	case CHARACTER_STATE::MOVE_RIGHT_BOTTOM:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM);
		break;
	case CHARACTER_STATE::MOVE_RIGHT_TOP:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP);
		break;
	default:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
		break;
	}
}

void Character::ChangeAnimAttackToIdle(CHARACTER_STATE _animState, RenderedAnimator * _rAnim)
{
	switch (_animState)
	{
	case CHARACTER_STATE::ATTACK_LEFT_BOTTOM:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
		break;
	case CHARACTER_STATE::ATTACK_LEFT_TOP:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_TOP);
		break;
	case CHARACTER_STATE::ATTACK_RIGHT_BOTTOM:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM);
		break;
	case CHARACTER_STATE::ATTACK_RIGHT_TOP:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP);
		break;
	default:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
		break;
	}
}

void Character::MovePos(CHARACTER_STATE _animState, Transform* _t)
{
	POINT pos = _t->GetPosition().ToPoint();

	switch (_animState)
	{
	case CHARACTER_STATE::MOVE_LEFT_BOTTOM:
		_t->SetPosition(D_POINT{ (double)pos.x - 2, (double)pos.y + 1 });
		break;
	case CHARACTER_STATE::MOVE_LEFT_TOP:
		_t->SetPosition(D_POINT{ (double)pos.x - 2, (double)pos.y - 1 });
		break;
	case CHARACTER_STATE::MOVE_RIGHT_BOTTOM:
		_t->SetPosition(D_POINT{ (double)pos.x + 2, (double)pos.y + 1 });
		break;
	case CHARACTER_STATE::MOVE_RIGHT_TOP:
		_t->SetPosition(D_POINT{ (double)pos.x + 2, (double)pos.y - 1 });
		break;
	}
}
