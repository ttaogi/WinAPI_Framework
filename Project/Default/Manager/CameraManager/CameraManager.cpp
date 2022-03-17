#include "Stdafx/stdafx.h"

#include "Manager/CameraManager/CameraManager.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

HRESULT CameraManager::init(GameObject* _target)
{
	target = _target;

	if (target)
	{
		coordinateRevision = target->GetComponent<Transform>()->GetPosition().ToPoint();
		coordinateRevision.x -= WINSIZE_X / 2;
		coordinateRevision.y -= WINSIZE_Y / 2;
	}
	else
		coordinateRevision = POINT{ 0, 0 };

	previousPos.x = coordinateRevision.x;
	previousPos.y = coordinateRevision.y;

	return S_OK;
}

void CameraManager::update()
{
	if (target)
	{
		coordinateRevision = target->GetComponent<Transform>()->GetPosition().ToPoint();
		coordinateRevision.x -= WINSIZE_X / 2;
		coordinateRevision.y -= WINSIZE_Y / 2;

		previousPos.x = (0.8f * previousPos.x + 0.2f * coordinateRevision.x);
		previousPos.y = (0.8f * previousPos.y + 0.2f * coordinateRevision.y);
		coordinateRevision.x = (long)previousPos.x;
		coordinateRevision.y = (long)previousPos.y;
	}
	else
		coordinateRevision = POINT{ 0, 0 };
}

void CameraManager::release() { }

POINT CameraManager::getRevision() { return coordinateRevision; }

CameraManager::CameraManager()
{
	target = NULL;
	coordinateRevision = POINT{ 0, 0 };
	previousPos = D_POINT{ 0, 0 };
}

CameraManager::~CameraManager() { release(); }
