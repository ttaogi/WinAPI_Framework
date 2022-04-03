#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ComponentBase/Component/Rendered/Rendered.h"

class Animator;
class Animation;

class RenderedAnimator : public Rendered, public MonoBehaviour {
private:
	Animator* animator;
protected:
public:
	RenderedAnimator();
	virtual ~RenderedAnimator();

	virtual void Operation() override;

	virtual void Init() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(Collision _col) override { }

	virtual void Render(HDC _hdc) override;

	void AddAnimation(CHARACTER_STATE _state, Animation* _animation);
	bool ChangeAnimation(CHARACTER_STATE _state);

	bool IsEnd() const;
	bool IsPlay() const;

	void AniStart();
	void AniStop();
	void AniPause();
	void AniResume();

	CHARACTER_STATE GetAnimationState() const;
};