#pragma warning(disable:28251)
#include "Stdafx/stdafx.h"

#include "MainGame.h"

#include "Image/Image.h"
#include "Manager/SceneManager/SceneManager.h"
#include "Scene/EndScene/EndScene.h"
#include "Scene/LobbyScene/LobbyScene.h"
#include "Scene/OnGameScene/OnGameScene.h"
#include "Scene/Stage1Scene/Stage1Scene.h"
#include "Scene/Stage2Scene/Stage2Scene.h"
#include "Scene/Stage3Scene/Stage3Scene.h"
#include "Scene/Stage4Scene/Stage4Scene.h"
#include "Scene/TitleScene/TitleScene.h"

MainGame::MainGame()
{
	quit = false;
	nodeHdc = NULL;
}

MainGame::~MainGame() { Release(); }

HRESULT MainGame::Init()
{
	nodeHdc = GetDC(HANDLE_WINDOW);

	SetBackBuffer(IMG->FindImage(KEY_BACKGROUND_BACKBUFFER));

	SCENE->AddScene(KEY_END_SCENE, new EndScene());
	SCENE->AddScene(KEY_LOBBY_SCENE, new LobbyScene());
	SCENE->AddScene(KEY_ONGAME_SCENE, new OnGameScene());
	SCENE->AddScene(KEY_TITLE_SCENE, new TitleScene());
	SCENE->AddScene(KEY_STAGE_1_SCENE, new Stage1Scene());
	SCENE->AddScene(KEY_STAGE_2_SCENE, new Stage2Scene());
	SCENE->AddScene(KEY_STAGE_3_SCENE, new Stage3Scene());
	SCENE->AddScene(KEY_STAGE_4_SCENE, new Stage4Scene());
	SCENE->ChangeScene(KEY_TITLE_SCENE);

	return S_OK;
}

void MainGame::Release() { ReleaseDC(HANDLE_WINDOW, nodeHdc); }

void MainGame::Update()
{
	if (quit == true)
	{
		Release();
		PostQuitMessage(0);
		return;
	}

	TIME->Update(60.0f);

	MOUSE_CLICKED = false;
	GetCursorPos(&POINT_MOUSE);
	ScreenToClient(HANDLE_WINDOW, &POINT_MOUSE);
	if (KEY->IsOnceKeyDown(VK_LBUTTON)) MOUSE_CLICKED = true;

	SCENE->Update();
}

void MainGame::Render()
{
	SCENE->Render();
	TIME->Render(GetMemDC());
	GetBackBuffer()->Render(GetHDC());
}

LRESULT MainGame::MainProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		switch (_wParam)
		{
		case 1:
			Update();
			break;
		}
		break;
	case WM_PAINT:
		Render();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return GameNode::MainProc(_hWnd, _message, _wParam, _lParam);
}

void MainGame::QuitGame() {	quit = true; }
