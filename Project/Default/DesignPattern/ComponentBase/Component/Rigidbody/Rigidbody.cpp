#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Rigidbody/Rigidbody.h"

#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"

Rigidbody::Rigidbody()
	: Component((const Component_ID)typeid(Rigidbody).name())
{
	drag = DEFAULT_DRAG;
	gravity = GRAVITY;
	mass = 1.0;
	velocity = VELOCITY{ 0, 0 };
}

Rigidbody::~Rigidbody() { }

void Rigidbody::AddForce(D_POINT _f)
{
	if (mass <= 0) return;

	double dX = TIME->GetScaledElapsedTime() * _f.x / mass;
	double dY = TIME->GetScaledElapsedTime() * _f.y / mass;

	velocity.x += dX;
	velocity.y += dY;

	if (velocity.x < -1 * MAX_LIMIT_VELOCITY_X) velocity.x = -1 * MAX_LIMIT_VELOCITY_X;
	if (velocity.y < -1 * MAX_LIMIT_VELOCITY_Y) velocity.y = -1 * MAX_LIMIT_VELOCITY_Y;

	if (velocity.x > MAX_LIMIT_VELOCITY_X) velocity.x = MAX_LIMIT_VELOCITY_X;
	if (velocity.y > MAX_LIMIT_VELOCITY_Y) velocity.y = MAX_LIMIT_VELOCITY_Y;

	if (abs(velocity.x) <= MIN_LIMIT_VELOCITY_X) velocity.x = 0;
	if (abs(velocity.y) <= MIN_LIMIT_VELOCITY_Y) velocity.y = 0;
}

void Rigidbody::MovePosition(D_POINT _p)
{
	transform->SetPosition(_p);
}

void Rigidbody::MovePosition()
{
	double dX = TIME->GetScaledElapsedTime() * velocity.x;
	double dY = TIME->GetScaledElapsedTime() * velocity.y;
	D_POINT pos = transform->GetPosition();

	pos.x += dX;
	pos.y += dY;

	transform->SetPosition(pos);
}

void Rigidbody::AdaptDrag()
{
	if(velocity.x != 0) velocity.x *= pow(drag, TIME->GetScaledElapsedTime());
	if(velocity.y != 0) velocity.y *= pow(drag, TIME->GetScaledElapsedTime());

	if (abs(velocity.x) <= MIN_LIMIT_VELOCITY_X) velocity.x = 0;
	if (abs(velocity.y) <= MIN_LIMIT_VELOCITY_Y) velocity.y = 0;
}

void Rigidbody::AdaptGravity()
{
	AddForce(D_POINT{ 0, gravity });
}
