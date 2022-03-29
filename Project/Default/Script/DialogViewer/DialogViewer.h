#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Subject.h"
#include "Manager/DialogManager/DialogManager.h"

class GameObject;

class DialogViewer : public MonoBehaviour, public Subject
{
private:
	DialogCycle cycle;
	GameObject* upper;
	GameObject* lower;
protected:
public:
	DialogViewer();
	virtual ~DialogViewer();

	virtual void Operation();

	void Init();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void OnCollision(Collision _col);

	void SetUpper(GameObject* _upper) { upper = _upper; }
	void SetLower(GameObject* _lower) { lower = _lower; }
	void SetCycle(DialogCycle _cycle) { cycle = _cycle; }

	void Next();
	bool IsEnd();
};
