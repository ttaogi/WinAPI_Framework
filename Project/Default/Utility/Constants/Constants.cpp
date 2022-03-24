#include "Stdafx/stdafx.h"

#include "Constants.h"

#pragma region Sprite
#pragma region Background
const std::wstring KEY_BACKGROUND_BACKBUFFER =
	L"BACKGROUND_BACKBUFFER";
const wchar_t* BACKGROUND_BACKBUFFER =
	L"Resources/Images/BackGround/BackBuffer.bmp";

const std::wstring KEY_BACKGROUND_ENDSCENE =
	L"BACKGROUND_ENDSCENE";
const wchar_t* BACKGROUND_ENDSCENE =
	L"Resources/Images/BackGround/BackgroundEndScene.bmp";

const std::wstring KEY_BACKGROUND_TITLESCENE =
	L"BACKGROUND_TITLESCENE";
const wchar_t* BACKGROUND_TITLESCENE =
	L"Resources/Images/BackGround/BackgroundTitleScene.bmp";

const std::wstring KEY_BACKGROUND_TOWNSCENE_DAY =
	L"BACKGROUND_TOWNSCENE_DAY";
const wchar_t* BACKGROUND_TOWNSCENE_DAY =
	L"Resources/Images/BackGround/BackgroundTownDay.bmp";
const std::wstring KEY_BACKGROUND_TOWNSCENE_NIGHT =
	L"BACKGROUND_TOWNSCENE_NIGHT";
const wchar_t* BACKGROUND_TOWNSCENE_NIGHT =
	L"Resources/Images/BackGround/BackgroundTownNight.bmp";

const std::wstring KEY_BACKGROUND_GUILD =
	L"BACKGROUND_GUILD";
const wchar_t* BACKGROUND_GUILD =
	L"Resources/Images/BackGround/BackgroundGuild.bmp";

const std::wstring KEY_BACKGROUND_SHOP =
	L"BACKGROUND_SHOP";
const wchar_t* BACKGROUND_SHOP =
	L"Resources/Images/BackGround/BackgroundShop.bmp";
#pragma endregion Background


#pragma region Ui_Button
const std::wstring KEY_UI_QUIT_BUTTON_SPRITE =
	L"UI_QUIT_BUTTON_SPRITE";
const wchar_t* UI_QUIT_BUTTON_SPRITE =
	L"Resources/Images/UI/Button/QuitButton.bmp";
const std::wstring KEY_UI_RETRY_BUTTON_SPRITE =
	L"UI_RETRY_BUTTON_SPRITE";
const wchar_t* UI_RETRY_BUTTON_SPRITE =
	L"Resources/Images/UI/Button/RetryButton.bmp";
#pragma endregion Ui_Button


#pragma region Ui_ButtonMouseOn
const std::wstring KEY_UI_TOWN_TO_FIELD_BUTTON_SPRITE =
	L"UI_TOWN_TO_FIELD_BUTTON_SPRITE";
const wchar_t* UI_TOWN_TO_FIELD_BUTTON_SPRITE =
	L"Resources/Images/UI/ButtonMouseOn/TownToField.bmp";
const std::wstring KEY_UI_TOWN_TO_GUILD_BUTTON_SPRITE =
	L"UI_TOWN_TO_GUILD_BUTTON_SPRITE";
const wchar_t* UI_TOWN_TO_GUILD_BUTTON_SPRITE =
	L"Resources/Images/UI/ButtonMouseOn/TownToGuild.bmp";
const std::wstring KEY_UI_TOWN_TO_SHOP_BUTTON_SPRITE =
	L"UI_TOWN_TO_SHOP_BUTTON_SPRITE";
const wchar_t* UI_TOWN_TO_SHOP_BUTTON_SPRITE =
	L"Resources/Images/UI/ButtonMouseOn/TownToShop.bmp";
#pragma endregion Ui_ButtonMouseOn


#pragma region Ui_Bar
const std::wstring KEY_UI_BAR_BACKGROUND_SPRITE =
	L"UI_BAR_BACKGROUND_SPRITE";
const wchar_t* DIR_UI_BAR_BACKGROUND_SPRITE =
	L"Resources/Images/UI/Bar/Background.bmp";
const std::wstring KEY_UI_BAR_GUAGE_SPRITE =
	L"UI_BAR_GUAGE_SPRITE";
const wchar_t* DIR_UI_BAR_GUAGE_SPRITE =
	L"Resources/Images/UI/Bar/Guage.bmp";
const std::wstring KEY_UI_BAR_BORDER_SPRITE =
	L"UI_BAR_BORDER_SPRITE";
const wchar_t* DIR_UI_BAR_BORDER_SPRITE =
	L"Resources/Images/UI/Bar/Border.bmp";
#pragma endregion Ui_Bar


#pragma region Player
const std::wstring KEY_PLAYER_TEMP_SPRITE =
	L"KEY_PLAYER_TEMP_SPRITE";
const wchar_t* DIR_PLAYER_TEMP_SPRITE =
	L"Resources/Images/Temp/PlayerTemp.bmp";
#pragma endregion Player
#pragma endregion Sprite

///////////////////////
///////////////////////

#pragma region GameObject_Name
const std::wstring NAME_QUIT_BUTTON = 	L"QUIT_BUTTON";
const std::wstring NAME_RETRY_BUTTON = 	L"RETRY_BUTTON";
#pragma endregion GameObject_Name

///////////////////////
///////////////////////

#pragma region Search_Keyword_In_GameObject
extern const std::wstring SKIG_BAR_GUAGE =
	L"BAR_GUAGE";
extern const std::wstring SKIG_BAR_BACKGROUND =
	L"BAR_BACKGROUND";
#pragma endregion Search_Keyword_In_GameObject

///////////////////////
///////////////////////

#pragma region Sound
const std::wstring KEY_SOUND_EXAMPLE =
	L"SOUND_EXAMPLE";
const std::wstring DIR_SOUND_EXAMPLE =
	L"Resources/Sounds/SOUND_EX_¸ð»öÃ¢¿¬(ÙºßäóïæÔ).mp3";
const std::wstring KEY_SOUND_TITLE_THEME =
	L"SOUND_TITLE_THEME";
const std::wstring DIR_SOUND_TITLE_THEME =
	L"Resources/Sounds/BGM/bgm00.mp3";
const std::wstring KEY_SOUND_TOWN_THEME =
	L"SOUND_TOWN_THEME";
const std::wstring DIR_SOUND_TOWN_THEME =
	L"Resources/Sounds/BGM/bgm01.mp3";
#pragma endregion Sound

///////////////////////
///////////////////////

#pragma region Scene
const std::wstring KEY_NONE_SCENE =
	L"NONE_SCENE";
const std::wstring KEY_END_SCENE =
	L"END_SCENE";
const std::wstring KEY_GUILD_SCENE =
	L"GUILD_SCENE";
const std::wstring KEY_SHOP_SCENE =
	L"SHOP_SCENE";
const std::wstring KEY_TITLE_SCENE =
	L"TITLE_SCENE";
const std::wstring KEY_TOWN_SCENE =
	L"TOWN_SCENE";
#pragma endregion Scene

///////////////////////
///////////////////////

#pragma region XmlDocument
const std::wstring XML_DOC_EXAMPLE =
	L"example document.txt";
const std::wstring XML_DOC_SAVEDATA =
	L"Resources/XML/save.dat";
#pragma endregion XmlDocument

///////////////////////
///////////////////////

#pragma region Size
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 150;
#pragma endregion Size

///////////////////////
///////////////////////

#pragma region ETC
const wchar_t* DEFAULT_FONT = L"Arial";
const COLORREF MAGENTA = RGB(255, 0, 255);
const double DEFAULT_FPS = 60.0;
const float DEFAULT_SOUND_VOLUME = 0.8f;

const double GRAVITY = 980;
const double DEFAULT_DRAG = 0.5;
const double MIN_LIMIT_VELOCITY_X = 1;
const double MIN_LIMIT_VELOCITY_Y = 1;
const double MAX_LIMIT_VELOCITY_X = 600;
const double MAX_LIMIT_VELOCITY_Y = 600;
#pragma endregion ETC



