#include "Stdafx/stdafx.h"

#include "GameObject.h"

GameObject::GameObject()
{
	AddComponent(&transform);
	tag = L"";
	active = true;
}

GameObject::~GameObject()
{
	Component* transform = GetComponent<Transform>();

	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
		if(transform != *iter) SAFE_DELETE(*iter);
	cList.clear();
}

void GameObject::Operation()
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		if(*it) (*it)->Operation();
}

void GameObject::AddComponent(Component* _c)
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		if (!strcmp((*it)->GetComponentID(), _c->GetComponentID()))
		{
			SAFE_DELETE(_c);
			return;
		}

	_c->gameObject = this;
	_c->transform = &transform;
	cList.push_back(_c);
}

void GameObject::RemoveComponent(Component* _c)
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		if (*it == _c)
		{
			SAFE_DELETE(*it);
			cList.erase(it);
			return;
		}
}

Component* GameObject::GetComponent(Component_ID _id)
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		if (!strcmp((*it)->GetComponentID(), _id)) return *it;
	return NULL;
}

Component_ID GameObject::GetComponentID() { return id; }
