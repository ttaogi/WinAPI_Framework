#pragma warning(disable: 28251)

#include "Stdafx/stdafx.h"

#include "Image/Image.h"

HINSTANCE		HANDLE_INSTANCE;
HWND			HANDLE_WINDOW;
POINT			POINT_MOUSE;
MainGame*		MAIN_GAME;
bool			MOUSE_CLICKED;

void SetWindowSize(int _x, int _y, int _width, int _height);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void LoadResources();
void ReleaseResources();

int APIENTRY wWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPWSTR _lpCmdLine, int _nCmdShow)
{
	LoadResources();

	MAIN_GAME = new MainGame();
	MOUSE_CLICKED = false;

	HANDLE_INSTANCE = _hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	HANDLE_WINDOW = CreateWindow(WINNAME, WINNAME,
		WINSTYLE, WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y,
		NULL, (HMENU)NULL, _hInstance, NULL);

	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	ShowWindow(HANDLE_WINDOW, _nCmdShow);

	if (FAILED(MAIN_GAME->Init()))	return 0;

	MSG message;

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			MAIN_GAME->Update();
			MAIN_GAME->Render();
		}
	}

	ReleaseResources();

	return (int)message.wParam;
}

void SetWindowSize(int _x, int _y, int _width, int _height)
{
	RECT rc{ 0, 0, _width, _height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(HANDLE_WINDOW, NULL, _x, _y,
		(rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	return MAIN_GAME->MainProc(_hWnd, _message, _wParam, _lParam);
}

void LoadResources()
{
	// singleton init.
	IMG->Init();
	_wsetlocale(LC_ALL, L"Korean");
	TIME->Init();
	SCENE->Init();
	SOUND->Init();
	XML->Init();
	JSON->Init();
	GAMEDATA->Init();
	MAPDATA->Init();
	CAMERA->Init(NULL);
	
	// backbuffer.
	IMG->AddImage(KEY_BACKGROUND_BACKBUFFER, BACKGROUND_BACKBUFFER, WINSIZE_X, WINSIZE_Y)
		->InitForAlphaBlend();
	
	// background.
	IMG->AddImage(KEY_BACKGROUND_ENDSCENE, BACKGROUND_ENDSCENE, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_BACKGROUND_TITLESCENE, BACKGROUND_TITLESCENE, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_BACKGROUND_ONGAMESCENE, BACKGROUND_ONGAMESCENE, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_BACKGROUND_LOBBYSCENE, BACKGROUND_LOBBYSCENE, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddImage(KEY_BACKGROUND_STAGE_1, BACKGROUND_STAGE_1, 1350, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();
	
	// ui button.
	IMG->AddImage(KEY_UI_QUIT_BUTTON_SPRITE, UI_QUIT_BUTTON_SPRITE, BUTTON_WIDTH, BUTTON_HEIGHT, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_RETRY_BUTTON_SPRITE, UI_RETRY_BUTTON_SPRITE, BUTTON_WIDTH, BUTTON_HEIGHT, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_START_BUTTON_SPRITE, UI_START_BUTTON_SPRITE, 400, 50, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddImage(KEY_UI_STAGE_1_BUTTON_SPRITE, UI_STAGE_1_BUTTON_SPRITE, 415, 155, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_STAGE_2_BUTTON_SPRITE, UI_STAGE_2_BUTTON_SPRITE, 415, 155, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_STAGE_3_BUTTON_SPRITE, UI_STAGE_3_BUTTON_SPRITE, 415, 155, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_STAGE_4_BUTTON_SPRITE, UI_STAGE_4_BUTTON_SPRITE, 415, 155, true, MAGENTA)
		->InitForAlphaBlend();
	
	// ui bar.
	IMG->AddImage(KEY_UI_BAR_BACKGROUND_SPRITE, DIR_UI_BAR_BACKGROUND_SPRITE, 20, 20, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_BAR_GUAGE_SPRITE, DIR_UI_BAR_GUAGE_SPRITE, 20, 20, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_BAR_BORDER_SPRITE, DIR_UI_BAR_BORDER_SPRITE, 20, 20, false, MAGENTA)
		->InitForAlphaBlend();
	
	// platform.
	IMG->AddImage(KEY_PLATFORM_DEFAULT_SPRITE, DIR_PLATFORM_DEFAULT_SPRITE, 80, 20, false, MAGENTA)
		->InitForAlphaBlend();
	
	// player.
	IMG->AddImage(KEY_PLAYER_TEMP_SPRITE, DIR_PLAYER_TEMP_SPRITE, 80, 80, false, MAGENTA)
		->InitForAlphaBlend();
	
	////// sound.
	SOUND->AddSound(KEY_SOUND_EXAMPLE, DIR_SOUND_EXAMPLE, true, true);
	SOUND->AddSound(KEY_SOUND_TITLE_THEME, DIR_SOUND_TITLE_THEME, true, true);
	SOUND->AddSound(KEY_SOUND_LOBBY_THEME, DIR_SOUND_LOBBY_THEME, true, true);

	SOUND->AddSound(KEY_SOUND_STAGE_1_NORMAL, DIR_SOUND_STAGE_1_NORMAL, true, true);
	SOUND->AddSound(KEY_SOUND_STAGE_2_NORMAL, DIR_SOUND_STAGE_2_NORMAL, true, true);
	SOUND->AddSound(KEY_SOUND_STAGE_3_NORMAL, DIR_SOUND_STAGE_3_NORMAL, true, true);
	SOUND->AddSound(KEY_SOUND_STAGE_4_NORMAL, DIR_SOUND_STAGE_4_NORMAL, true, true);
}

void ReleaseResources()
{
	// singleton release.
	MAPDATA->Release();
	MAPDATA->ReleaseSingleton();
	GAMEDATA->Release();
	GAMEDATA->ReleaseSingleton();
	JSON->Release();
	JSON->ReleaseSingleton();
	XML->Release();
	XML->ReleaseSingleton();
	SOUND->AllStop();
	SOUND->Release();
	SOUND->ReleaseSingleton();
	SCENE->Release();
	SCENE->ReleaseSingleton();
	TIME->Release();
	TIME->ReleaseSingleton();
	FONT->ReleaseSingleton();
	IMG->Release();
	IMG->ReleaseSingleton();
	KEY->ReleaseSingleton();
	RND->ReleaseSingleton();
}
