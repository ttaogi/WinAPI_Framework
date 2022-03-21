#include "Stdafx/stdafx.h"

#include "Scene/Scene.h"

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

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
