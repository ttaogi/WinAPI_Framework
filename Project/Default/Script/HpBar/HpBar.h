#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

class HpBar : public MonoBehaviour
{
private:
	std::vector<float> hpRateVec;
public:
	HpBar();
	virtual ~HpBar();

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(Collision _col) override { }

	void PrepareRender(float _hpRate);
};
