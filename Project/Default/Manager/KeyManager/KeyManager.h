#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	std::bitset<KEY_MAX> keyDown;
	std::bitset<KEY_MAX> keyUp;
public:
	KeyManager();
	~KeyManager();

	HRESULT Init(void);
	bool IsOnceKeyDown(int _key);
	bool IsOnceKeyUp(int _key);
	bool IsStayKeyDown(int _key);
	bool IsTrigger(int _key);
	// a-z, space, enter, 0-9.
	bool IsOnceAnyKeyDown();

	std::bitset<KEY_MAX> GetKeyDown() { return keyDown; }
	std::bitset<KEY_MAX> GetKeyUp() { return keyUp; }

	void SetKeyDown(int _key, bool _state) { keyDown.set(_key, _state); }
	void SetKeyUp(int _key, bool _state) { keyUp.set(_key, _state); }
};