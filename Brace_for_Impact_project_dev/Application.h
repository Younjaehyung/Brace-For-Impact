#pragma once
#include <Windows.h>
#include "Player1.h"

class Application {
private:
	Player1 player1;
	
	HWND mHwnd;
	HDC mDC;

	
	HBITMAP mBackBitmap;

public:
	
	void f_Run();
	void f_Render();
	void f_Update();
	void f_FixedUpdate();
	void f_Initialize(HWND hWnd);
};

