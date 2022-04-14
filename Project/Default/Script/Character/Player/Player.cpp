#include "Stdafx/stdafx.h"

#include "Script/Character/Player/Player.h"

#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Scene/Scene.h"
#include "Script/HpBar/HpBar.h"

Player::Player()
	: Component((const Component_ID)typeid(Player).name())
{
	state = PHASE_DETAIL::DEFAULT;
}

void Player::Update()
{
	RenderedAnimator* rAnim = gameObject->GetComponent<RenderedAnimator>();
	CHARACTER_STATE animState = rAnim->GetAnimationState();
	Scene* scene = (Scene*)observerVec[0];
	RECT playerRc = gameObject->GetComponent<RectTransform>()->GetScreenRectByCamera();

	if (PtInRect(&playerRc, POINT_MOUSE) && !observerVec.empty())
	{
		if (scene->GetHpBar())
			scene->GetHpBar()->PrepareRender(((float)hp / hpMax));
	}

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
				MovePos(animState, gameObject->GetComponent<Transform>());
			}
		}
			break;
		case PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION:
		{
			DIRECTION moveDir = SearchRoute(scene, gridPos, moveGridPos);

			switch (moveDir)
			{
			case DIRECTION::LEFT_BOTTOM:
				nextGridPos = POINT{ gridPos.x, gridPos.y + 1 };
				if (animState != CHARACTER_STATE::MOVE_LEFT_BOTTOM)
					rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_LEFT_BOTTOM);
				state = PHASE_DETAIL::BATTLE_PLAYER_MOVING;
				break;
			case DIRECTION::LEFT_TOP:
				nextGridPos = POINT{ gridPos.x - 1, gridPos.y };
				if (animState != CHARACTER_STATE::MOVE_LEFT_TOP)
					rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_LEFT_TOP);
				state = PHASE_DETAIL::BATTLE_PLAYER_MOVING;
				break;
			case DIRECTION::RIGHT_BOTTOM:
				nextGridPos = POINT{ gridPos.x + 1, gridPos.y };
				if (animState != CHARACTER_STATE::MOVE_RIGHT_BOTTOM)
					rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_RIGHT_BOTTOM);
				state = PHASE_DETAIL::BATTLE_PLAYER_MOVING;
				break;
			case DIRECTION::RIGHT_TOP:
				nextGridPos = POINT{ gridPos.x, gridPos.y - 1 };
				if (animState != CHARACTER_STATE::MOVE_RIGHT_TOP)
					rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_RIGHT_TOP);
				state = PHASE_DETAIL::BATTLE_PLAYER_MOVING;
				break;
			default:
				ChangeAnimMoveToIdle(animState, rAnim);
				Notify(EVENT::MOVE_END);
				break;
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
					ChangeAnimAttackToIdle(rAnim->GetAnimationState(), rAnim);

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

void Player::NoMove()
{
	state = PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION;
}

void Player::StartAttack(DIRECTION _dir)
{
	state = PHASE_DETAIL::BATTLE_PLAYER_ACTION;
	RenderedAnimator* rAnim = gameObject->GetComponent<RenderedAnimator>();

	switch (id)
	{
	case CHARACTER_ID::AL:
		SOUND->Play(KEY_SOUND_SLASH);
		break;
	case CHARACTER_ID::KARIN:
		SOUND->Play(KEY_SOUND_FLAME_BURST);
		break;
	}

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

void Player::Attacked(Damage _dmg, DIRECTION _dir)
{
	int pDmg = _dmg.str - def;
	int mDmg = _dmg.mgc - mDef;
	if (pDmg < 0) pDmg = 0;
	if (mDmg < 0) mDmg = 0;
	int tDmg = pDmg + mDmg;
	if (tDmg <= 0) tDmg = 1;

	hp -= tDmg;
}
