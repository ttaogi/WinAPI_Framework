#include "Stdafx/stdafx.h"

#include "Scene/Scene.h"

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Script/Character/Player/Player.h"
#include "Script/Character/Enemy/Enemy.h"

bool Scene::IsEmpty(POINT _gridPos)
{
	for (auto iter = mapData.playerVec.begin(); iter != mapData.playerVec.end(); ++iter)
		if (PointEqual((*iter)->GetComponent<Player>()->GetGridPos(), _gridPos)) return false;
	for (auto iter = mapData.enemyVec.begin(); iter != mapData.enemyVec.end(); ++iter)
		if (PointEqual((*iter)->GetComponent<Enemy>()->GetGridPos(), _gridPos) && (*iter)->GetComponent<Enemy>()->GetHp() > 0) return false;

	return true;
}

void Scene::LoadMapData(MapData* _mapData)
{
	for (int i = 0; i < _mapData->x; ++i)
		for (int j = 0; j < _mapData->y; ++j)
			root->AddGameObject(_mapData->tileVec[i][j]);

	for (auto iter = _mapData->playerVec.begin(); iter != _mapData->playerVec.end(); ++iter)
		root->AddGameObject(*iter);

	for (auto iter = _mapData->enemyVec.begin(); iter != _mapData->enemyVec.end(); ++iter)
		root->AddGameObject(*iter);
}

void Scene::ProcessCollision(std::vector<Collision>* _collisionVec)
{
	if (!_collisionVec) return;

	for (auto iter = _collisionVec->begin(); iter != _collisionVec->end(); ++iter)
	{
		iter->col1->gameObject->OnCollision(*iter);
		iter->col2->gameObject->OnCollision(*iter);
	}
}

void Scene::ProcessRender(HDC _hdc, priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr>* _queue)
{
	if (!_queue) return;

	while (!_queue->empty())
	{
		_queue->top()->Render(_hdc);
		_queue->pop();
	}
}
