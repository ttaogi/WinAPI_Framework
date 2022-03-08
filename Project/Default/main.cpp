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

	// backbuffer.
	IMG->AddImage(KEY_BACKGROUND_BACKBUFFER, BACKGROUND_BACKBUFFER, WINSIZE_X, WINSIZE_Y);

	// background.
	IMG->AddImage(KEY_BACKGROUND_ENDSCENE, BACKGROUND_ENDSCENE, 1280, 800, false, MAGENTA);
	IMG->FindImage(KEY_BACKGROUND_ENDSCENE)->InitForAlphaBlend();
	IMG->AddImage(KEY_BACKGROUND_TITLESCENE, BACKGROUND_TITLESCENE, 1280, 800, false, MAGENTA);
	IMG->FindImage(KEY_BACKGROUND_TITLESCENE)->InitForAlphaBlend();
	IMG->AddImage(KEY_BACKGROUND_ONGAMESCENE, BACKGROUND_ONGAMESCENE, 1280, 800, false, MAGENTA);
	IMG->FindImage(KEY_BACKGROUND_ONGAMESCENE)->InitForAlphaBlend();

	IMG->AddImage(KEY_UI_QUIT_BUTTON_STRIPE, UI_QUIT_BUTTON_STRIPE, 200, 150, false, MAGENTA);
	IMG->AddImage(KEY_UI_RETRY_BUTTON_STRIPE, UI_RETRY_BUTTON_STRIPE, 200, 150, false, MAGENTA);
	IMG->AddImage(KEY_UI_START_BUTTON_STRIPE, UI_START_BUTTON_STRIPE, 200, 150, false, MAGENTA);

	////// sound.
	SOUND->AddSound(KEY_SOUND_EXAMPLE, SOUND_EXAMPLE, true, true);
}

void ReleaseResources()
{
	// singleton release.
	XML->Release();
	XML->ReleaseSingleton();
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
