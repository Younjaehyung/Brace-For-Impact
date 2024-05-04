#include "Application.h"



void Application::f_Update() {

	player1.f_Update();
	for (int i = 0; i < 10; i++) {
		enemys[i].f_Update(player1);
		for (int j = i + 1; j < 10; j++) {
			enemys[i].f_crash(enemys[j]);
		}
	}
}

void Application::f_FixedUpdate() {
	


}
void Application::f_Initialize(HWND hWnd) {
	mHwnd = hWnd;
	for (int i = 0; i < 10; i++) {
		enemys[i].f_init();
	}

	hDC = GetDC(mHwnd);
}
void Application::f_Render() {
	GetClientRect(mHwnd, &rt);
	mDC = CreateCompatibleDC(hDC);
	mBackBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	SelectObject(mDC, (HBITMAP)mBackBitmap);
	Rectangle(mDC, 0, 0, rt.right, rt.bottom);

	player1.f_Render(mDC);
	for (int i = 0; i < 10; i++) {
		enemys[i].f_Render(mDC);
	}


	BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
	DeleteDC(mDC);
	DeleteObject(mBackBitmap);
	
}



void Application::f_Run() {
	f_Update();
	f_FixedUpdate();
	f_Render();

}

