#include "Stdafx/stdafx.h"

#include "Scene/Scene.h"

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

void Scene::ProcessCollision(std::vector<Collision>* _collisionVec)
{
	if (!_collisionVec) return;

	for (auto iter = _collisionVec->begin(); iter != _collisionVec->end(); ++iter)
	{
		iter->col1->gameObject->cList;
		for (auto component = iter->col1->gameObject->cList.begin();
			component != iter->col1->gameObject->cList.end();
			++component)
		{
			MonoBehaviour* m = IsDerivedFromMonoBehaviour(*component);
			if (m) m->OnCollision(*iter);
		}
	}
}
