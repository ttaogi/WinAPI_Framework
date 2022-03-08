#include "Stdafx/stdafx.h"

#include "RenderedAnimator.h"
#include "Image/Animator/Animator.h"

RenderedAnimator::RenderedAnimator()
	: Component((const Component_ID)typeid(RenderedAnimator).name())
{
	animator = new Animator();
	animator->Init();
}

RenderedAnimator::~RenderedAnimator()
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void RenderedAnimator::Operation() { }

void RenderedAnimator::Render(HDC _hdc, POINT _pos)
{
	animator->AnimationRender(_hdc, _pos);
}

void RenderedAnimator::Init() { }

void RenderedAnimator::Update(HWND _hWnd)
{
	animator->Update();
}

void RenderedAnimator::LateUpdate() { }

void RenderedAnimator::AddAnimation(CHARACTER_STATE _state, Animation* _animation)
{
	animator->AddAnimation(_state, _animation);
}

bool RenderedAnimator::ChangeAnimation(CHARACTER_STATE _state)
{
	return animator->ChangeAnimation(_state);
}

bool RenderedAnimator::IsEnd() const
{
	return animator->IsEnd();
}

bool RenderedAnimator::IsPlay() const
{
	return animator->IsPlay();
}

void RenderedAnimator::AniStart()
{
	animator->AniStart();
}

void RenderedAnimator::AniStop()
{
	animator->AniStop();
}

void RenderedAnimator::AniPause()
{
	animator->AniPause();
}

void RenderedAnimator::AniResume()
{
	animator->AniResume();
}
