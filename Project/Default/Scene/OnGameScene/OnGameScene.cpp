#include "Stdafx/stdafx.h"

#include "OnGameScene.h"

#include <functional>

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"

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

	root = new GameObject();
	root->AddGameObject(quitBtn);

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

	root->Update();

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
