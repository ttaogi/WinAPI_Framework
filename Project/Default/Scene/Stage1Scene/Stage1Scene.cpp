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
		IMG->FindImage(KEY_UI_QUIT_BUTTON_STRIPE));
	quitBtn->SetName(NAME_QUIT_BUTTON);
	quitBtn->SetActive(false);

	root = new GameObject();
	root->AddGameObject(quitBtn);

	SOUND->Play(KEY_SOUND_STAGE_1_NORMAL, GAMEDATA->GetVolume());

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
