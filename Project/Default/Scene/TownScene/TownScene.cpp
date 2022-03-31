#include "Stdafx/stdafx.h"

#include "Scene/TownScene/TownScene.h"

TownScene::TownScene() { }

TownScene::~TownScene() { }

HRESULT TownScene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_TOWNSCENE_DAY);
	root = NULL;

	GameObject* townToFieldBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::MOUSE_ON,
		std::bind(&SceneManager::SetNextSceneKeyFieldScene, SCENE),
		D_POINT{ 590, 25 }, 100, 50,
		IMG->FindImage(KEY_UI_TOWN_TO_FIELD_BUTTON_SPRITE));
	GameObject* townToGuildBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::MOUSE_ON,
		std::bind(&SceneManager::SetNextSceneKeyGuildScene, SCENE),
		D_POINT{ 340, 210 }, 100, 50,
		IMG->FindImage(KEY_UI_TOWN_TO_GUILD_BUTTON_SPRITE));
	GameObject* townToShopBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::MOUSE_ON,
		std::bind(&SceneManager::SetNextSceneKeyShopScene, SCENE),
		D_POINT{ 200, 230 }, 100, 50,
		IMG->FindImage(KEY_UI_TOWN_TO_SHOP_BUTTON_SPRITE));
	GameObject* townToTitleBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::MOUSE_ON,
		std::bind(&SceneManager::SetNextSceneKeyTitleScene, SCENE),
		D_POINT{ 590, 455 }, 100, 50,
		IMG->FindImage(KEY_UI_TOWN_TO_TITLE_BUTTON_SPRITE));

	root = new GameObject();
	root->AddGameObject(townToFieldBtn);
	root->AddGameObject(townToGuildBtn);
	root->AddGameObject(townToShopBtn);
	root->AddGameObject(townToTitleBtn);

	SOUND->Play(KEY_SOUND_TOWN_THEME, GAMEDATA->GetVolume());

	return S_OK;
}

void TownScene::Release()
{
	SAFE_DELETE(root);
}

void TownScene::Update()
{
	SOUND->Update();

	root->Update();
}

void TownScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
