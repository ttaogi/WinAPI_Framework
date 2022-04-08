#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

class RenderedAnimator;

class FlameBurst : public MonoBehaviour
{
private:
	RenderedAnimator* rAnim;
public:
	FlameBurst();
	virtual ~FlameBurst() { }

	virtual void Operation() override { }

	virtual void Init() override { }
	virtual void FixedUpdate() override { }
	virtual void Update() override;
	virtual void LateUpdate() override { }
	virtual void OnCollision(Collision _col) override { }

	RenderedAnimator*	GetRAnim()							{ return rAnim; }
	void				SetRAnim(RenderedAnimator* _rAnim)	{ rAnim = _rAnim; }
};