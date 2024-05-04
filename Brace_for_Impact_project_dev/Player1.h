#pragma once
#include <Windows.h>
class Player1
{

private:
	RECT rect;
	int count = 0;
	

public:

	Player1();
	void f_Render(HDC mDC);
	void f_Update();
	void f_FixedUpdate();
	RECT f_ReturnRect();
};

