#include "Stdafx/stdafx.h"

#include "Rendered.h"

Rendered::Rendered()
	: Component((const Component_ID)typeid(Rendered).name())
{
	byCamera = false;
}

Rendered::~Rendered() { }

void Rendered::Operation() { }
