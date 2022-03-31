#include "Stdafx/stdafx.h"

#include "Scene/FieldScene/FieldScene.h"

FieldScene::FieldScene() { }

FieldScene::~FieldScene() { }

void FieldScene::OnNotify(Subject* _subject, EVENT _event)
{
	switch (_event)
	{
	case EVENT::TILE_CLICK:
		wcout << L"Tile Click." << endl;
		break;
	}
}

HRESULT FieldScene::Init()
{
	SOUND->AllStop();
	
	backgroundImage = IMG->FindImage(KEY_BACKGROUND_FIELD);
	root = NULL;

	MapData mapData;
	if (!MAPDATA->GetMapData(XML_DOC_FIELD_MAP_DATA, this, mapData)) return E_FAIL;

	GameObject* toTownButton = FACTORY_METHOD_BUTTON->CreateObject(
		BUTTON_FACTORY_TYPE::MOUSE_ON,
		std::bind(&SceneManager::SetNextSceneKeyTownScene, SCENE),
		D_POINT{ 590, 455 }, 100, 50,
		IMG->FindImage(KEY_UI_TOWN_TO_FIELD_BUTTON_SPRITE));

	root = new GameObject();
	LoadMapData(&mapData);
	root->AddGameObject(toTownButton);

	SOUND->Play(KEY_SOUND_FIELD_THEME, GAMEDATA->GetVolume());

	CAMERA->SetTarget(mapData.tileVec[2][2]);
	CAMERA->Update();

	GAMEMANAGER->SetPhase(PHASE::PHASE_DIALOG);

	return S_OK;
}

void FieldScene::Release()
{
	CAMERA->SetTarget(NULL);
	CAMERA->Update();
	SAFE_DELETE(root);
}

void FieldScene::Update()
{
	SOUND->Update();

	root->Update();

	CAMERA->Update();
}

void FieldScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
