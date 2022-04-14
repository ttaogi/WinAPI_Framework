#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Observer.h"
#include "DesignPattern/ObserverBase/Subject.h"

class EquipChange : public MonoBehaviour, public Subject, public Observer
{
private:
public:
	EquipChange();
	virtual ~EquipChange() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	virtual void OnNotify(Subject* _subject, EVENT _event) override;
};

class ECCharacterPanel : public MonoBehaviour, public Subject
{
private:
public:
	ECCharacterPanel();
	virtual ~ECCharacterPanel() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};

class ECAbilityTabPanel : public MonoBehaviour, public Subject
{
private:
public:
	ECAbilityTabPanel();
	virtual ~ECAbilityTabPanel() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};

class ECEquipTabPanel : public MonoBehaviour, public Subject
{
private:
public:
	ECEquipTabPanel();
	virtual ~ECEquipTabPanel() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};

class ECWeaponText : public MonoBehaviour, public Subject
{
private:
public:
	ECWeaponText();
	virtual ~ECWeaponText() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};

class ECArmorText : public MonoBehaviour, public Subject
{
private:
public:
	ECArmorText();
	virtual ~ECArmorText() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};

class ECEquipInInvenPanel : public MonoBehaviour, public Subject
{
private:
public:
	ECEquipInInvenPanel();
	virtual ~ECEquipInInvenPanel() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};

class ToShopListButton : public MonoBehaviour, public Subject
{
private:
public:
	ToShopListButton();
	virtual ~ToShopListButton() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};

class EquipChangeButton : public MonoBehaviour, public Subject
{
private:
public:
	EquipChangeButton();
	virtual ~EquipChangeButton() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};
