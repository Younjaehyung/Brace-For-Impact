#include "PlayScenes.h"

PlayScenes::PlayScenes()
{
}

PlayScenes::~PlayScenes()
{
}

void PlayScenes :: Initialize() {
	//for (size_t i = 0; i < 10; i++)
	//{
	//	enemy1* obj  = new enemy1();
	//	obj->Initialize(1);
	//	
	//	AddGameObject(obj);
	//}

}
void PlayScenes :: Update() {
	Scene::Update();
}


void PlayScenes :: LateUpdate() {

	Scene::LateUpdate();

}

void PlayScenes :: Render(HDC hdc) {
	Scene::Render(hdc);
	StretchBlt ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 0 , 0 , 1024 * 2 , 1024 * 2 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 , 0 , 1024 , 1024 , SRCCOPY );
}