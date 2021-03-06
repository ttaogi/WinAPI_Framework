#pragma once

typedef char* Component_ID;

class GameObject;
class Transform;

class Component
{
private:
protected:
	const Component_ID id;
public:
	GameObject* gameObject = NULL;
	Transform* transform = NULL;
public:
	Component(const Component_ID _id);
	virtual ~Component() {};

	virtual void Operation() = 0;

	Component_ID GetComponentID() { return id; }
};
