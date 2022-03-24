#pragma once

enum class DIRECTION
{
	LEFT = 0, TOP, RIGHT, BOTTOM,
	LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM,
	DIRECTION_NUM
};

enum class IMAGE_LOAD_KIND
{
	LOAD_RESOURCE = 0,
	LOAD_FILE,
	LOAD_EMPTY,
	LOAD_END,
	IMAGE_LOAD_KIND_NUM
};

enum class CHARACTER_STATE
{
	IDLE = 0, ATTACK, ATTACKED, DEFFENCE,
	CHARACTER_STATE_NUM
};

std::wstring CharacterStateToWString(CHARACTER_STATE _state);

enum class TAG
{
	UNTAGGED = 0,
	PLAYER,
	MAIN_CAMERA,
	TAG_NUM
};

std::wstring TagToWString(TAG _tag);

#pragma region FactoryType
enum class BUTTON_FACTORY_TYPE
{
	DEFAULT = 0,
	MOUSE_ON,
	BUTTON_FACTORY_TYPE_NUM
};

enum class BAR_FACTORY_TYPE
{
	DEFAULT = 0,
	BAR_FACTORY_TYPE_NUM
};

enum class PLAYER_FACTORY_TYPE
{
	DEFAULT = 0,
	PLAYER_FACTORY_TYPE_NUM
};

enum class PLATFORM_FACTORY_TYPE
{
	DEFAULT = 0,
	PLATFORM_FACTORY_TYPE_NUM
};
#pragma endregion FactoryType

enum class RENDERED_IMAGE_RENDERING_TYPE
{
	DEFAULT = 0,
	LOOP,
	RENDERED_IMAGE_RENDERING_TYPE
};

enum class SORTING_LAYER
{
	BACKGROUND = 0,
	BACKGROUND_EFFECT,
	PLATFORM,
	OBJECT,
	MONSTER,
	BOSS,
	PLAYER,
	UI,
	UI_EFFECT,
	SORTING_LAYER_NUM
};

enum class CHARACTER_ID
{
	AL = 0,
	KARIN,
	CHARACTER_ID_NUM
};

enum class EQUIP_ID
{
	NONE = 0,
	LONGSWORD,
	BROADSWORD,
	MAGICIANWAND,
	WIZARDWAND,
	CROSSARMOR,
	LEZAARMOR,
	MAGICIANROBE,
	WIZARDROBE,
	EQUIP_ID_NUM
};
