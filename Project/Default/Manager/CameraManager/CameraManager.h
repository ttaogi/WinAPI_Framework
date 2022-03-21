#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class GameObject;

class CameraManager : public SingletonBase<CameraManager>
{
private:
	GameObject* target;
	POINT coordinateRevision;
	D_POINT previousPos;
public:
	CameraManager();
	virtual ~CameraManager();

	HRESULT init(GameObject* _target = NULL);
	void update();
	void release();

	POINT getRevision();
};