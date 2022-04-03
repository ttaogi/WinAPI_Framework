#include "Stdafx/stdafx.h"

#include "Script/Tile/Tile.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

#pragma region Tile
Tile::Tile()
	: Component((const Component_ID)typeid(Tile).name()) { }

void Tile::Update()
{
	if (!enabled) return;

	RectTransform* rcT = gameObject->GetComponent<RectTransform>();

	if(rcT)
	{
		RECT area = rcT->GetScreenRectByCamera();
		area = MakeRectCWH(
			POINT{ (area.left + area.right) / 2,(area.top + area.bottom) / 2 },
			(area.right - area.left) / 2, (area.bottom - area.top) / 2);

		if (MOUSE_CLICKED && PtInRect(&area, POINT_MOUSE))
			Notify(EVENT::TILE_CLICK);
		else if (MOUSE_CLICKED_RIGHT && PtInRect(&area, POINT_MOUSE))
			Notify(EVENT::TILE_CLICK_RIGHT);
	}
}
#pragma endregion Tile


#pragma region TileFocus
TileFocus::TileFocus()
	: Component((const Component_ID)typeid(TileFocus).name()) { }

void TileFocus::Update()
{
	if (!enabled) return;

	RectTransform* rcT = gameObject->GetComponent<RectTransform>();
	RenderedImage* rImg = gameObject->GetComponent<RenderedImage>();

	if (rcT && rImg)
	{
		RECT area = rcT->GetScreenRectByCamera();

		area = MakeRectCWH(
			POINT{(area.left + area.right) / 2, (area.top + area.bottom) / 2},
			(area.right - area.left) / 2, (area.bottom - area.top) / 2);

		if (PtInRect(&area, POINT_MOUSE))	rImg->SetEnabled(true);
		else								rImg->SetEnabled(false);
	}
}
#pragma endregion TileFocus
