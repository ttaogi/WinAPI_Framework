#include "Stdafx/stdafx.h"

#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"

#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rigidbody/Rigidbody.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

Collider::Collider()
	: Component((const Component_ID)typeid(Collider).name())
{
	isTrigger = false;
}

Collider::~Collider() { }

void Collider::CheckCollision(std::vector<Collision>* _colVec, Collider* _col)
{
	if (!enabled || !_col) return;

	RectTransform* rcT1 = gameObject->GetComponent<RectTransform>();
	RectTransform* rcT2 = _col->gameObject->GetComponent<RectTransform>();

	if (rcT1 && rcT2)
	{
		RECT collisionRc{ 0, 0, 0, 0 };
		RECT rc1 = rcT1->GetScreenRect();
		RECT rc2 = rcT2->GetScreenRect();

		if (IntersectRect(&collisionRc, &rc1, &rc2) != 0)
		{
			SetRect(&collisionRc, 0, 0, collisionRc.right - collisionRc.left, collisionRc.bottom - collisionRc.top);
			bool horizontalCollision = false;

			if (collisionRc.right > collisionRc.bottom) // vertical collision.
			{
				if ((rc1.top + rc1.bottom) < (rc2.top + rc2.bottom)) // this is upper.
					SetRect(&collisionRc, 0, 0, 0, -1 * abs(collisionRc.bottom));
				else // this is lower.
					SetRect(&collisionRc, 0, 0, 0, abs(collisionRc.bottom));
			}
			else // horizontal collision.
			{
				horizontalCollision = true;
				if ((rc1.left + rc1.right) < (rc2.left + rc2.right)) // this is left.
					SetRect(&collisionRc, 0, 0, -1 * abs(collisionRc.right), 0);
				else // this is right.
					SetRect(&collisionRc, 0, 0, abs(collisionRc.right), 0);
			}

			if(!isTrigger && !_col->GetIsTrigger())
			{
				Rigidbody* rb1 = gameObject->GetComponent<Rigidbody>();
				if (rb1)
				{
					VELOCITY v = rb1->GetVelocity();
					if (horizontalCollision)	v.x = 0;
					else						v.y = 0;
					rb1->SetVelocity(v);
				}
				Rigidbody* rb2 = _col->gameObject->GetComponent<Rigidbody>();
				if (rb2)
				{
					VELOCITY v = rb2->GetVelocity();
					if (horizontalCollision)	v.x = 0;
					else						v.y = 0;
					rb2->SetVelocity(v);
				}

				if (rb1 && rb2)
				{
					if ((rb1->GetMass() == 0 && rb2->GetMass() == 0) ||
						(rb1->GetMass() != 0 && rb2->GetMass() != 0) )
					{
						D_POINT pos1 = rb1->transform->GetPosition();
						D_POINT pos2 = rb2->transform->GetPosition();
						pos1.x += collisionRc.right / 2;
						pos1.y += collisionRc.bottom / 2;
						pos2.x -= collisionRc.right / 2;
						pos2.y -= collisionRc.bottom / 2;
						rb1->MovePosition(pos1);
						rb2->MovePosition(pos2);
					}
					else if (rb1->GetMass() == 0)
					{
						D_POINT pos2 = rb2->transform->GetPosition();
						pos2.x -= collisionRc.right;
						pos2.y -= collisionRc.bottom;
						rb2->MovePosition(pos2);
					}
					else
					{
						D_POINT pos1 = rb1->transform->GetPosition();
						pos1.x += collisionRc.right;
						pos1.y += collisionRc.bottom;
						rb1->MovePosition(pos1);
					}
				}
				else if (rb1)
				{
					D_POINT pos1 = rb1->transform->GetPosition();
					pos1.x += collisionRc.right;
					pos1.y += collisionRc.bottom;
					rb1->MovePosition(pos1);
				}
				else if (rb2)
				{
					D_POINT pos2 = rb2->transform->GetPosition();
					pos2.x -= collisionRc.right;
					pos2.y -= collisionRc.bottom;
					rb2->MovePosition(pos2);
				}
				else
				{
					// Nothing.
				}
			}

			Collision collision{ this, _col };
			_colVec->push_back(collision);
		}
	}
}
