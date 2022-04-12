#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Subject.h"
#include "Utility/Enums/Enums.h"

class RenderedAnimator;

class NODE
{
public:
	POINT id;
	int f;
	int g;
	int h;
	POINT parent;
public:
	bool operator<(const NODE n) const { return this->f > n.f; }
};

class Damage
{
public:
	int str;
	int mgc;
};

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
	virtual void Attacked(Damage _dmg, DIRECTION _dir) = 0;

	static void PushPriorityQueue(vector<NODE>& _que, NODE _node);
	static bool HasNode(vector<NODE>& _que, POINT _pos);
	static void SearchNearTile(vector<NODE>& _open, vector<NODE>& _close,
		POINT _destGridPos, Scene* _scene, NODE _parent);
	static DIRECTION SearchRoute(Scene* _scene, POINT _startGridPos, POINT _destGridPos);
};