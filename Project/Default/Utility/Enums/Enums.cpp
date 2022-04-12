#include "Stdafx/stdafx.h"

#include "Enums.h"

wstring DirectionToWString(DIRECTION _dir)
{
	switch (_dir)
	{
	case DIRECTION::LEFT:
		return L"LEFT";
	case DIRECTION::TOP:
		return L"TOP";
	case DIRECTION::RIGHT:
		return L"RIGHT";
	case DIRECTION::BOTTOM:
		return L"BOTTOM";
	case DIRECTION::LEFT_BOTTOM:
		return L"LEFT_BOTTOM";
	case DIRECTION::LEFT_TOP:
		return L"LEFT_TOP";
	case DIRECTION::RIGHT_BOTTOM:
		return L"RIGHT_BOTTOM";
	case DIRECTION::RIGHT_TOP:
		return L"RIGHT_TOP";
	default:
		return L"DIRECTION_NUM";
	}
}

wstring CharacterStateToWString(CHARACTER_STATE _state)
{
	switch (_state)
	{
		case CHARACTER_STATE::IDLE_LEFT_BOTTOM:
			return L"IDLE_LEFT_BOTTOM";
		case CHARACTER_STATE::IDLE_LEFT_TOP:
			return L"IDLE_LEFT_TOP";
		case CHARACTER_STATE::IDLE_RIGHT_BOTTOM:
			return L"IDLE_RIGHT_BOTTOM";
		case CHARACTER_STATE::IDLE_RIGHT_TOP:
			return L"IDLE_RIGHT_TOP";
		case CHARACTER_STATE::MOVE_LEFT_BOTTOM:
			return L"MOVE_LEFT_BOTTOM";
		case CHARACTER_STATE::MOVE_LEFT_TOP:
			return L"MOVE_LEFT_TOP";
		case CHARACTER_STATE::MOVE_RIGHT_BOTTOM:
			return L"MOVE_RIGHT_BOTTOM";
		case CHARACTER_STATE::MOVE_RIGHT_TOP:
			return L"MOVE_RIGHT_TOP";
		case CHARACTER_STATE::ATTACK_LEFT_BOTTOM:
			return L"ATTACK_LEFT_BOTTOM";
		case CHARACTER_STATE::ATTACK_LEFT_TOP:
			return L"ATTACK_LEFT_TOP";
		case CHARACTER_STATE::ATTACK_RIGHT_BOTTOM:
			return L"ATTACK_RIGHT_BOTTOM";
		case CHARACTER_STATE::ATTACK_RIGHT_TOP:
			return L"ATTACK_RIGHT_TOP";
		case CHARACTER_STATE::ATTACKED_LEFT_BOTTOM:
			return L"ATTACKED_LEFT_BOTTOM";
		case CHARACTER_STATE::ATTACKED_LEFT_TOP:
			return L"ATTACKED_LEFT_TOP";
		case CHARACTER_STATE::ATTACKED_RIGHT_BOTTOM:
			return L"ATTACKED_RIGHT_BOTTOM";
		case CHARACTER_STATE::ATTACKED_RIGHT_TOP:
			return L"ATTACKED_RIGHT_TOP";
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
