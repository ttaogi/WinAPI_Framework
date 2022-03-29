#include "Stdafx/stdafx.h"

#include "Manager/GameManager/GameManager.h"

GameManager::GameManager() { }

GameManager::~GameManager() { }

HRESULT GameManager::Init()
{
	phase = PHASE::PHASE_NUM;

	return S_OK;
}

void GameManager::Release() { }
