#include "Stdafx/stdafx.h"

#include "Enums.h"

wstring CharacterStateToWString(CHARACTER_STATE _state)
{
	switch (_state)
	{
	case CHARACTER_STATE::IDLE:
		return L"IDLE";
	case CHARACTER_STATE::ATTACK:
		return L"ATTACK";
	case CHARACTER_STATE::ATTACKED:
		return L"ATTACKED";
	case CHARACTER_STATE::DEFFENCE:
		return L"DEFFENCE";
	default:
		return L"CHARACTER_STATE_NUM";
	}
}

std::wstring TagToWString(TAG _tag)
{
	switch (_tag)
	{
	case TAG::UNTAGGED:
		return L"UNTAGGED";
	case TAG::PLAYER:
		return L"PLAYER";
	case TAG::MAIN_CAMERA:
		return L"MAIN_CAMERA";
	default:
		return L"TAG_NUM";
	}
}
