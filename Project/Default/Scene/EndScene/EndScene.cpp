#include "Stdafx/stdafx.h"

#include "EndScene.h"

#include <functional>

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"

EndScene::EndScene() { }

EndScene::~EndScene() { Release(); }

HRESULT EndScene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_ENDSCENE);
	root = NULL;

	GameObject* quitBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&MainGame::QuitGame, MAIN_GAME),
		D_POINT{ (double)(WINSIZE_X / 2 - BUTTON_WIDTH - 50), (double)(WINSIZE_Y / 2) },
		BUTTON_WIDTH, BUTTON_HEIGHT,
		IMG->FindImage(KEY_UI_QUIT_BUTTON_SPRITE));
	quitBtn->SetName(NAME_QUIT_BUTTON);

	GameObject* retryBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::DEFAULT,
		std::bind(&SceneManager::SetNextSceneKeyTitleScene, SCENE),
		D_POINT{ (double)(WINSIZE_X / 2 + BUTTON_WIDTH + 50), (double)(WINSIZE_Y / 2) },
		BUTTON_WIDTH, BUTTON_HEIGHT,
		IMG->FindImage(KEY_UI_RETRY_BUTTON_SPRITE));
	retryBtn->SetName(NAME_RETRY_BUTTON);

	root = new GameObject();
	root->AddGameObject(quitBtn);
	root->AddGameObject(retryBtn);

	return S_OK;
}

void EndScene::Update() {
	root->Update();
}

void EndScene::Release()
{
	SAFE_DELETE(root);
}

void EndScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
