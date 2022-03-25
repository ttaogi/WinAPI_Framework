#pragma once

#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")	//Multibyte.
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")	
#pragma comment(lib, "Winmm.lib") // mmsystem.h	//Unicode.

#include <malloc.h>
#include <memory.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <time.h>

#include <bitset>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <vector>

#include "DesignPattern/FactoryMethodBase/FactoryMethod.h"
#include "GameNode/MainGame/MainGame.h"
#include "Manager/CameraManager/CameraManager.h"
#include "Manager/DialogManager/DialogManager.h"
#include "Manager/FontManager/FontManager.h"
#include "Manager/GameDataManager/GameDataManager.h"
#include "Manager/ImageManager/ImageManager.h"
#include "Manager/JsonManager/JsonManager.h"
#include "Manager/KeyManager/KeyManager.h"
#include "Manager/MapDataManager/MapDataManager.h"
#include "Manager/SceneManager/SceneManager.h"
#include "Manager/SoundManager/SoundManager.h"
#include "Manager/TimeManager/TimeManager.h"
#include "Manager/XmlManager/XmlManager.h"
#include "Utility/CommonFunction/CommonFunction.h"
#include "Utility/Constants/Constants.h"
#include "Utility/Enums/Enums.h"
#include "Utility/RandomFunction/RandomFunction.h"

using namespace std;

#define WINNAME				    L"WindowsAPI"

#define WINSTART_X			    960
#define WINSTART_Y			    540
#define WINSIZE_X				640
#define WINSIZE_Y				480
#define WINSTYLE				WS_CAPTION | WS_SYSMENU

#define RND						RandomFunction::GetSingleton()
#define KEY						KeyManager::GetSingleton()
#define IMG						ImageManager::GetSingleton()
#define FONT					FontManager::GetSingleton()
#define TIME					TimeManager::GetSingleton()
#define SCENE					SceneManager::GetSingleton()
#define SOUND					SoundManager::GetSingleton()
#define XML						XmlManager::GetSingleton()
#define JSON					JsonManager::GetSingleton()
#define GAMEDATA				GameDataManager::GetSingleton()
#define MAPDATA					MapDataManager::GetSingleton()
#define CAMERA					CameraManager::GetSingleton()
#define DIALOG					DialogManager::GetSingleton()

#define FACTORY_METHOD_BUTTON	FactoryMethodButton::GetSingleton()
#define FACTORY_METHOD_BAR		FactoryMethodBar::GetSingleton()
#define FACTORY_METHOD_PLAYER	FactoryMethodPlayer::GetSingleton()
#define FACTORY_METHOD_PLATFORM	FactoryMethodPlatform::GetSingleton()

#define SAFE_RELEASE(p)			{if((p) != NULL) { (p)->Release();}}
#define SAFE_DELETE(p)			{if((p) != NULL) { delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if((p) != NULL) { delete[] (p); (p) = NULL;}}

extern HINSTANCE				HANDLE_INSTANCE;
extern HWND						HANDLE_WINDOW;
extern POINT					POINT_MOUSE;
extern MainGame*				MAIN_GAME;
extern bool						MOUSE_CLICKED;
