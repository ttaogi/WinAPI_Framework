#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "Image/Image.h"

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
			RECT rc;

			if (byCamera)	rc = rcT->GetScreenRectByCamera();
			else			rc = rcT->GetScreenRect();

			switch (renderingType)
			{
			case RENDERED_IMAGE_RENDERING_TYPE::DEFAULT:
			{
				image->AlphaRender(_hdc, rc.left, rc.top, alpha);
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
