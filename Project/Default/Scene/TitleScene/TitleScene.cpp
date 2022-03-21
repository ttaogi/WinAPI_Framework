#include "Stdafx/stdafx.h"

#include "TitleScene.h"

#include <functional>

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"

TitleScene::TitleScene() { }

TitleScene::~TitleScene() { }

HRESULT TitleScene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_TITLESCENE);
	root = NULL;

	GameObject* gameStartBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyLobbyScene, SCENE),
		D_POINT{ WINSIZE_X / 2, WINSIZE_Y * 3 / 4 }, 400, 50,
		IMG->FindImage(KEY_UI_START_BUTTON_STRIPE));

	root = new GameObject();
	root->AddGameObject(gameStartBtn);

	SOUND->Play(KEY_SOUND_TITLE_THEME, GAMEDATA->GetVolume());

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
}

void TitleScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
