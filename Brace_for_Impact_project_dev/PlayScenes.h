#pragma once
#include "Scene.h"
#include "enemy1.h"
class PlayScenes : public Scene {
public :
	PlayScenes();
	~PlayScenes();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC) override;
	void SetName(const std::wstring& name) { mName = name; }
	std::wstring& GetName() { return mName; }

private:
	std::wstring mName;
};