#include "Stdafx/stdafx.h"

#include "GameObject.h"

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"

GameObject::GameObject()
{
	name = L"";
	tag = TAG::UNTAGGED;
	active = true;
	cList.clear();
	goList.clear();
	AddComponent(&transform);
}

GameObject::~GameObject()
{
	for (auto iter = goList.begin(); iter != goList.end(); ++iter)
		SAFE_DELETE(*iter);
	goList.clear();

	Component* transform = GetComponent<Transform>();

	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
		if (transform != *iter) SAFE_DELETE(*iter);
	cList.clear();
}

void GameObject::Operation()
{
	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
		if (*iter) (*iter)->Operation();

	for (auto iter = goList.begin(); iter != goList.end(); ++iter)
		if (*iter) (*iter)->Operation();
}

void GameObject::FixedUpdate()
{
	if (!active) return;

	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
	{
		MonoBehaviour* m = IsDerivedFromMonoBehaviour(*iter);
		if (m) m->FixedUpdate();
	}

	for (auto iter = goList.begin(); iter != goList.end(); ++iter) (*iter)->FixedUpdate();
}

void GameObject::Update()
{
	if (!active) return;

	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
	{
		MonoBehaviour* m = IsDerivedFromMonoBehaviour(*iter);
		if (m) m->Update();
	}

	for (auto iter = goList.begin(); iter != goList.end(); ++iter) (*iter)->Update();
}

void GameObject::LateUpdate()
{
	if (!active) return;

	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
	{
		MonoBehaviour* m = IsDerivedFromMonoBehaviour(*iter);
		if (m) m->LateUpdate();
	}

	for (auto iter = goList.begin(); iter != goList.end(); ++iter) (*iter)->LateUpdate();
}

void GameObject::Render(HDC _hdc)
{
	if (!active) return;

	RenderedImage* rImg = GetComponent<RenderedImage>();
	if (rImg) rImg->Render(_hdc);

	for (auto iter = goList.begin(); iter != goList.end(); ++iter) (*iter)->Render(_hdc);
}

void GameObject::AddGameObject(GameObject* _go)
{
	if (_go) goList.push_back(_go);
}

GameObject* GameObject::GetGameObjectByTag(TAG _tag)
{
	if (CompareTag(_tag)) return this;
	else
	{
		GameObject* result = NULL;
		for (auto iter = goList.begin(); iter != goList.end(); ++iter)
		{
			result = (*iter)->GetGameObjectByTag(_tag);
			if (result) return result;
		}
	}
	return NULL;
}

GameObject* GameObject::GetGameObjectByName(wstring _name)
{
	if (CompareName(_name)) return this;
	else
	{
		GameObject* result = NULL;
		for (auto iter = goList.begin(); iter != goList.end(); ++iter)
		{
			result = (*iter)->GetGameObjectByName(_name);
			if (result) return result;
		}
	}
	return NULL;
}

void GameObject::AddComponent(Component* _c)
{
	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
		if (!strcmp((*iter)->GetComponentID(), _c->GetComponentID()))
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
	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
		if (*iter == _c)
		{
			SAFE_DELETE(*iter);
			cList.erase(iter);
			return;
		}
}

Component* GameObject::GetComponent(Component_ID _id)
{
	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
		if (!strcmp((*iter)->GetComponentID(), _id)) return *iter;
	return NULL;
}

void GameObject::CollectCollider(std::vector<Collider*>* _colliderVec)
{
	Collider* collider = GetComponent<Collider>();
	if (collider) _colliderVec->push_back(collider);

	for (auto iter = goList.begin(); iter != goList.end(); ++iter)
		(*iter)->CollectCollider(_colliderVec);
}

Component_ID GameObject::GetComponentID() { return id; }
