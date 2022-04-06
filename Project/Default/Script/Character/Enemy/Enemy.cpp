#include "Stdafx/stdafx.h"

#include "Script/Character/Enemy/Enemy.h"

#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Scene/Scene.h"
#include "Script/Character/Player/Player.h"

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

	if (phaseDetail == PHASE_DETAIL::BATTLE_ENEMY_DEFAULT)
	{
		switch (state)
		{
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

					if (gridPos.x < moveGridPos.x)
					{
						nextGridPos = POINT{ gridPos.x + 1, gridPos.y };

						if (scene->IsEmpty(nextGridPos))
						{
							if (animState != CHARACTER_STATE::MOVE_RIGHT_BOTTOM)
								rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_RIGHT_BOTTOM);
							state = PHASE_DETAIL::BATTLE_ENEMY_MOVING;
						}
						else
						{
							ChangeAnimMoveToIdle(animState, rAnim);
							state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_ACTION;
						}
					}
					else if (gridPos.x > moveGridPos.x)
					{
						nextGridPos = POINT{ gridPos.x - 1, gridPos.y };

						if (scene->IsEmpty(nextGridPos))
						{
							if (animState != CHARACTER_STATE::MOVE_LEFT_TOP)
								rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_LEFT_TOP);
							state = PHASE_DETAIL::BATTLE_ENEMY_MOVING;
						}
						else
						{
							ChangeAnimMoveToIdle(animState, rAnim);
							state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_ACTION;
						}
					}
					else
					{
						if (gridPos.y < moveGridPos.y)
						{
							nextGridPos = POINT{ gridPos.x, gridPos.y + 1 };

							if(scene->IsEmpty(nextGridPos))
							{
								if (animState != CHARACTER_STATE::MOVE_LEFT_BOTTOM)
									rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_LEFT_BOTTOM);
								state = PHASE_DETAIL::BATTLE_ENEMY_MOVING;
							}
							else
							{
								ChangeAnimMoveToIdle(animState, rAnim);
								state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_ACTION;
							}
						}
						else // if (gridPos.y > moveGridPos.y)
						{
							nextGridPos = POINT{ gridPos.x, gridPos.y - 1 };

							if(scene->IsEmpty(nextGridPos))
							{
								if (animState != CHARACTER_STATE::MOVE_RIGHT_TOP)
									rAnim->ChangeAnimation(CHARACTER_STATE::MOVE_RIGHT_TOP);
								state = PHASE_DETAIL::BATTLE_ENEMY_MOVING;
							}
							else
							{
								ChangeAnimMoveToIdle(animState, rAnim);
								state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_ACTION;
							}
						}
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
}

void Enemy::StartMove()
{
	movingDistCount = ENEMY_MOVE_RANGE;
	state = PHASE_DETAIL::BATTLE_ENEMY_SELECTING_DIRECTION;
}
