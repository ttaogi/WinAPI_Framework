#pragma once

#include <functional>

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

class Button : public MonoBehaviour
{
protected:
	std::function<void()> callBack_v_CB_v;
	std::wstring str;
public:
	Button(std::wstring _str = L"");
	virtual ~Button();

	virtual void Operation() override;

	virtual void Init() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(Collision _col) override;

	void SetCallBack_v_CB_v(std::function<void()> _callBack);
	std::wstring	GetString() const { return str; }
	void			SetString(std::wstring _str) { str = _str; }
};

class ButtonMouseOn : public Button
{
public:
	ButtonMouseOn(std::wstring _str = L"");
	virtual ~ButtonMouseOn();

	virtual void Operation() override;

	virtual void Init() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(Collision _col) override;
};
