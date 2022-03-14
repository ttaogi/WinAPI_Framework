#include "Stdafx/stdafx.h"

#include "OnGameScene.h"

#include <functional>

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"
#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Rigidbody/Rigidbody.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"
#include "Player/Player.h"

const static std::wstring NOTICE = L"Press Q to quit.";

OnGameScene::OnGameScene() { }

OnGameScene::~OnGameScene() { }

HRESULT OnGameScene::Init()
{
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_ONGAMESCENE);
	root = NULL;

	GameObject* quitBtn = AbstractFactoryButton::GetObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyEndScene, SCENE),
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y / 2 }, BUTTON_WIDTH, BUTTON_HEIGHT,
		IMG->FindImage(KEY_UI_QUIT_BUTTON_STRIPE));
	quitBtn->SetName(NAME_QUIT_BUTTON);
	quitBtn->SetActive(false);

	GameObject* player = AbstractFactoryPlayer::GetObject(
		PLAYER_FACTORY_TYPE::DEFAULT,
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y / 2 }, 80, 80,
		IMG->FindImage(KEY_PLAYER_TEMP_STRIPE));

	GameObject* platform01 = AbstractFactoryPlatform::GetObject(
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y * 3 / 4 }, 800, 20,
		IMG->FindImage(KEY_PLATFORM_DEFAULT_STRIPE));

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

	root->FixedUpdate();

	vector<Collider*> colliderVec;
	colliderVec.clear();
	root->CollectCollider(&colliderVec);
	vector<Collision> collisionVec;
	collisionVec.clear();
	for (int i = 0; i < colliderVec.size() - 1; ++i)
		for (int j = i + 1; j < colliderVec.size(); ++j)
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
	SOUND->AllStop();
}

void OnGameScene::Render()
{
	HDC memDC = MAIN_GAME->GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	RECT tmp{ 0, 0, WINSIZE_X, WINSIZE_Y };
	backgroundImage->LoopAlphaRender(memDC, &tmp, bgOffsetX, bgOffsetY, alpha);

	root->Render(memDC);
}
