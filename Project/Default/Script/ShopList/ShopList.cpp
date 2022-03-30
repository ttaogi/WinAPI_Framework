#include "Stdafx/stdafx.h"

#include "Script/ShopList/ShopList.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedText/RenderedText.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#pragma region ShopListPanel
ShopListPanel::ShopListPanel()
	: Component((const Component_ID)typeid(ShopListPanel).name()) { }

void ShopListPanel::Update()
{
	if (!enabled) return;

	if (GAMEMANAGER->GetPhase() == PHASE::PHASE_SHOPPING && MOUSE_CLICKED)
	{
		RectTransform* rcT = gameObject->GetComponent<RectTransform>();
		if (rcT == NULL) return;
		RECT rc = rcT->GetScreenRect();
		if (PtInRect(&rc, POINT_MOUSE))
		{
			Notify(EVENT::SHOP_LIST_PANEL_CLICK);
			MOUSE_CLICKED = false;
		}
	}
}
#pragma endregion ShopListPanel


#pragma region ShopList
ShopList::ShopList()
	: Component((const Component_ID)typeid(ShopList).name()) { }

void ShopList::OnNotify(Subject* _subject, EVENT _event)
{
	if (GAMEMANAGER->GetPhase() != PHASE::PHASE_SHOPPING) return;

	vector<GameObject*> panelVec;
	ShopListPanel* subject = NULL;
	panelVec.clear();

	switch (_event)
	{
	case EVENT::SHOP_LIST_PANEL_CLICK:
		gameObject->GetGameObjectsByTag(&panelVec, TAG::SHOP_PANEL);
		for (auto iter = panelVec.begin(); iter != panelVec.end(); ++iter)
		{
			RenderedImage* rImg = (*iter)->GetComponent<RenderedImage>();
			if (rImg) rImg->SetEnabled(false);
		}

		subject = dynamic_cast<ShopListPanel*>(_subject);
		if (subject)
		{
			subject->gameObject->GetComponent<RenderedImage>()->SetEnabled(true);
			SetSelectedItem(subject->GetEquip());
		}
		break;
	case EVENT::BUY_BUTTON_CLICK:
		if (GAMEDATA->GetGold() >= selectedItem.priceBuy)
		{
			GAMEDATA->AddItem(selectedItem);
			GAMEDATA->SetGold(GAMEDATA->GetGold() - selectedItem.priceBuy);

			GameObject* goldGo = gameObject->GetGameObjectByName(SKIG_SHOP_LIST_GOLD);
			if (goldGo)
				goldGo->GetComponent<RenderedText>()->SetStr(to_wstring(GAMEDATA->GetGold()));
		}
		break;
	case EVENT::EXIT_BUTTON_CLICK:
		Notify(EVENT::EXIT_BUTTON_CLICK);
		break;
	}
}
#pragma endregion ShopList


#pragma region BuyButton
BuyButton::BuyButton()
	: Component((const Component_ID)typeid(BuyButton).name()) { }

void BuyButton::Update()
{
	if (!enabled) return;

	if (GAMEMANAGER->GetPhase() == PHASE::PHASE_SHOPPING && MOUSE_CLICKED)
	{
		RectTransform* rcT = gameObject->GetComponent<RectTransform>();
		if (rcT == NULL) return;
		RECT rc = rcT->GetScreenRect();
		if (PtInRect(&rc, POINT_MOUSE))
		{
			Notify(EVENT::BUY_BUTTON_CLICK);
			MOUSE_CLICKED = false;
		}
	}
}
#pragma endregion BuyButton


#pragma region ExitButton
ExitButton::ExitButton()
	: Component((const Component_ID)typeid(ExitButton).name()) { }

void ExitButton::Update()
{
	if (!enabled) return;

	if (GAMEMANAGER->GetPhase() == PHASE::PHASE_SHOPPING && MOUSE_CLICKED)
	{
		RectTransform* rcT = gameObject->GetComponent<RectTransform>();
		if (rcT == NULL) return;
		RECT rc = rcT->GetScreenRect();
		if (PtInRect(&rc, POINT_MOUSE))
		{
			Notify(EVENT::EXIT_BUTTON_CLICK);
			MOUSE_CLICKED = false;
		}
	}
}
#pragma endregion ExitButton
