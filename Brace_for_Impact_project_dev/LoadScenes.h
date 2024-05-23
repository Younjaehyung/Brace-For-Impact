#pragma once
#include "SceneManager.h"
#include "PlayScenes.h"

void LoadScenes()
{
	SceneManager::CreateScene<PlayScenes>(L"PlayScenes");
	//SceneManager::CreateScene<EndScene>(L"EndScene");
	//SceneManager::CreateScene<TitleScene>(L"TitleScene");

	SceneManager::LoadScene(L"PlayScene");
}