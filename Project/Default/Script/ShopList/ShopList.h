#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Observer.h"
#include "DesignPattern/ObserverBase/Subject.h"
#include "Manager/GameDataManager/GameDataManager.h"
#include "Utility/Enums/Enums.h"

class ShopListPanel : public MonoBehaviour, public Subject
{
private:
	EquipInfo equip;
protected:
public:
	ShopListPanel();
	virtual ~ShopListPanel() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	EquipInfo GetEquip() const { return equip; }
	void SetEquip(EquipInfo _equip) { equip = _equip; }
};


class ShopList : public MonoBehaviour, public Observer, public Subject
{
private:
	EquipInfo selectedItem;
protected:
public:
	ShopList();
	virtual ~ShopList() { }

	virtual void OnNotify(Subject* _subject, EVENT _event) override;

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override { }
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	EquipInfo GetSelectedItem() const { return selectedItem; }
	void SetSelectedItem(EquipInfo _item) { selectedItem = _item; }
};


class BuyButton : public MonoBehaviour, public Subject
{
private:
protected:
public:
	BuyButton();
	virtual ~BuyButton() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};


class ExitButton : public MonoBehaviour, public Subject
{
private:
protected:
public:
	ExitButton();
	virtual ~ExitButton() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};


class ToEquipChangeButton : public MonoBehaviour, public Subject
{
private:
protected:
public:
	ToEquipChangeButton();
	virtual ~ToEquipChangeButton() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }
};
