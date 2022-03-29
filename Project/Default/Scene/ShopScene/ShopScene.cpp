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

	root = new GameObject();
	root->AddGameObject(dialogViewer);
	root->AddGameObject(shopList);

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
