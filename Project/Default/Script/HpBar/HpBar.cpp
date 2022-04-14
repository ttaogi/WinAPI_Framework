#include "Stdafx/stdafx.h"

#include "Script/HpBar/HpBar.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

HpBar::HpBar()
	: Component((const Component_ID)typeid(HpBar).name())
{
	hpRateVec.clear();
}

HpBar::~HpBar() { }

void HpBar::Update() { }

void HpBar::LateUpdate()
{
	GameObject* background = gameObject->GetGameObjectByName(SKIG_HP_BAR_BACKGROUND);
	GameObject* hp = gameObject->GetGameObjectByName(SKIG_HP_BAR_HP);

	if (hpRateVec.empty())
	{
		background->SetActive(false);
		hp->SetActive(false);
	}
	else
	{
		background->SetActive(true);
		hp->SetActive(true);

		hp->GetComponent<RectTransform>()->SetRect((long)(hpRateVec[0] * HP_BAR_WIDTH), HP_BAR_HEIGHT);
		hp->GetComponent<Transform>()->SetPosition(D_POINT{
			background->GetComponent<Transform>()->GetPosition().x - (long)(((int)(HP_BAR_WIDTH * (1 - hpRateVec[0])) + 1) / 2),
			background->GetComponent<Transform>()->GetPosition().y
			});
	}

	hpRateVec.clear();
}

void HpBar::PrepareRender(float _hpRate)
{
	if (hpRateVec.empty()) hpRateVec.push_back(_hpRate);
}
