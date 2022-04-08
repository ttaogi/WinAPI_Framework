#include "Stdafx/stdafx.h"

#include "Script/Effect/FlameBurst.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

FlameBurst::FlameBurst()
	: Component((const Component_ID)typeid(FlameBurst).name())
{
	rAnim = NULL;
}

void FlameBurst::Update()
{
	if (rAnim->IsEnd()) gameObject->SetActive(false);
}
