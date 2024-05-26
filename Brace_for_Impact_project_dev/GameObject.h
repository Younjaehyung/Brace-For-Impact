#pragma once
#include "CommonInclude.h"

class GameObject
{
	public:
		GameObject();
		~GameObject();

		virtual void Update() ;
		void LateUpdate();
		virtual void Render(HDC);
		virtual void Initialize();

		void SetPosition(float right, float top,float left,float bottom) {
			rect.bottom = bottom;
			rect.left = left;
			rect.right = right;
			rect.top = top;

		}

		float GetPositionx() { return mx; }
		float GetPositiony() { return my; }

	protected:
		//게임 오브젝트 좌표
		float mx;
		float my;
		RECTS rect;
};

