#pragma once

#include <functional>

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

class Bar : public MonoBehaviour
{
private:
	double rate;
	std::function<void()> callBack_v_CB_v;
public:
	Bar();
	virtual ~Bar();

	virtual void Operation() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	void SetCallBack_v_CB_v(std::function<void()> _callBack) { callBack_v_CB_v = _callBack; }
	double GetRate() const { return rate; }
	void SetRate(double _rate);
};
