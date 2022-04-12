#include "Stdafx/stdafx.h"

#include "Script/Character/Enemy/Enemy.h"

#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Scene/Scene.h"
#include "Script/Character/Player/Player.h"
#include "Script/HpBar/HpBar.h"

Enemy::Enemy()
	: Component((const Component_ID)typeid(Enemy).name())
{
	state = PHASE_DETAIL::DEFAULT;
}

void Enemy::Update()
{
	RenderedAnimator* rAnim = gameObject->GetComponent<RenderedAnimator>();
	CHARACTER_STATE animState = rAnim->GetAnimationState();
	PHASE_DETAIL phaseDetail = GAMEMANAGER->GetPhaseDetail();
	Scene* scene = (Scene*)observerVec[0];
	MapData* mapData = scene->GetMapData();
	RECT enemyRc = gameObject->GetComponent<RectTransform>()->GetScreenRectByCamera();

	if (PtInRect(&enemyRc, POINT_MOUSE) && !observerVec.empty())
	{
		if (scene->GetHpBar())
			scene->GetHpBar()->PrepareRender(((float)hp / hpMax));
	}

	switch (state)
	{
	case PHASE_DETAIL::DEFAULT:
	{
		if (animState == CHARACTER_STATE::ATTACKED_LEFT_BOTTOM ||
			animState == CHARACTER_STATE::ATTACKED_LEFT_TOP ||
			animState == CHARACTER_STATE::ATTACKED_RIGHT_BOTTOM ||
			animState == CHARACTER_STATE::ATTACKED_RIGHT_TOP)
		{
			if (rAnim->IsEnd())
			{
				if (hp <= 0)
				{
					Notify(EVENT::DIE);
				}
				else
				{
					switch (animState)
					{
					case CHARACTER_STATE::ATTACKED_LEFT_BOTTOM:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
						break;
					case CHARACTER_STATE::ATTACKED_LEFT_TOP:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_TOP);
						break;
					case CHARACTER_STATE::ATTACKED_RIGHT_BOTTOM:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM);
						break;
					default:
						rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP);
						break;
					}
				}
			}
		}
	}
		break;
	case PHASE_DETAIL::BATTLE_ENEMY_SELECTING_DIRECTION:
	{
		if (movingDistCount == 0)
		{
			ChangeAnimMoveToIdle(animState, rAnim);
			state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_ACTION;
		}
		else
		{
			Player* nearestPlayer = NULL;
			int dist = 0;

			for (auto iter = mapData->playerVec.begin(); iter != mapData->playerVec.end(); ++iter)
			{
				if ((*iter)->GetComponent<Player>()->GetHp() <= 0) continue;

				if (!nearestPlayer)
				{
					nearestPlayer = (*iter)->GetComponent<Player>();
					dist = GridPosDist(gridPos, nearestPlayer->GetGridPos());
				}
				else
				{
					if (dist > GridPosDist(gridPos, (*iter)->GetComponent<Player>()->GetGridPos()))
					{
						nearestPlayer = (*iter)->GetComponent<Player>();
						dist = GridPosDist(gridPos, (*iter)->GetComponent<Player>()->GetGridPos());
					}
				}
			}

			if (dist == 1)
			{
				ChangeAnimMoveToIdle(animState, rAnim);
				state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_ACTION;
			}
			else
			{
				moveGridPos = nearestPlayer->GetGridPos();

				DIRECTION moveDir = SearchRoute(scene, gridPos, nearestPlayer->GetGridPos());

				switch (moveDir)
				{
				case DIRECTION::LEFT_BOTTOM:
					if (animState != CHARACTER_STATE::MOVE_LEFT_BOTTOM)
						rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_LEFT_BOTTOM);
					nextGridPos = POINT{ gridPos.x, gridPos.y + 1 };
					state = PHASE_DETAIL::BATTLE_ENEMY_MOVING;
					break;
				case DIRECTION::LEFT_TOP:
					if (animState != CHARACTER_STATE::MOVE_LEFT_TOP)
						rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_LEFT_TOP);
					nextGridPos = POINT{ gridPos.x - 1, gridPos.y };
					state = PHASE_DETAIL::BATTLE_ENEMY_MOVING;
					break;
				case DIRECTION::RIGHT_BOTTOM:
					if (animState != CHARACTER_STATE::MOVE_RIGHT_BOTTOM)
						rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_RIGHT_BOTTOM);
					nextGridPos = POINT{ gridPos.x + 1, gridPos.y };
					state = PHASE_DETAIL::BATTLE_ENEMY_MOVING;
					break;
				case DIRECTION::RIGHT_TOP:
					if (animState != CHARACTER_STATE::MOVE_RIGHT_TOP)
						rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_RIGHT_TOP);
					nextGridPos = POINT{ gridPos.x, gridPos.y - 1 };
					state = PHASE_DETAIL::BATTLE_ENEMY_MOVING;
					break;
				default:
					ChangeAnimMoveToIdle(animState, rAnim);
					state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_ACTION;
					break;
				}
			}
		}
	}
		break;
	case PHASE_DETAIL::BATTLE_ENEMY_MOVING:
	{
		POINT pos = gameObject->GetComponent<Transform>()->GetPosition().ToPoint();
		POINT pNextGridPos = GridPosToPos(nextGridPos);

		if (PointDist(pos, pNextGridPos) <= 6)
		{
			gameObject->GetComponent<Transform>()->SetPosition(D_POINT{ (double)pNextGridPos.x, (double)pNextGridPos.y });
			gridPos = nextGridPos;
			--movingDistCount;
			state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_DIRECTION;
		}
		else
			MovePos(animState, gameObject->GetComponent<Transform>());
	}
		break;
	case PHASE_DETAIL::BATTLE_ENEMY_SELECTING_ACTION:
	{
		Player* nearestPlayer = NULL;
		int dist = 0;

		for (auto iter = mapData->playerVec.begin(); iter != mapData->playerVec.end(); ++iter)
		{
			if (!nearestPlayer)
			{
				nearestPlayer = (*iter)->GetComponent<Player>();
				dist = GridPosDist(gridPos, nearestPlayer->GetGridPos());
			}
			else
			{
				if (dist > GridPosDist(gridPos, (*iter)->GetComponent<Player>()->GetGridPos()))
				{
					nearestPlayer = (*iter)->GetComponent<Player>();
					dist = GridPosDist(gridPos, (*iter)->GetComponent<Player>()->GetGridPos());
				}
			}
		}

		if (dist == 1)
		{
			POINT playerPos = nearestPlayer->GetGridPos();
			nearestPlayer->Attacked(Damage{str, 0}, DIRECTION::DIRECTION_NUM);

			if (gridPos.x > playerPos.x)
			{
				rAnim->ChangeAnimation(CHARACTER_STATE::ATTACK_LEFT_TOP);
				state = PHASE_DETAIL::BATTLE_ENEMY_ACTION;
			}
			else if (gridPos.x < playerPos.x)
			{
				rAnim->ChangeAnimation(CHARACTER_STATE::ATTACK_RIGHT_BOTTOM);
				state = PHASE_DETAIL::BATTLE_ENEMY_ACTION;
			}
			else
			{
				if (gridPos.y > playerPos.y)
				{
					rAnim->ChangeAnimation(CHARACTER_STATE::ATTACK_RIGHT_TOP);
					state = PHASE_DETAIL::BATTLE_ENEMY_ACTION;
				}
				else
				{
					rAnim->ChangeAnimation(CHARACTER_STATE::ATTACK_LEFT_BOTTOM);
					state = PHASE_DETAIL::BATTLE_ENEMY_ACTION;
				}
			}
		}
		else
		{
			state = PHASE_DETAIL::DEFAULT;
			Notify(EVENT::ACTION_END);
		}
	}
		break;
	case PHASE_DETAIL::BATTLE_ENEMY_ACTION:
	{
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

void Enemy::Attacked(Damage _dmg, DIRECTION _dir)
{
	int pDmg = _dmg.str - def;
	int mDmg = _dmg.mgc - mDef;
	if (pDmg < 0) pDmg = 0;
	if (mDmg < 0) mDmg = 0;
	int tDmg = pDmg + mDmg;
	if (tDmg <= 0) tDmg = 1;
	hp -= tDmg;

	RenderedAnimator* rAnim = gameObject->GetComponent<RenderedAnimator>();

	switch (_dir)
	{
	case DIRECTION::LEFT_BOTTOM:
		rAnim->ChangeAnimation(CHARACTER_STATE::ATTACKED_LEFT_BOTTOM);
		break;
	case DIRECTION::LEFT_TOP:
		rAnim->ChangeAnimation(CHARACTER_STATE::ATTACKED_LEFT_TOP);
		break;
	case DIRECTION::RIGHT_BOTTOM:
		rAnim->ChangeAnimation(CHARACTER_STATE::ATTACKED_RIGHT_BOTTOM);
		break;
	default:
		rAnim->ChangeAnimation(CHARACTER_STATE::ATTACKED_RIGHT_TOP);
		break;
	}
}

void Enemy::StartMove()
{
	movingDistCount = ENEMY_MOVE_RANGE;
	state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_DIRECTION;
}
