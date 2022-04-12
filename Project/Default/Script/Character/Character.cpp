#include "Stdafx/stdafx.h"

#include "Script/Character/Character.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "Scene/Scene.h"

Character::Character()
	: Component((const Component_ID)typeid(Character).name()) { }

void Character::ChangeAnimMoveToIdle(CHARACTER_STATE _animState, RenderedAnimator* _rAnim)
{
	switch (_animState)
	{
	case CHARACTER_STATE::MOVE_LEFT_BOTTOM:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
		break;
	case CHARACTER_STATE::MOVE_LEFT_TOP:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_TOP);
		break;
	case CHARACTER_STATE::MOVE_RIGHT_BOTTOM:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM);
		break;
	case CHARACTER_STATE::MOVE_RIGHT_TOP:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP);
		break;
	default:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
		break;
	}
}

void Character::ChangeAnimAttackToIdle(CHARACTER_STATE _animState, RenderedAnimator * _rAnim)
{
	switch (_animState)
	{
	case CHARACTER_STATE::ATTACK_LEFT_BOTTOM:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
		break;
	case CHARACTER_STATE::ATTACK_LEFT_TOP:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_TOP);
		break;
	case CHARACTER_STATE::ATTACK_RIGHT_BOTTOM:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM);
		break;
	case CHARACTER_STATE::ATTACK_RIGHT_TOP:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP);
		break;
	default:
		_rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);
		break;
	}
}

void Character::MovePos(CHARACTER_STATE _animState, Transform* _t)
{
	POINT pos = _t->GetPosition().ToPoint();

	switch (_animState)
	{
	case CHARACTER_STATE::MOVE_LEFT_BOTTOM:
		_t->SetPosition(D_POINT{ (double)pos.x - 2, (double)pos.y + 1 });
		break;
	case CHARACTER_STATE::MOVE_LEFT_TOP:
		_t->SetPosition(D_POINT{ (double)pos.x - 2, (double)pos.y - 1 });
		break;
	case CHARACTER_STATE::MOVE_RIGHT_BOTTOM:
		_t->SetPosition(D_POINT{ (double)pos.x + 2, (double)pos.y + 1 });
		break;
	case CHARACTER_STATE::MOVE_RIGHT_TOP:
		_t->SetPosition(D_POINT{ (double)pos.x + 2, (double)pos.y - 1 });
		break;
	}
}

void Character::PushPriorityQueue(vector<NODE>& _que, NODE _node) {
	bool redundant = false;

	for (int i = 0; i < _que.size(); ++i)
		if (PointEqual(_que[i].id, _node.id))
		{
			redundant = true;
			if (_que[i].g > _node.g) _que[i] = _node;
			break;
		}

	if (redundant == false)
	{
		_que.push_back(_node);
	}

	for (int i = (int)_que.size() - 1; i > 0; --i)
		for (int j = 0; j < i; ++j)
			if (_que[j] < _que[j + 1])
			{
				NODE tmp = _que[j];
				_que[j] = _que[j + 1];
				_que[j + 1] = tmp;
			}
}

bool Character::HasNode(vector<NODE>& _que, POINT _pos)
{
	for (auto iter = _que.begin(); iter != _que.end(); ++iter)
		if (PointEqual(iter->id, _pos)) return true;
	return false;
}

void Character::SearchNearTile(vector<NODE>& _open, vector<NODE>& _close,
	POINT _destGridPos, Scene* _scene, NODE _parent)
{
	if (_parent.id.y >= 1)
	{
		POINT rightTop{ _parent.id.x, _parent.id.y - 1 };

		if ((_scene->IsEmpty(rightTop) || PointEqual(_destGridPos, rightTop)) && !HasNode(_close, rightTop))
		{
			NODE n{ rightTop,
				_parent.g + 1 + (abs(_destGridPos.x - rightTop.x) + abs(_destGridPos.y - rightTop.y)),
				_parent.g + 1, (abs(_destGridPos.x - rightTop.x) + abs(_destGridPos.y - rightTop.y)),
				_parent.id };

			PushPriorityQueue(_open, n);
		}
	}
	if (_parent.id.x >= 1)
	{
		POINT leftTop{ _parent.id.x - 1, _parent.id.y };

		if ((_scene->IsEmpty(leftTop) || PointEqual(_destGridPos, leftTop)) && !HasNode(_close, leftTop))
		{
			NODE n{ leftTop,
				_parent.g + 1 + (abs(_destGridPos.x - leftTop.x) + abs(_destGridPos.y - leftTop.y)),
				_parent.g + 1, (abs(_destGridPos.x - leftTop.x) + abs(_destGridPos.y - leftTop.y)),
				_parent.id };

			PushPriorityQueue(_open, n);
		}
	}
	if (_parent.id.y < _scene->GetMapData()->y - 1)
	{
		POINT leftBottom{ _parent.id.x, _parent.id.y + 1 };

		if ((_scene->IsEmpty(leftBottom) || PointEqual(_destGridPos, leftBottom)) && !HasNode(_close, leftBottom))
		{
			NODE n{ leftBottom,
				_parent.g + 1 + (abs(_destGridPos.x - leftBottom.x) + abs(_destGridPos.y - leftBottom.y)),
				_parent.g + 1, (abs(_destGridPos.x - leftBottom.x) + abs(_destGridPos.y - leftBottom.y)),
				_parent.id };

			PushPriorityQueue(_open, n);
		}
	}
	if (_parent.id.x < _scene->GetMapData()->x - 1)
	{
		POINT rightBottom{ _parent.id.x + 1, _parent.id.y };

		if ((_scene->IsEmpty(rightBottom) || PointEqual(_destGridPos, rightBottom)) && !HasNode(_close, rightBottom))
		{
			NODE n{ rightBottom,
				_parent.g + 1 + (abs(_destGridPos.x - rightBottom.x) + abs(_destGridPos.y - rightBottom.y)),
				_parent.g + 1, (abs(_destGridPos.x - rightBottom.x) + abs(_destGridPos.y - rightBottom.y)),
				_parent.id };

			PushPriorityQueue(_open, n);
		}
	}
}

DIRECTION Character::SearchRoute(Scene* _scene, POINT _startGridPos, POINT _destGridPos)
{
	if (PointEqual(_startGridPos, _destGridPos)) return DIRECTION::DIRECTION_NUM;

	vector<NODE> open;
	vector<NODE> close;
	bool find = false;

	open.push_back(NODE{ _startGridPos, 0, 0, 0, POINT{-1, -1} });

	while (true)
	{
		if (open.empty()) break;

		NODE curNode = open.front();
		open.erase(open.begin());
		close.push_back(curNode);

		if (PointEqual(curNode.id, _destGridPos))
		{
			find = true;
			break;
		}

		SearchNearTile(open, close, _destGridPos, _scene, curNode);
	}

	if (find)
	{
		NODE n = close.back();

		while (true)
		{
			if (PointEqual(n.parent, _startGridPos)) break;

			for (int i = 0; i < close.size(); ++i)
				if (PointEqual(close[i].id, n.parent))
				{
					n = close[i];
					break;
				}
		}

		if (n.id.x == _startGridPos.x - 1)		return DIRECTION::LEFT_TOP;
		else if (n.id.x == _startGridPos.x + 1)	return DIRECTION::RIGHT_BOTTOM;
		else if (n.id.y == _startGridPos.y - 1)	return DIRECTION::RIGHT_TOP;
		else									return DIRECTION::LEFT_BOTTOM;
	}
	else
		return DIRECTION::DIRECTION_NUM;
}
