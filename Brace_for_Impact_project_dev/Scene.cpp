#include "Scene.h"

Scene::Scene() : mGameObjects{}
{
}
Scene::~Scene()
{
}
void Scene::Initialize()
{
}
void Scene::Update()
{
	for (GameObject* gameObj : mGameObjects)
	{
		gameObj->Update();
	}
}
void Scene::LateUpdate()
{
	for (GameObject* gameObj : mGameObjects)
	{
		gameObj->LateUpdate();
	}
}
void Scene::Render(HDC mDC)
{
	for (GameObject* gameObj : mGameObjects)
	{
		gameObj->Render(mDC);
	}
}

void Scene::AddGameObject(GameObject* gameObject)
{
	mGameObjects.push_back(gameObject);
}