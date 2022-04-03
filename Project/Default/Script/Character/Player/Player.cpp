#include "Stdafx/stdafx.h"

#include "Script/Character/Player/Player.h"

#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

Player::Player()
	: Component((const Component_ID)typeid(Player).name())
{
	state = PHASE_DETAIL::DEFAULT;
}

void Player::Update()
{
	RenderedAnimator* rAnim = gameObject->GetComponent<RenderedAnimator>();
	CHARACTER_STATE animState = rAnim->GetAnimationState();

	if(GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_MOVING)
	{
		switch (state)
		{
		case PHASE_DETAIL::BATTLE_PLAYER_MOVING:
			{
				POINT pos = gameObject->GetComponent<Transform>()->GetPosition().ToPoint();
				POINT pNextGridPos = GridPosToPos(nextGridPos);

				if (PointDist(pos, pNextGridPos) <= 6)
				{
					gameObject->GetComponent<Transform>()->SetPosition(D_POINT{ (double)pNextGridPos.x, (double)pNextGridPos.y });
					gridPos = nextGridPos;
					state = PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION;
				}
				else
				{
					switch (animState)
					{
					case CHARACTER_STATE::MOVE_LEFT_BOTTOM:
						gameObject->GetComponent<Transform>()->SetPosition(D_POINT{ (double)pos.x - 4, (double)pos.y + 2 });
						break;
					case CHARACTER_STATE::MOVE_LEFT_TOP:
						gameObject->GetComponent<Transform>()->SetPosition(D_POINT{ (double)pos.x - 4, (double)pos.y - 2 });
						break;
					case CHARACTER_STATE::MOVE_RIGHT_BOTTOM:
						gameObject->GetComponent<Transform>()->SetPosition(D_POINT{ (double)pos.x + 4, (double)pos.y + 2 });
						break;
					case CHARACTER_STATE::MOVE_RIGHT_TOP:
						gameObject->GetComponent<Transform>()->SetPosition(D_POINT{ (double)pos.x + 4, (double)pos.y - 2 });
						break;
					}
				}
			}
			break;
		case PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION:
			if (gridPos.x < moveGridPos.x)
			{
				nextGridPos = POINT{ gridPos.x + 1, gridPos.y };
				rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_RIGHT_BOTTOM);
				state = PHASE_DETAIL::BATTLE_PLAYER_MOVING;
			}
			else if (gridPos.x > moveGridPos.x)
			{
				nextGridPos = POINT{ gridPos.x - 1, gridPos.y };
				rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_LEFT_TOP);
				state = PHASE_DETAIL::BATTLE_PLAYER_MOVING;
			}
			else
			{
				if (gridPos.y < moveGridPos.y)
				{
					nextGridPos = POINT{ gridPos.x, gridPos.y + 1 };
					rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_LEFT_BOTTOM);
					state = PHASE_DETAIL::BATTLE_PLAYER_MOVING;
				}
				else if (gridPos.y > moveGridPos.y)
				{
					nextGridPos = POINT{ gridPos.x, gridPos.y - 1 };
					rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_RIGHT_TOP);
					state = PHASE_DETAIL::BATTLE_PLAYER_MOVING;
				}
				else
				{
					switch (animState)
					{
					case CHARACTER_STATE::MOVE_LEFT_BOTTOM:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
						break;
					case CHARACTER_STATE::MOVE_LEFT_TOP:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_TOP);
						break;
					case CHARACTER_STATE::MOVE_RIGHT_BOTTOM:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM);
						break;
					case CHARACTER_STATE::MOVE_RIGHT_TOP:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP);
						break;
					default:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
						break;
					}
					Notify(EVENT::MOVE_END);
				}
			}
			break;
		}
	}
	else if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION)
	{
		switch(state)
		{
		case PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION:
			if (MOUSE_CLICKED)
			{
				if (POINT_MOUSE.x < WINSIZE_X / 2)
					if (POINT_MOUSE.y < WINSIZE_Y / 2)
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_TOP);
					else
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
				else
					if (POINT_MOUSE.y < WINSIZE_Y / 2)
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP);
					else
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM);

				state = PHASE_DETAIL::BATTLE_PLAYER_SELECTING_ACTION;
				Notify(EVENT::SELECT_DIRECTION_END);
			}
			break;
		}
	}
	else if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_SELECTING_ACTION)
	{
		switch (state)
		{
		case PHASE_DETAIL::BATTLE_PLAYER_SELECTING_ACTION:
			break;
		}
	}
	else if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_ACTION)
	{
		switch (state)
		{
		case PHASE_DETAIL::BATTLE_PLAYER_ACTION:
			{
				RenderedAnimator* rAnim = gameObject->GetComponent<RenderedAnimator>();

				if (rAnim->IsEnd())
				{
					CHARACTER_STATE anim = rAnim->GetAnimationState();

					switch (anim)
					{
					case CHARACTER_STATE::ATTACK_LEFT_TOP:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_TOP);
						break;
					case CHARACTER_STATE::ATTACK_LEFT_BOTTOM:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
						break;
					case CHARACTER_STATE::ATTACK_RIGHT_TOP:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP);
						break;
					default:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM);
						break;
					}

					state = PHASE_DETAIL::DEFAULT;

					Notify(EVENT::ACTION_END);
				}
			}
			break;
		}
	}
}

void Player::StartMove(POINT _moveGridPos)
{
	state = PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION;
	moveGridPos = _moveGridPos;
}

void Player::StartAttack(DIRECTION _dir)
{
	state = PHASE_DETAIL::BATTLE_PLAYER_ACTION;
	RenderedAnimator* rAnim = gameObject->GetComponent<RenderedAnimator>();

	switch (_dir)
	{
	case DIRECTION::LEFT_TOP:
		rAnim->ChangeAnimation(CHARACTER_STATE::ATTACK_LEFT_TOP);
		break;
	case DIRECTION::LEFT_BOTTOM:
		rAnim->ChangeAnimation(CHARACTER_STATE::ATTACK_LEFT_BOTTOM);
		break;
	case DIRECTION::RIGHT_TOP:
		rAnim->ChangeAnimation(CHARACTER_STATE::ATTACK_RIGHT_TOP);
		break;
	default:
		rAnim->ChangeAnimation(CHARACTER_STATE::ATTACK_RIGHT_BOTTOM);
		break;
	}
}

void Player::Stay()
{
	state = PHASE_DETAIL::DEFAULT;
}
