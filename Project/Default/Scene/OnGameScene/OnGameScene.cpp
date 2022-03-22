#include "Stdafx/stdafx.h"

#include "OnGameScene.h"

const static std::wstring NOTICE = L"Press Q to quit.";

OnGameScene::OnGameScene() { }

OnGameScene::~OnGameScene() { }

HRESULT OnGameScene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_ONGAMESCENE);
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

	GameObject* platform01 = FACTORY_METHOD_PLATFORM->CreateObject(
		PLATFORM_FACTORY_TYPE::DEFAULT,
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y * 3 / 4 }, 800, 20,
		IMG->FindImage(KEY_PLATFORM_DEFAULT_SPRITE));

	root = new GameObject();
	root->AddGameObject(quitBtn);
	root->AddGameObject(player);
	root->AddGameObject(platform01);

	msg = L"";

	alpha = 0;
	bgSpeed = 20;
	bgOffsetX = 0;
	bgOffsetY = 0;

	return S_OK;
}

void OnGameScene::Update()
{
	if (KEY->IsOnceKeyDown('Q'))
	{
		GameObject* quitBtn = root->GetGameObjectByName(NAME_QUIT_BUTTON);
		if (quitBtn) quitBtn->SetActive(!quitBtn->GetActive());
	}
	if (KEY->IsOnceKeyDown('E'))
	{
		if (TIME->GetTimeScale() > 0.5) TIME->SetTimeScale(0.1);
		else TIME->SetTimeScale(1);
	}

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

	bgOffsetX = (bgOffsetX + bgSpeed) % WINSIZE_X;
	alpha = (alpha + 5) % 255;
}

void OnGameScene::Release()
{
	SAFE_DELETE(root);
}

void OnGameScene::Render()
{
	HDC memDC = MAIN_GAME->GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	RECT tmp{ 0, 0, WINSIZE_X, WINSIZE_Y };
	backgroundImage->LoopAlphaRender(memDC, &tmp, bgOffsetX, bgOffsetY, alpha);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
