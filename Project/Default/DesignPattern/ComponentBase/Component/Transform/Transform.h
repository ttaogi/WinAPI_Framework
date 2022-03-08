#pragma once

#include "DesignPattern/ComponentBase/Component/Component.h"
#include "Utility/CommonClasses/CommonClasses.h"

class Transform : public Component
{
private:
	friend class GameObject;

	D_POINT position;
protected:
public:
	Transform();
	Transform(Transform* _t);
	virtual ~Transform();

	virtual void Operation() override;

	D_POINT	GetPosition() const { return position; }
	void	SetPosition(const D_POINT _position) { position = _position; }
};