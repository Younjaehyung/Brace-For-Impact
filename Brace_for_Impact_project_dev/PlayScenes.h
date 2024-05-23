#pragma once
#include "Scene.h"

class PlayScenes : public Scene {
public :
	PlayScenes();
	~PlayScenes();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC) override;
};