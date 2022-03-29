#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"
#include "Utility/Enums/Enums.h"

class GameManager : public SingletonBase<GameManager>
{
private:
	PHASE phase;
public:
	GameManager();
	virtual ~GameManager();

	HRESULT Init();
	void Release();

	PHASE GetPhase() const { return phase; }
	void SetPhase(PHASE _phase) { phase = _phase; }
};