#include "Stdafx/stdafx.h"

#include "Player/Player.h"

#include "DesignPattern/ComponentBase/Component/Rigidbody/Rigidbody.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

Player::Player() : Component((const Component_ID)typeid(Player).name())
{
	hp = 100;
}

Player::~Player() { }

void Player::Operation() { }

void Player::Init() { }

void Player::FixedUpdate()
{
	Rigidbody* rb = gameObject->GetComponent<Rigidbody>();
	if (rb)
	{
		rb->AdaptGravity();
		rb->MovePosition();
		rb->AdaptDrag();
	}
}

void Player::Update()
{
	Rigidbody* rb = gameObject->GetComponent<Rigidbody>();
	if(rb)
	{
		if (KEY->IsOnceKeyDown('A') || KEY->IsStayKeyDown('A')) rb->AddForce(D_POINT{ -2 * GRAVITY, 0 });
		if (KEY->IsOnceKeyDown('D') || KEY->IsStayKeyDown('D')) rb->AddForce(D_POINT{ 2 * GRAVITY, 0 });
		if (KEY->IsOnceKeyDown('S') || KEY->IsStayKeyDown('S')) rb->AddForce(D_POINT{ 0, GRAVITY });
		if (KEY->IsOnceKeyDown('W') || KEY->IsStayKeyDown('W')) rb->AddForce(D_POINT{ 0, -10 * GRAVITY });
	}
}

void Player::LateUpdate() { }

void Player::OnCollision(Collision _col)
{
	//wcout << L"OnCollision" << endl;
}
