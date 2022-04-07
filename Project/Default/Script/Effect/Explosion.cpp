#include "Stdafx/stdafx.h"

#include "Script/Effect/Explosion.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

Explosion::Explosion()
	: Component((const Component_ID)typeid(Explosion).name())
{
	rAnim = NULL;
}

void Explosion::Update()
{
	if (rAnim->IsEnd()) gameObject->SetActive(false);
}
