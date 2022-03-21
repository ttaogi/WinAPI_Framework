#pragma once

#include "DesignPattern/ComponentBase/Component/Rendered/Rendered.h"

class Image;

class RenderedImage : public Rendered
{
private:
	int alpha;
	RENDERED_IMAGE_RENDERING_TYPE renderingType;
	Image* image;
protected:
public:
	RenderedImage();
	virtual ~RenderedImage();

	virtual void Operation() override;

	virtual void Render(HDC _hdc) override;

	int		GetAlpha() const		{ return alpha; }
	void	SetAlpha(int _alpha)	{ alpha = _alpha; }
	RENDERED_IMAGE_RENDERING_TYPE GetRenderingType() const { return renderingType; }
	void SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE _renderingType) { renderingType = _renderingType; }
	Image*	GetImage()				{ return image; }
	void	SetImage(Image* _image)	{ image = _image; }
};
