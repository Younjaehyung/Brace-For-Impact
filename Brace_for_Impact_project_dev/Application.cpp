#include "Application.h"


void Application::f_Update() {
	input::Update();
	player1.f_Update();
	player2.f_Update();

	for (int i = 0; i < 10; i++) {
		enemys[i].f_Update(player1);
	//	enemys[i].f_Update(player2);
		for (int j = i + 1; j < 10; j++) {
			enemys[i].f_crash(enemys[j]);
		}
	}
}

void Application::f_FixedUpdate() {
	


}
void Application::f_Initialize(HWND hWnd) {
	mHwnd = hWnd;
	input::Initialize();

	for (int i = 0; i < 5; i++) {
		enemys[i].f_init(1);
	}
	for (int i = 5; i < 10; i++) {
		enemys[i].f_init(2);
	}

	hDC = GetDC(mHwnd);
}
void Application::f_Render() {
	GetClientRect(mHwnd, &rt);
	mDC = CreateCompatibleDC(hDC);
	mBackBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	SelectObject(mDC, (HBITMAP)mBackBitmap);
	Rectangle(mDC, 0, 0, rt.right, rt.bottom);
	
	//화면 전체 크기 1680, 1050 (Y축 윈도우 창 크기때문에 30빼고 계산)
	Rectangle(mDC, r_stage.left, r_stage.top, r_stage.right, r_stage.bottom);	//필드 스테이지 UI
	Rectangle(mDC, r_info.left, r_info.top, r_info.right, r_info.bottom);	//정보 UI
	Rectangle(mDC, r_car.left, r_car.top, r_car.right, r_car.bottom);	//포신 조종실 UI
	Rectangle(mDC, r_cannon.left, r_cannon.top, r_cannon.right, r_cannon.bottom);	//차체 조종실 UI

	player1.f_Render(mDC);
	player2.f_Render(mDC);

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

