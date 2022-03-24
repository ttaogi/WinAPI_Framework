#include "Stdafx/stdafx.h"

#include "Scene/GuildScene/GuildScene.h"

GuildScene::GuildScene() { }

GuildScene::~GuildScene() { }

HRESULT GuildScene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_GUILD);
	root = NULL;

	GameObject* toTownBtn = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::MOUSE_ON,
		std::bind(&SceneManager::SetNextSceneKeyTownScene, SCENE),
		D_POINT{ 590, 455 }, 100, 50,
		IMG->FindImage(KEY_UI_TOWN_TO_FIELD_BUTTON_SPRITE));

	root = new GameObject();
	root->AddGameObject(toTownBtn);

	SOUND->Play(KEY_SOUND_TOWN_THEME, GAMEDATA->GetVolume());

	return S_OK;
}

void GuildScene::Release()
{
	SAFE_DELETE(root);
}

void GuildScene::Update()
{
	SOUND->Update();

	root->Update();
}

void GuildScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
