#include "Stdafx/stdafx.h"

#include "Scene/FieldScene/FieldScene.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "Script/Character/Player/Player.h"
#include "Script/Character/Enemy/Enemy.h"
#include "Script/DialogViewer/DialogViewer.h"
#include "Script/Tile/Tile.h"

FieldScene::FieldScene() { }

FieldScene::~FieldScene() { }

void FieldScene::OnNotify(Subject* _subject, EVENT _event)
{
	switch (_event)
	{
	case EVENT::DIALOG_CLICK:
		if (GAMEMANAGER->GetPhase() == PHASE::PHASE_DIALOG)
		{
			GameObject* dialogViewer = root->GetGameObjectByName(SKIG_DIALOG_VIEWER);
			DialogViewer* dv = dialogViewer->GetComponent<DialogViewer>();

			if (dv)
			{
				if (dv->IsEnd())
				{
					dialogViewer->SetActive(false);

					CAMERA->SetTarget(mapData.playerVec[0]);
					GAMEMANAGER->SetPhase(PHASE::PHASE_BATTLE);
					GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_DEFAULT);
				}
				else
					dv->Next();
			}
		}
		break;
	case EVENT::TILE_CLICK_RIGHT:
		if (GAMEMANAGER->GetPhase() == PHASE::PHASE_BATTLE)
		{
			if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_SELECTING_ACTION)
			{
				for (auto iterCol = mapData.tileVec.begin(); iterCol != mapData.tileVec.end(); ++iterCol)
					for (auto iter = iterCol->begin(); iter != iterCol->end(); ++iter)
					{
						(*iter)->GetGameObjectByName(SKIG_TILE_TILE)->GetComponent<RenderedImage>()->SetEnabled(false);
					}

				GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_DEFAULT);
			}
			else if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_DEFAULT)
			{
				enemyVec.clear();

				for (auto iter = mapData.enemyVec.begin(); iter != mapData.enemyVec.end(); ++iter)
				{
					Enemy* e = (*iter)->GetComponent<Enemy>();
					if (e->GetHp() > 0) enemyVec.push_back(e);
				}

				if (enemyVec.size() == 0)
				{
					CAMERA->SetTarget(NULL);
					SCENE->SetNextSceneKeyTownScene();
				}
				else
				{
					Enemy* e = enemyVec[0];
					enemyVec.erase(enemyVec.begin());

					CAMERA->SetTarget(e->gameObject);

					e->StartMove();
					GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_ENEMY_DEFAULT);
				}
			}
		}
		break;
	case EVENT::TILE_CLICK:
		if(GAMEMANAGER->GetPhase() == PHASE::PHASE_BATTLE)
		{
			if(GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_DEFAULT)
			{
				POINT gridPosClick = ((Tile*)_subject)->GetGridPos();
				wcout << L"[Battle:Player default] Tile Click : " << gridPosClick.x << L"-" << gridPosClick.y << endl;

				for (auto iter = mapData.playerVec.begin(); iter != mapData.playerVec.end(); ++iter)
				{
					POINT pGridPos = (*iter)->GetComponent<Player>()->GetGridPos();

					if (PointEqual(gridPosClick, pGridPos))
					{
						selectedObj = *iter;

						for (auto iterCol = mapData.tileVec.begin(); iterCol != mapData.tileVec.end(); ++iterCol)
							for (auto iter = iterCol->begin(); iter != iterCol->end(); ++iter)
							{
								GameObject* tileScriptGo = (*iter)->GetGameObjectByName(SKIG_TILE_TILE);
								POINT gridPos = tileScriptGo->GetComponent<Tile>()->GetGridPos();

								if (GridPosDist(gridPosClick, gridPos) <= MOVE_RANGE)
									tileScriptGo->GetComponent<RenderedImage>()->SetEnabled(true);
							}

						CAMERA->SetTarget(selectedObj);
						GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_CHARACTER_SELECTED);

						break;
					}
				}
			} // PHASE_DETAIL::BATTLE_PLAYER_DEFAULT
			else if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_CHARACTER_SELECTED)
			{
				POINT gridPosClick = ((Tile*)_subject)->GetGridPos();
				wcout << L"[Battle:Player character selected] Tile Click : " << gridPosClick.x << L"-" << gridPosClick.y << endl;

				POINT playerGridPos = selectedObj->GetComponent<Player>()->GetGridPos();

				if (PointEqual(gridPosClick, playerGridPos))
				{
					for (auto iterCol = mapData.tileVec.begin(); iterCol != mapData.tileVec.end(); ++iterCol)
						for (auto iter = iterCol->begin(); iter != iterCol->end(); ++iter)
							(*iter)->GetGameObjectByName(SKIG_TILE_TILE)->GetComponent<RenderedImage>()->SetEnabled(false);

					selectedObj->GetComponent<Player>()->NoMove();
					GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION);
				}
				else if (GridPosDist(gridPosClick, playerGridPos) <= MOVE_RANGE)
				{
					for (auto iter = mapData.playerVec.begin(); iter != mapData.playerVec.end(); ++iter)
					{
						POINT p = (*iter)->GetComponent<Player>()->GetGridPos();
						if (PointEqual(p, gridPosClick)) return;
					}

					for (auto iter = mapData.enemyVec.begin(); iter != mapData.enemyVec.end(); ++iter)
					{
						POINT p = (*iter)->GetComponent<Enemy>()->GetGridPos();
						if (PointEqual(p, gridPosClick)) return;
					}

					for (auto iterCol = mapData.tileVec.begin(); iterCol != mapData.tileVec.end(); ++iterCol)
						for (auto iter = iterCol->begin(); iter != iterCol->end(); ++iter)
							(*iter)->GetGameObjectByName(SKIG_TILE_TILE)->GetComponent<RenderedImage>()->SetEnabled(false);

					// command for player to move.
					selectedObj->GetComponent<Player>()->StartMove(gridPosClick);

					GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_MOVING);
				}
			} // PHASE_DETAIL::BATTLE_PLAYER_CHARACTER_SELECTED
			else if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION)
			{
				// None.
			} // PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION
			else if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_SELECTING_ACTION)
			{
				POINT playerGridPos = selectedObj->GetComponent<Player>()->GetGridPos();
				POINT tileGridPos = ((Tile*)_subject)->GetGridPos();

				if (GridPosDist(playerGridPos, tileGridPos) == 1)
				{
					for (auto iter = mapData.enemyVec.begin(); iter != mapData.enemyVec.end(); ++iter)
					{
						POINT enemyGridPos = (*iter)->GetComponent<Enemy>()->GetGridPos();

						if (PointEqual(tileGridPos, enemyGridPos))
						{
							if (playerGridPos.x - 1 == tileGridPos.x)
								selectedObj->GetComponent<Player>()->StartAttack(DIRECTION::LEFT_TOP);
							else if (playerGridPos.x + 1 == tileGridPos.x)
								selectedObj->GetComponent<Player>()->StartAttack(DIRECTION::RIGHT_BOTTOM);
							else if (playerGridPos.y - 1 == tileGridPos.y)
								selectedObj->GetComponent<Player>()->StartAttack(DIRECTION::RIGHT_TOP);
							else
								selectedObj->GetComponent<Player>()->StartAttack(DIRECTION::LEFT_BOTTOM);

							for(auto iterCol = mapData.tileVec.begin(); iterCol != mapData.tileVec.end(); ++iterCol)
								for (auto iter = iterCol->begin(); iter != iterCol->end(); ++iter)
								{
									(*iter)->GetGameObjectByName(SKIG_TILE_TILE)->GetComponent<RenderedImage>()->SetEnabled(false);
								}

							GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_ACTION);
							break;
						}
					}
				}
			}
		} // PHASE::PHASE_BATTLE
		break; // EVENT::TILE_CLICK
	case EVENT::MOVE_END:
		if(GAMEMANAGER->GetPhase() == PHASE::PHASE_BATTLE)
		{
			if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_MOVING)
			{
				GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION);
			} // PHASE_DETAIL::BATTLE_PLAYER_MOVING
		}
		break;
	case EVENT::SELECT_DIRECTION_END:
		if (GAMEMANAGER->GetPhase() == PHASE::PHASE_BATTLE)
		{
			if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION)
			{
				POINT playerGridPos = ((Player*)_subject)->GetGridPos();

				for (auto iterCol = mapData.tileVec.begin(); iterCol != mapData.tileVec.end(); ++iterCol)
					for (auto iter = iterCol->begin(); iter != iterCol->end(); ++iter)
					{
						Tile* tile = (*iter)->GetGameObjectByName(SKIG_TILE_TILE)->GetComponent<Tile>();
						if (GridPosDist(playerGridPos, tile->GetGridPos()) == 1)
							(*iter)->GetGameObjectByName(SKIG_TILE_TILE)->GetComponent<RenderedImage>()->SetEnabled(true);
					}

				GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_SELECTING_ACTION);
			} // PHASE_DETAIL::BATTLE_PLAYER_SELECTING_DIRECTION
		}
		break;
	case EVENT::ACTION_END:
		if (GAMEMANAGER->GetPhase() == PHASE::PHASE_BATTLE)
		{
			if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_PLAYER_ACTION)
			{
				GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_DEFAULT);
			} // PHASE_DETAIL::BATTLE_PLAYER_ACTION
			else if (GAMEMANAGER->GetPhaseDetail() == PHASE_DETAIL::BATTLE_ENEMY_DEFAULT)
			{
				if (enemyVec.size() == 0)
				{
					CAMERA->SetTarget(mapData.playerVec[0]);
					GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::BATTLE_PLAYER_DEFAULT);
				}
				else
				{
					Enemy* e = enemyVec[0];
					enemyVec.erase(enemyVec.begin());

					CAMERA->SetTarget(e->gameObject);

					e->StartMove();
				}
			} // PHASE_DETAIL::BATTLE_ENEMY_DEFAULT
		}
		break;
	}
}

HRESULT FieldScene::Init()
{
	SOUND->AllStop();
	
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_FIELD);
	root = NULL;
	selectedObj = NULL;
	enemyVec.clear();

	if (!MAPDATA->GetMapData(XML_DOC_FIELD_MAP_DATA, this, mapData)) return E_FAIL;

	//GameObject* toTownButton = FACTORY_METHOD_BUTTON->CreateObject(
	//	BUTTON_FACTORY_TYPE::MOUSE_ON,
	//	std::bind(&SceneManager::SetNextSceneKeyTownScene, SCENE),
	//	D_POINT{ 590, 455 }, 100, 50,
	//	IMG->FindImage(KEY_UI_TOWN_TO_FIELD_BUTTON_SPRITE));

	GameObject* dialogViewer = FACTORY_METHOD_DIALOGVIEWER->CreateObject(this, DIALOG_SPOT_FIELD, -1);

	root = new GameObject();
	LoadMapData(&mapData);
	//root->AddGameObject(toTownButton);
	root->AddGameObject(dialogViewer);

	SOUND->Play(KEY_SOUND_FIELD_THEME, GAMEDATA->GetVolume());

	int mapSizeX = (int)mapData.tileVec.size();
	int mapSizeY = (int)mapData.tileVec[0].size();
	CAMERA->SetTarget(mapData.tileVec[mapSizeX / 2][mapSizeY / 2]);
	CAMERA->Update();

	GAMEMANAGER->SetPhase(PHASE::PHASE_DIALOG);
	GAMEMANAGER->SetPhaseDetail(PHASE_DETAIL::DEFAULT);

	return S_OK;
}

void FieldScene::Release()
{
	enemyVec.clear();
	CAMERA->SetTarget(NULL);
	CAMERA->Update();
	SAFE_DELETE(root);
}

void FieldScene::Update()
{
	SOUND->Update();

	root->Update();

	CAMERA->Update();
}

void FieldScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
