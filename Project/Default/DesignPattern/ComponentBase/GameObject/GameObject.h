#pragma once

#include <list>
#include <queue>

#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/Rendered.h"
#include "Utility/Enums/Enums.h"

class GameObject {
private:
	const Component_ID id = (const Component_ID)L"GameObject";
	Transform transform;
	std::wstring name;
	TAG tag;
	bool active;
	std::list<GameObject*> goList;
	std::list<Component*> cList;
public:
	GameObject();
	~GameObject();

	void Operation();

	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render(HDC _hdc);

	void AddGameObject(GameObject* _go);
	GameObject* GetGameObjectByTag(TAG _tag);
	GameObject* GetGameObjectByName(std::wstring _name);
	//std::list<GameObject*> GetGameObjectsByTag(TAG _tag);
	//std::list<GameObject*> GetGameObjectsByName(std::wstring _name);

	Component_ID GetComponentID();

	void AddComponent(Component* _c);
	void RemoveComponent(Component* _c);
	template<class T>
	void RemoveComponent()
	{
		T* c = new T();

		for(auto it = cList.begin(); it != cList.end(); ++it)
			if (!strcmp((*it)->GetComponentID(), c->GetComponentID()))
			{
				SAFE_DELETE(*it);
				cList.erase(it);
				break;
			}

		SAFE_DELETE(c);
	}

	Component*	GetComponent(Component_ID _id);
	template<class T>
	T* GetComponent()
	{
		if (cList.size() == 0) return NULL;

		T* c = new T();

		for (auto it = cList.begin(); it != cList.end(); ++it)
			if ( !strcmp((*it)->GetComponentID(), c->GetComponentID()) )
			{
				SAFE_DELETE(c);
				return dynamic_cast<T*>(*it);
			}

		SAFE_DELETE(c);
		return NULL;
	}

	std::wstring GetName() const { return name; }
	void SetName(std::wstring _name) { name = _name; }
	TAG GetTag() const { return tag; }
	void SetTag(TAG _tag) { tag = _tag; }
	bool GetActive() const { return active; }
	void SetActive(bool _active) { active = _active; }

	bool CompareName(std::wstring _name) const { return name.compare(_name) == 0; }
	bool CompareTag(TAG _tag) const { return tag == _tag; }
	void CollectCollider(std::vector<Collider*>* _colliderVec);
	void OnCollision(Collision _col);
	void CollectRendered(priority_queue<Rendered*, std::vector<Rendered*>, CmpRenderedPtr>* _queue);
};
