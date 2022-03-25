#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Animator/Animator.h"

RenderedAnimator::RenderedAnimator()
	: Component((const Component_ID)typeid(RenderedAnimator).name())
{ animator = NULL; }

RenderedAnimator::~RenderedAnimator()
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void RenderedAnimator::Operation() { }

void RenderedAnimator::Init()
{
	animator = new Animator();
	animator->Init();
}

void RenderedAnimator::FixedUpdate() { }

void RenderedAnimator::Update() { if(enabled && animator) animator->Update(); }

void RenderedAnimator::LateUpdate() { }

void RenderedAnimator::Render(HDC _hdc)
{
	if (enabled && animator)
	{
		POINT revision = CAMERA->GetRevision();
		POINT pos = gameObject->GetComponent<Transform>()->GetPosition().ToPoint();
		pos.x -= revision.x;
		pos.y -= revision.y;
		animator->AnimationRender(_hdc, pos);
	}
}

void RenderedAnimator::AddAnimation(CHARACTER_STATE _state, Animation* _animation) { animator->AddAnimation(_state, _animation); }
bool RenderedAnimator::ChangeAnimation(CHARACTER_STATE _state) { return animator->ChangeAnimation(_state); }

bool RenderedAnimator::IsEnd()	const	{ return animator->IsEnd();	}
bool RenderedAnimator::IsPlay()	const	{ return animator->IsPlay();}

void RenderedAnimator::AniStart()	{ animator->AniStart();	}
void RenderedAnimator::AniStop()	{ animator->AniStop();	}
void RenderedAnimator::AniPause()	{ animator->AniPause();	}
void RenderedAnimator::AniResume()	{ animator->AniResume();}
