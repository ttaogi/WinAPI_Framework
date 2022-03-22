#include "Stdafx/stdafx.h"

#include "Scene/Stage1Scene/Stage1Scene.h"

Stage1Scene::Stage1Scene() { }

Stage1Scene::~Stage1Scene() { }

HRESULT Stage1Scene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_STAGE_1);
	root = NULL;

	GameObject* quitBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyEndScene, SCENE),
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y / 2 }, BUTTON_WIDTH, BUTTON_HEIGHT,
		IMG->FindImage(KEY_UI_QUIT_BUTTON_SPRITE));
	quitBtn->SetName(NAME_QUIT_BUTTON);
	quitBtn->SetActive(false);

	GameObject* player = FACTORY_METHOD_PLAYER->CreateObject(
		PLAYER_FACTORY_TYPE::DEFAULT,
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y / 2 }, 80, 80,
		IMG->FindImage(KEY_PLAYER_TEMP_SPRITE));

	MAPDATA->GetMapData(XML_DOC_STAGE_1, mapData);

	root = new GameObject();
	root->AddGameObject(quitBtn);
	root->AddGameObject(player);

	for (auto iter = mapData.goVec.begin(); iter != mapData.goVec.end(); ++iter)
		root->AddGameObject(*iter);

	SOUND->Play(mapData.normalBgmKey, GAMEDATA->GetVolume());

	return S_OK;
}

void Stage1Scene::Release()
{
	SAFE_DELETE(root);
}

void Stage1Scene::Update()
{
	if (KEY->IsOnceKeyDown('Q'))
	{
		GameObject* quitBtn = root->GetGameObjectByName(NAME_QUIT_BUTTON);
		if (quitBtn) quitBtn->SetActive(!quitBtn->GetActive());
	}

	SOUND->Update();

	root->FixedUpdate();

	// collision detection.
	vector<Collider*> colliderVec;
	colliderVec.clear();
	root->CollectCollider(&colliderVec);
	vector<Collision> collisionVec;
	collisionVec.clear();
	for (int i = 0; i < (int)colliderVec.size() - 1; ++i)
		for (int j = i + 1; j < (int)colliderVec.size(); ++j)
			colliderVec[i]->CheckCollision(&collisionVec, colliderVec[j]);

	ProcessCollision(&collisionVec);

	root->Update();
	root->LateUpdate();
}

void Stage1Scene::Render()
{
	HDC memDC = MAIN_GAME->GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
