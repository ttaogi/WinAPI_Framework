#include "Stdafx/stdafx.h"

#include "KeyManager.h"

#include <bitset>

KeyManager::KeyManager() { Init(); }

KeyManager::~KeyManager() { }

HRESULT KeyManager::Init(void)
{
	for (int i = 0; i < KEY_MAX; ++i)
	{
		SetKeyDown(i, false);
		SetKeyUp(i, false);
	}
	return S_OK;
}

bool KeyManager::IsOnceKeyDown(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		if (!GetKeyDown()[_key])
		{
			SetKeyDown(_key, true);
			return true;
		}
	else
		SetKeyDown(_key, false);

	return false;
}

bool KeyManager::IsOnceKeyUp(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		SetKeyUp(_key, true);
	else
		if (GetKeyUp()[_key])
		{
			SetKeyUp(_key, true);
			return true;
		}

	return false;
}

bool KeyManager::IsStayKeyDown(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000) return true;

	return false;
}

bool KeyManager::IsTrigger(int _key)
{
	if (GetKeyState(_key) & 0x0001) return true;

	return false;
}

bool KeyManager::IsOnceAnyKeyDown()
{
	for (int i = 'A'; i <= 'Z'; ++i)
		if (IsOnceKeyDown(i)) return true;
	for (int i = 0x30; i <= 0x39; ++i)
		if (IsOnceKeyDown(i)) return true;
	if (IsOnceKeyDown(VK_SPACE)) return true;
	if (IsOnceKeyDown(VK_RETURN)) return true;

	return false;
}
