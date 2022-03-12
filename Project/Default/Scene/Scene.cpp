#include "Stdafx/stdafx.h"

#include "Scene/Scene.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

GameObject* Scene::GetObjectByName(std::wstring _name)
{
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
		if ((*iter)->CompareName(_name)) return (*iter);
	return NULL;
}
