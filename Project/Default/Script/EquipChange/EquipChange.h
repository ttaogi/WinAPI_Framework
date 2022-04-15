#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ObserverBase/Observer.h"
#include "DesignPattern/ObserverBase/Subject.h"

class GameObject;
class RenderedImage;
class RenderedText;

class ECEquipInInvenPanel;

enum class TAB { ABILITY, EQUIP };

class EquipChange : public MonoBehaviour, public Subject, public Observer
{
private:
	CHARACTER_ID curCharacter;
	TAB curTab;
	EQUIP_TYPE selectedEquipType;
	EQUIP_ID selectedEquip;

	GameObject* abilPanel;
	GameObject* equipPanel;
	RenderedImage* chPortrait;
	RenderedText* chLevel;
	RenderedText* chAbilFigure;
	RenderedText* weaponText;
	RenderedText* armorText;
	std::vector<ECEquipInInvenPanel*> equipInInvenPanelVec;
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

	void SetCurCharacter(CHARACTER_ID _curCharacter)	{ curCharacter = _curCharacter; }
	void SetCurTab(TAB _curTab)							{ curTab = _curTab; }
	void SetSelectedEquipType(EQUIP_TYPE _selectedEquipType)	{ selectedEquipType = _selectedEquipType; }
	void SetSelectedEquip(EQUIP_ID _selectedEquip)		{ selectedEquip = _selectedEquip; }

	void SetAbilPanel(GameObject* _abilPanel)			{ abilPanel = _abilPanel; }
	void SetEquipPanel(GameObject* _equipPanel)			{ equipPanel = _equipPanel; }
	void SetChPortrait(RenderedImage* _chPortrait)		{ chPortrait = _chPortrait; }
	void SetChLevel(RenderedText* _chLevel)				{ chLevel = _chLevel; }
	void SetChAbilFigure(RenderedText* _chAbilFigure)	{ chAbilFigure = _chAbilFigure; }
	void SetWeaponText(RenderedText* _weaponText)		{ weaponText = _weaponText; }
	void SetArmorText(RenderedText* _armorText)			{ armorText = _armorText; }
	void AddEuipInInvenPanel(ECEquipInInvenPanel* _e)	{ equipInInvenPanelVec.push_back(_e); }

	void Renew();
};

class ECCharacterPanel : public MonoBehaviour, public Subject
{
private:
	CHARACTER_ID characterId;

	virtual void Init() override { }
public:
	ECCharacterPanel();
	virtual ~ECCharacterPanel() { }

	virtual void Operation() override { }

	void Init(CHARACTER_ID _id) { characterId = _id; }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	CHARACTER_ID GetCharacterId() const { return characterId; }
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
	EQUIP_ID equipId;
public:
	ECEquipInInvenPanel();
	virtual ~ECEquipInInvenPanel() { }

	virtual void Operation() override { }

	virtual void Init() override { equipId = EQUIP_ID::NONE; }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	EQUIP_ID	GetEquipId() const { return equipId; }
	void		SetEquipId(EQUIP_ID _equipId);
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
