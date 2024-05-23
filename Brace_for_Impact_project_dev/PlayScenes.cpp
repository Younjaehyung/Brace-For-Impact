#include "PlayScenes.h"

PlayScenes::PlayScenes()
{
}

PlayScenes::~PlayScenes()
{
}

void PlayScenes :: Initialize() {
	for (size_t i = 0; i < 100; i++)
	{
		GameObject* obj = new GameObject();
		obj->SetPosition(rand() % 1600, rand() % 900);
		AddGameObject(obj);
	}

}
void PlayScenes :: Update() {
	Scene::Update();
}


void PlayScenes :: LateUpdate() {

	Scene::LateUpdate();

}

void PlayScenes :: Render(HDC hdc) {
	Scene::Render(hdc);
}