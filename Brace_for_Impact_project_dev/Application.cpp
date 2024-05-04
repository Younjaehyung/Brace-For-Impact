#include "Application.h"



void Application::f_Update() {

	player1.f_Update();
}

void Application::f_FixedUpdate() {



}
void Application::f_Initialize(HWND hWnd) {
	mHwnd = hWnd;
	mDC = GetDC(mHwnd);
}
void Application::f_Render() {

	player1.f_Render(mDC);
	
}



void Application::f_Run() {
	f_Update();
	f_FixedUpdate();
	f_Render();

}

