#include "Stdafx/stdafx.h"

#include "TitleScene.h"

#include <functional>

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"

TitleScene::TitleScene() { }

TitleScene::~TitleScene() { }

HRESULT TitleScene::Init()
{
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_TITLESCENE);
	root = NULL;

	GameObject* gameStartBtn = AbstractFactoryButton::GetObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyOnGameScene, SCENE),
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y / 2 }, BUTTON_WIDTH, BUTTON_HEIGHT,
		IMG->FindImage(KEY_UI_START_BUTTON_STRIPE));

	root = new GameObject();
	root->AddGameObject(gameStartBtn);

	SOUND->Play(KEY_SOUND_EXAMPLE, DEFAULT_SOUND_VOLUME);

	return S_OK;
}

void TitleScene::Update()
{
	if (KEY->IsOnceKeyDown(VK_ESCAPE))
	{
		MAIN_GAME->QuitGame();
		return;
	}

	SOUND->Update();

	root->Update();
}

void TitleScene::Release()
{
	SAFE_DELETE(root);
	SOUND->AllStop();
}

void TitleScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	root->Render(memDC);
}
