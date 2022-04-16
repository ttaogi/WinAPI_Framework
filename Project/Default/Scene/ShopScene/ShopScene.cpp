#include "Stdafx/stdafx.h"

#include "Scene/ShopScene/ShopScene.h"

#include "DesignPattern/ObserverBase/Subject.h"
#include "Script/DialogViewer/DialogViewer.h"
#include "Script/ShopList/ShopList.h"

ShopScene::ShopScene() { }

ShopScene::~ShopScene() { }

void ShopScene::OnNotify(Subject* _subject, EVENT _event)
{
	switch (_event)
	{
	case EVENT::DIALOG_CLICK:
		if(GAMEMANAGER->GetPhase() == PHASE::PHASE_DIALOG)
		{
			GameObject* dialogViewer = root->GetGameObjectByName(SKIG_DIALOG_VIEWER);
			DialogViewer* dv = dialogViewer->GetComponent<DialogViewer>();

			if (dv)
			{
				if (dv->IsEnd())
				{
					dialogViewer->SetActive(false);
					GameObject* shopList = root->GetGameObjectByName(SKIG_SHOP_LIST);
					if (shopList) shopList->SetActive(true);
					GAMEMANAGER->SetPhase(PHASE::PHASE_SHOPPING);
				}
				else
					dv->Next();
			}
		}
		break;
	case EVENT::EXIT_BUTTON_CLICK:
		if (GAMEMANAGER->GetPhase() == PHASE::PHASE_SHOPPING)
			SCENE->SetNextSceneKeyTownScene();
		break;
	case EVENT::SHOP_LIST_TO_EQUIP_CHANGE_BUTTON_CLICK:
	{
		GameObject* shopList = root->GetGameObjectByName(SKIG_SHOP_LIST);
		GameObject* equipChange = root->GetGameObjectByName(SKIG_EQUIP_CHANGE);
		if (shopList && equipChange)
		{
			shopList->SetActive(false);
			equipChange->SetActive(true);
		}
	}
		break;
	case EVENT::EQUIP_CHANGE_TO_SHOP_LIST_BUTTON_CLICK:
	{
		GameObject* shopList = root->GetGameObjectByName(SKIG_SHOP_LIST);
		GameObject* equipChange = root->GetGameObjectByName(SKIG_EQUIP_CHANGE);
		if (shopList && equipChange)
		{
			shopList->SetActive(true);
			equipChange->SetActive(false);
		}
	}
		break;
	}
}

HRESULT ShopScene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_SHOP);
	root = NULL;

	GameObject* dialogViewer = FACTORY_METHOD_DIALOGVIEWER->CreateObject(this, DIALOG_SPOT_SHOP, -1);
	GameObject* shopList = FACTORY_METHOD_SHOPLIST->CreateObject(this);
	shopList->SetActive(false);
	GameObject* equipChange = FACTORY_METHOD_EQUIPCHANGE->CreateObject(this);
	equipChange->SetActive(false);

	root = new GameObject();
	root->AddGameObject(dialogViewer);
	root->AddGameObject(shopList);
	root->AddGameObject(equipChange);

	SOUND->Play(KEY_SOUND_TOWN_THEME, GAMEDATA->GetVolume());

	GAMEMANAGER->SetPhase(PHASE::PHASE_DIALOG);

	return S_OK;
}

void ShopScene::Release()
{
	SAFE_DELETE(root);
}

void ShopScene::Update()
{
	SOUND->Update();

	root->Update();
}

void ShopScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
