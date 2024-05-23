#pragma once
#include "CommonInclude.h"

class GameObject
{
	public:
		GameObject();
		~GameObject();

		void Update();
		void LateUpdate();
		void Render(HDC);


		void SetPosition(float x, float y) {
			mx = x;
			my = y;

		}

		float GetPositionx() { return mx; }
		float GetPositiony() { return my; }

	private:
		//게임 오브젝트 좌표
		float mx;
		float my;
};

