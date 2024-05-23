#pragma once
#include "GameObject.h"
#include <vector>
class Scene
{
public:
	Scene();
	~Scene();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC);

	void AddGameObject(GameObject* gameobject);

private:
	std::vector<GameObject*> mGameObjects;
};

