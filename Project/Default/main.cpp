#pragma warning(disable: 28251)

#include "Stdafx/stdafx.h"

#include "Image/Image.h"

HINSTANCE		HANDLE_INSTANCE;
HWND			HANDLE_WINDOW;
POINT			POINT_MOUSE;
MainGame*		MAIN_GAME;
bool			MOUSE_CLICKED;
bool			MOUSE_CLICKED_RIGHT;

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
	//JSON->Init();
	GAMEDATA->Init();
	MAPDATA->Init();
	CAMERA->Init(NULL);
	DIALOG->Init();
	GAMEMANAGER->Init();
	
	// backbuffer.
	IMG->AddImage(KEY_BACKGROUND_BACKBUFFER, BACKGROUND_BACKBUFFER, WINSIZE_X, WINSIZE_Y)
		->InitForAlphaBlend();
	
	// background.
	IMG->AddImage(KEY_BACKGROUND_ENDSCENE, BACKGROUND_ENDSCENE, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_BACKGROUND_TITLESCENE, BACKGROUND_TITLESCENE, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddImage(KEY_BACKGROUND_TOWNSCENE_DAY, BACKGROUND_TOWNSCENE_DAY, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_BACKGROUND_TOWNSCENE_NIGHT, BACKGROUND_TOWNSCENE_NIGHT, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddImage(KEY_BACKGROUND_GUILD, BACKGROUND_GUILD, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddImage(KEY_BACKGROUND_SHOP, BACKGROUND_SHOP, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddImage(KEY_BACKGROUND_FIELD, BACKGROUND_FIELD, WINSIZE_X, WINSIZE_Y, false, MAGENTA)
		->InitForAlphaBlend();
	
	// ui button.
	IMG->AddImage(KEY_UI_QUIT_BUTTON_SPRITE, UI_QUIT_BUTTON_SPRITE, BUTTON_WIDTH, BUTTON_HEIGHT, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_RETRY_BUTTON_SPRITE, UI_RETRY_BUTTON_SPRITE, BUTTON_WIDTH, BUTTON_HEIGHT, true, MAGENTA)
		->InitForAlphaBlend();

	// ui button mouse on.
	IMG->AddImage(KEY_UI_TOWN_TO_FIELD_BUTTON_SPRITE, UI_TOWN_TO_FIELD_BUTTON_SPRITE, 100, 50, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_TOWN_TO_GUILD_BUTTON_SPRITE, UI_TOWN_TO_GUILD_BUTTON_SPRITE, 100, 50, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_TOWN_TO_SHOP_BUTTON_SPRITE, UI_TOWN_TO_SHOP_BUTTON_SPRITE, 100, 50, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_TOWN_TO_TITLE_BUTTON_SPRITE, UI_TOWN_TO_TITLE_BUTTON_SPRITE, 100, 50, true, MAGENTA)
		->InitForAlphaBlend();
	
	// ui bar.
	IMG->AddImage(KEY_UI_BAR_BACKGROUND_SPRITE, DIR_UI_BAR_BACKGROUND_SPRITE, 20, 20, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_BAR_GUAGE_SPRITE, DIR_UI_BAR_GUAGE_SPRITE, 20, 20, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_BAR_BORDER_SPRITE, DIR_UI_BAR_BORDER_SPRITE, 20, 20, false, MAGENTA)
		->InitForAlphaBlend();

	// ui hp bar.
	IMG->AddImage(KEY_UI_HP_BAR_BACKGROUND_SPRITE, DIR_UI_HP_BAR_BACKGROUND_SPRITE, 20, 20, false, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_HP_BAR_HP_SPRITE, DIR_UI_HP_BAR_HP_SPRITE, 20, 20, false, MAGENTA)
		->InitForAlphaBlend();

	// ui dialog.
	IMG->AddImage(KEY_UI_DIALOG_BACKGROUND_SPRITE, DIR_UI_DIALOG_BACKGROUND_SPRITE, 640, 160, true, MAGENTA)
		->InitForAlphaBlend();

	// ui shop.
	IMG->AddImage(KEY_UI_SHOPLIST_BACKGROUND_SPRITE, DIR_UI_SHOPLIST_BACKGROUND_SPRITE, 420, 378, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_SHOPLIST_PANEL_BACKGROUND_SPRITE, DIR_UI_SHOPLIST_PANEL_BACKGROUND_SPRITE, 412, 25, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_SHOPLIST_BUY_BUTTON_SPRITE, DIR_UI_SHOPLIST_BUY_BUTTON_SPRITE, 112, 21, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_SHOPLIST_EXIT_BUTTON_SPRITE, DIR_UI_SHOPLIST_EXIT_BUTTON_SPRITE, 112, 21, true, MAGENTA)
		->InitForAlphaBlend();

	// ui equip change.
	IMG->AddImage(KEY_UI_EQUIP_CHANGE_BACKGROUND_SPRITE, DIR_UI_EQUIP_CHANGE_BACKGROUND_SPRITE, 605, 438, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddImage(KEY_UI_EQUIP_CHANGE_PORTRAIT_AL_SPRITE, DIR_UI_EQUIP_CHANGE_PORTRAIT_AL_SPRITE, 128, 88, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_EQUIP_CHANGE_PORTRAIT_KARIN_SPRITE, DIR_UI_EQUIP_CHANGE_PORTRAIT_KARIN_SPRITE, 128, 88, true, MAGENTA)
		->InitForAlphaBlend();

	// tile.
	IMG->AddImage(KEY_TILE_PANEL, DIR_TILE_PANEL, TILE_WIDTH, TILE_HEIGHT_Z0, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_TILE_FOCUS, DIR_TILE_FOCUS, TILE_WIDTH, TILE_HEIGHT_Z0, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddImage(KEY_TILE_DIRT_Z0_SPRITE, DIR_TILE_DIRT_Z0_SPRITE, TILE_WIDTH, TILE_HEIGHT_Z0, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_TILE_DIRT_Z1_SPRITE, DIR_TILE_DIRT_Z1_SPRITE, TILE_WIDTH, TILE_HEIGHT_Z1, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_TILE_GRASS_Z0_SPRITE, DIR_TILE_GRASS_Z0_SPRITE, TILE_WIDTH, TILE_HEIGHT_Z0, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_TILE_GRASS_Z1_SPRITE, DIR_TILE_GRASS_Z1_SPRITE, TILE_WIDTH, TILE_HEIGHT_Z1, true, MAGENTA)
		->InitForAlphaBlend();

	// portrait.
	IMG->AddImage(KEY_UI_PORTRAIT_AL_DEFAULT_SPRITE, DIR_UI_PORTRAIT_AL_DEFAULT_SPRITE, 240, 192, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_PORTRAIT_GUILD_DEFAULT_SPRITE, DIR_UI_PORTRAIT_GUILD_DEFAULT_SPRITE, 240, 192, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_PORTRAIT_KARIN_DEFAULT_SPRITE, DIR_UI_PORTRAIT_KARIN_DEFAULT_SPRITE, 240, 192, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddImage(KEY_UI_PORTRAIT_SHOP_DEFAULT_SPRITE, DIR_UI_PORTRAIT_SHOP_DEFAULT_SPRITE, 240, 192, true, MAGENTA)
		->InitForAlphaBlend();
	
	// player.
	IMG->AddFrameImage(KEY_AL_IDLE_LEFT_BOTTOM, DIR_AL_IDLE_LEFT_BOTTOM, 168, 64, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_IDLE_LEFT_TOP, DIR_AL_IDLE_LEFT_TOP, 168, 64, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_IDLE_RIGHT_BOTTOM, DIR_AL_IDLE_RIGHT_BOTTOM, 168, 64, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_IDLE_RIGHT_TOP, DIR_AL_IDLE_RIGHT_TOP, 168, 64, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddFrameImage(KEY_AL_MOVE_LEFT_BOTTOM, DIR_AL_MOVE_LEFT_BOTTOM, 176, 72, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_MOVE_LEFT_TOP, DIR_AL_MOVE_LEFT_TOP, 176, 72, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_MOVE_RIGHT_BOTTOM, DIR_AL_MOVE_RIGHT_BOTTOM, 176, 72, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_MOVE_RIGHT_TOP, DIR_AL_MOVE_RIGHT_TOP, 176, 72, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddFrameImage(KEY_AL_ATTACK_LEFT_BOTTOM, DIR_AL_ATTACK_LEFT_BOTTOM, 640, 88, 8, 1, 8, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_ATTACK_LEFT_TOP, DIR_AL_ATTACK_LEFT_TOP, 640, 88, 8, 1, 8, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_ATTACK_RIGHT_BOTTOM, DIR_AL_ATTACK_RIGHT_BOTTOM, 640, 88, 8, 1, 8, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_AL_ATTACK_RIGHT_TOP, DIR_AL_ATTACK_RIGHT_TOP, 640, 88, 8, 1, 8, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddFrameImage(KEY_KARIN_IDLE_LEFT_BOTTOM, DIR_KARIN_IDLE_LEFT_BOTTOM, 204, 64, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_IDLE_LEFT_TOP, DIR_KARIN_IDLE_LEFT_TOP, 204, 64, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_IDLE_RIGHT_BOTTOM, DIR_KARIN_IDLE_RIGHT_BOTTOM, 204, 64, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_IDLE_RIGHT_TOP, DIR_KARIN_IDLE_RIGHT_TOP, 204, 64, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddFrameImage(KEY_KARIN_MOVE_LEFT_BOTTOM, DIR_KARIN_MOVE_LEFT_BOTTOM, 288, 64, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_MOVE_LEFT_TOP, DIR_KARIN_MOVE_LEFT_TOP, 288, 64, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_MOVE_RIGHT_BOTTOM, DIR_KARIN_MOVE_RIGHT_BOTTOM, 288, 64, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_MOVE_RIGHT_TOP, DIR_KARIN_MOVE_RIGHT_TOP, 288, 64, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddFrameImage(KEY_KARIN_ATTACK_LEFT_BOTTOM, DIR_KARIN_ATTACK_LEFT_BOTTOM, 272, 264, 4, 3, 11, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_ATTACK_LEFT_TOP, DIR_KARIN_ATTACK_LEFT_TOP, 272, 264, 4, 3, 11, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_ATTACK_RIGHT_BOTTOM, DIR_KARIN_ATTACK_RIGHT_BOTTOM, 272, 264, 4, 3, 11, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_KARIN_ATTACK_RIGHT_TOP, DIR_KARIN_ATTACK_RIGHT_TOP, 272, 264, 4, 3, 11, true, MAGENTA)
		->InitForAlphaBlend();

	// enemy.
	IMG->AddFrameImage(KEY_SLIME_IDLE, DIR_SLIME_IDLE, 126, 36, 3, 1, 3, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_SLIME_MOVE, DIR_SLIME_MOVE, 168, 40, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddFrameImage(KEY_SLIME_ATTACK_LEFT_BOTTOM, DIR_SLIME_ATTACK_LEFT_BOTTOM, 424, 240, 4, 3, 11, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_SLIME_ATTACK_LEFT_TOP, DIR_SLIME_ATTACK_LEFT_TOP, 424, 240, 4, 3, 11, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_SLIME_ATTACK_RIGHT_BOTTOM, DIR_SLIME_ATTACK_RIGHT_BOTTOM, 424, 240, 4, 3, 11, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_SLIME_ATTACK_RIGHT_TOP, DIR_SLIME_ATTACK_RIGHT_TOP, 424, 240, 4, 3, 11, true, MAGENTA)
		->InitForAlphaBlend();

	IMG->AddFrameImage(KEY_SLIME_ATTACKED_LEFT, DIR_SLIME_ATTACKED_LEFT, 160, 48, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();
	IMG->AddFrameImage(KEY_SLIME_ATTACKED_RIGHT, DIR_SLIME_ATTACKED_RIGHT, 160, 48, 4, 1, 4, true, MAGENTA)
		->InitForAlphaBlend();

	// effect.
	IMG->AddFrameImage(KEY_EFFECT_FLAME_BURST, DIR_EFFECT_FLAME_BURST, 560, 1000, 4, 5, 17, true, MAGENTA)
		->InitForAlphaBlend();
	
	////// sound.
	SOUND->AddSound(KEY_SOUND_EXAMPLE, DIR_SOUND_EXAMPLE, true, true);
	SOUND->AddSound(KEY_SOUND_TITLE_THEME, DIR_SOUND_TITLE_THEME, true, true);
	SOUND->AddSound(KEY_SOUND_TOWN_THEME, DIR_SOUND_TOWN_THEME, true, true);
	SOUND->AddSound(KEY_SOUND_FIELD_THEME, DIR_SOUND_FIELD_THEME, true, true);
	SOUND->AddSound(KEY_SOUND_FLAME_BURST, DIR_SOUND_FLAME_BURST, false, false);
	SOUND->AddSound(KEY_SOUND_SLASH, DIR_SOUND_SLASH, false, false);
	SOUND->AddSound(KEY_SOUND_SLIME_ATTACK, DIR_SOUND_SLIME_ATTACK, false, false);
}

void ReleaseResources()
{
	// singleton release.
	GAMEMANAGER->Release();
	GAMEMANAGER->ReleaseSingleton();
	DIALOG->Release();
	DIALOG->ReleaseSingleton();
	CAMERA->Release();
	CAMERA->ReleaseSingleton();
	MAPDATA->Release();
	MAPDATA->ReleaseSingleton();
	GAMEDATA->Release();
	GAMEDATA->ReleaseSingleton();
	//JSON->Release();
	//JSON->ReleaseSingleton();
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
