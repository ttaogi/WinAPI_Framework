#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class GameDataManager : public SingletonBase<GameDataManager>
{
private:
	bool stage1Clear;
	bool stage2Clear;
	bool stage3Clear;
	bool stage4Clear;
	float volume;
protected:
public:
	GameDataManager();
	virtual ~GameDataManager();

	HRESULT Init();
	void Release();

	bool GetStage1Clear() const			{ return stage1Clear; }
	void SetStage1Clear(bool _clear)	{ stage1Clear = _clear; }
	bool GetStage2Clear() const			{ return stage2Clear; }
	void SetStage2Clear(bool _clear)	{ stage2Clear = _clear; }
	bool GetStage3Clear() const			{ return stage3Clear; }
	void SetStage3Clear(bool _clear)	{ stage3Clear = _clear; }
	bool GetStage4Clear() const			{ return stage4Clear; }
	void SetStage5Clear(bool _clear)	{ stage4Clear = _clear; }
	float	GetVolume() const			{ return volume; }
	void	SetVolume(float _volume)	{ volume = _volume; }
};