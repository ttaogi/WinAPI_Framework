#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"
#include "RenderedImage.h"

RenderedImage::RenderedImage()
	: Component((const Component_ID)typeid(RenderedImage).name())
{
	alpha = 255;
	renderingType = RENDERED_IMAGE_RENDERING_TYPE::DEFAULT;
	image = NULL;
}

RenderedImage::~RenderedImage() { }

void RenderedImage::Operation() { }

void RenderedImage::Render(HDC _hdc)
{
	if (enabled && image)
	{
		RectTransform* rcT = gameObject->GetComponent<RectTransform>();
		if (rcT)
		{
			RECT rc = rcT->GetScreenRect();

			switch (renderingType)
			{
			case RENDERED_IMAGE_RENDERING_TYPE::DEFAULT:
			{
				POINT revision = CAMERA->GetRevision();
				image->AlphaRender(_hdc, rc.left - revision.x, rc.top - revision.y, alpha);
				//image->Render(_hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
				break;
			}
			case RENDERED_IMAGE_RENDERING_TYPE::LOOP:
				image->LoopAlphaRender(_hdc, &rc, 0, 0, alpha);
				//image->LoopRender(_hdc, &rc, 0, 0);
				break;
			}
		}
	}
}
