#include "Stdafx/stdafx.h"

#include "Scene/GuildScene/GuildScene.h"

#include "DesignPattern/ObserverBase/Subject.h"
#include "Script/DialogViewer/DialogViewer.h"

GuildScene::GuildScene() { }

GuildScene::~GuildScene() { }

void GuildScene::OnNotify(Subject* _subject, EVENT _event)
{
	switch (_event)
	{
	case EVENT::DIALOG_CLICK:
		if (GAMEMANAGER->GetPhase() == PHASE::PHASE_DIALOG)
		{
			GameObject* dialogViewer = root->GetGameObjectByName(SKIG_DIALOG_VIEWER);
			DialogViewer* dv = dialogViewer->GetComponent<DialogViewer>();

			if (dv)
				if (dv->IsEnd())
				{
					if (GAMEDATA->GetProcessivity() == 0) GAMEDATA->SetProcessivity(1);
					SCENE->SetNextSceneKeyTownScene();
				}
				else dv->Next();
		}
		break;
	}
}

HRESULT GuildScene::Init()
{
	SOUND->AllStop();

	backgroundImage = IMG->FindImage(KEY_BACKGROUND_GUILD);
	root = NULL;

	GameObject* dialogViewer = FACTORY_METHOD_DIALOGVIEWER->CreateObject(this, DIALOG_SPOT_GUILD, GAMEDATA->GetProcessivity());

	root = new GameObject();
	root->AddGameObject(dialogViewer);

	SOUND->Play(KEY_SOUND_TOWN_THEME, GAMEDATA->GetVolume());

	GAMEMANAGER->SetPhase(PHASE::PHASE_DIALOG);

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
