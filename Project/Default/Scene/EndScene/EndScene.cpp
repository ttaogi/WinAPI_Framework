#include "Stdafx/stdafx.h"

#include "EndScene.h"

#include <functional>

#include "DesignPattern/AbstractFactoryBase/AbstractFactoryBase.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"

EndScene::EndScene() { }

EndScene::~EndScene() { Release(); }

HRESULT EndScene::Init()
{
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_ENDSCENE);

	RECT quitBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* quitBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&MainGame::QuitGame, MAIN_GAME),
			&quitBtnRc,
			IMG->FindImage(KEY_UI_QUIT_BUTTON_STRIPE));
	quitBtn->SetTag(TAG_QUIT_BUTTON);
	quitBtn->GetComponent<Transform>()
		->SetPosition(D_POINT{ (double)(WINSIZE_X / 2 - BUTTON_WIDTH - 50), (double)(WINSIZE_Y - 100) });
	gameObjects.push_back(quitBtn);

	RECT retryBtnRc{ 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	GameObject* retryBtn = AbstractFactoryButton::GetSingleton()
		->GetObject(BUTTON_FACTORY_TYPE::DEFAULT,
			std::bind(&SceneManager::SetNextSceneKeyOnGameScene, SCENE),
			&retryBtnRc,
			IMG->FindImage(KEY_UI_RETRY_BUTTON_STRIPE));
	retryBtn->SetTag(TAG_RETRY_BUTTON);
	retryBtn->GetComponent<Transform>()
		->SetPosition(D_POINT{ (double)(WINSIZE_X / 2 + BUTTON_WIDTH + 50), (double)(WINSIZE_Y - 100) });
	gameObjects.push_back(retryBtn);

	return S_OK;
}

void EndScene::Update() {
	for (GameObject* go : gameObjects)
		if (go->GetActive())
			for (Component* c : go->cList)
			{
				MonoBehaviour* m = IsDerivedFromMonoBehaviour(c);
				if (m != NULL) m->Update();
			}
}

void EndScene::Release()
{
	for (GameObject* go : gameObjects) SAFE_DELETE(go);
	gameObjects.clear();
	SOUND->AllStop();
}

void EndScene::Render()
{
	HDC memDC = MAIN_GAME->GetBackBuffer()->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC, 0, 0);

	for (GameObject* go : gameObjects)
		if (go->GetActive()) {
			RenderedImage* rImg = go->GetComponent<RenderedImage>();
			if (rImg) rImg->Render(memDC);
		}
}
