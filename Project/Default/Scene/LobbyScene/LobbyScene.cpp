#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "Scene/LobbyScene/LobbyScene.h"

const wstring stage1BtnName = L"STAGE1BTN";
const wstring stage2BtnName = L"STAGE2BTN";
const wstring stage3BtnName = L"STAGE3BTN";
const wstring stage4BtnName = L"STAGE4BTN";

LobbyScene::LobbyScene() { }

LobbyScene::~LobbyScene() { }

HRESULT LobbyScene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_LOBBYSCENE);
	root = NULL;

	GameObject* quitBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyEndScene, SCENE),
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y / 2 }, BUTTON_WIDTH, BUTTON_HEIGHT,
		IMG->FindImage(KEY_UI_QUIT_BUTTON_SPRITE));
	quitBtn->SetName(NAME_QUIT_BUTTON);
	quitBtn->SetActive(false);

	// stage btn.
	GameObject* stage1btn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyStage1Scene, SCENE),
		D_POINT{ 121 + 207, 120 + 77 }, 415, 155,
		IMG->FindImage(KEY_UI_STAGE_1_BUTTON_SPRITE));
	stage1btn->SetName(stage1BtnName);

	GameObject* stage2btn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyStage2Scene, SCENE),
		D_POINT{ 743 + 207, 120 + 77 }, 415, 155,
		IMG->FindImage(KEY_UI_STAGE_2_BUTTON_SPRITE));
	stage2btn->SetName(stage2BtnName);
	if (!GAMEDATA->GetStage1Clear())
		stage2btn->GetComponent<Button>()->SetEnabled(false);

	GameObject* stage3btn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyStage3Scene, SCENE),
		D_POINT{ 121 + 207, 422 + 77 }, 415, 155,
		IMG->FindImage(KEY_UI_STAGE_3_BUTTON_SPRITE));
	stage3btn->SetName(stage3BtnName);
	if (!GAMEDATA->GetStage2Clear())
		stage3btn->GetComponent<Button>()->SetEnabled(false);

	GameObject* stage4btn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyStage4Scene, SCENE),
		D_POINT{ 743 + 207, 422 + 77 }, 415, 155,
		IMG->FindImage(KEY_UI_STAGE_4_BUTTON_SPRITE));
	stage4btn->SetName(stage4BtnName);
	if (!GAMEDATA->GetStage3Clear())
		stage4btn->GetComponent<Button>()->SetEnabled(false);

	root = new GameObject();
	root->AddGameObject(quitBtn);
	root->AddGameObject(stage1btn);
	root->AddGameObject(stage2btn);
	root->AddGameObject(stage3btn);
	root->AddGameObject(stage4btn);

	SOUND->Play(KEY_SOUND_LOBBY_THEME, GAMEDATA->GetVolume());

	return S_OK;
}

void LobbyScene::Release()
{
	SAFE_DELETE(root);
}

void LobbyScene::Update()
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

void LobbyScene::Render()
{
	HDC memDC = MAIN_GAME->GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
