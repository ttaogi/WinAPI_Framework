#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Subject.h"

class RenderedAnimator;

class Character : public MonoBehaviour, public Subject
{
protected:
	int hp;
	int hpMax;
	int str;
	int mgc;
	int def;
	int mDef;
	int dex;

	POINT gridPos;
	POINT moveGridPos;
	POINT nextGridPos;
	PHASE_DETAIL state;
public:
	Character();
	virtual ~Character() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override = 0;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	POINT	GetGridPos() const			{ return gridPos; }
	void	SetGridPos(POINT _gridPos)	{ gridPos = _gridPos; }
	POINT	GetMoveGridPos() const				{ return moveGridPos; }
	void	SetMoveGridPos(POINT _moveGridPos)	{ moveGridPos = _moveGridPos; }
	void	GetAbility(int& _hp, int& _hpMax, int& _str, int& _mgc, int& _def, int& _mDef, int& _dex)
	{
		_hp = hp; _hpMax = hpMax; _str = str; _mgc = mgc; _def = def; _mDef = mDef; _dex = dex;
	}
	void	SetAbility(int _hp, int _hpMax, int _str, int _mgc, int _def, int _mDef, int _dex)
	{
		hp = _hp; hpMax = _hpMax; str = _str; mgc = _mgc; def = _def; mDef = _mDef; dex = _dex;
	}
	int		GetHp() const			{ return hp; }
	void	SetHKp(int _hp)			{ hp = _hp; }
	int		GetHpMax() const		{ return hpMax; }
	void	SetHpMax(int _hpMax)	{ hpMax = _hpMax; }
	int		GetStr() const			{ return str; }
	void	SetStr(int _str)		{ str = _str; }
	int		GetMgc() const			{ return mgc; }
	void	SetMgc(int _mgc)		{ mgc = _mgc; }
	int		GetDef() const			{ return def; }
	void	SetDef(int _def)		{ def = _def; }
	int		GetMDef() const			{ return mDef; }
	void	SetMDef(int _mDef)		{ mDef = _mDef; }
	int		GetDex() const			{ return dex; }
	void	SetDex(int _dex)		{ dex = _dex; }

	void ChangeAnimMoveToIdle(CHARACTER_STATE _animState, RenderedAnimator* _rAnim);
	void ChangeAnimAttackToIdle(CHARACTER_STATE _animState, RenderedAnimator* _rAnim);
	void MovePos(CHARACTER_STATE _animState, Transform* _t);
};