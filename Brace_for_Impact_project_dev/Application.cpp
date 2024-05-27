#include "Application.h"

int counter = 0;

void Application::f_Update() {
	input::Update();
	Time::Update ( );
	player1.Update();
	player2.Update();

	
	SceneManager::Update();
	for (int i = 0; i < 10; i++) {
		//enemys[i].f_Update(player1);
		//enemys[i].f_Update(player2);
		/*for (int j = i + 1; j < 10; j++) {
			enemys[i].f_crash(enemys[j]);
		}*/
	}
	
	//monsters.spone(monsterHD, 2);
	MonsterManager::Update (player1 );
	BulletManager::Update ( );

	if (counter > 1000) {
		MonsterManager::spone (2 );
		counter = 0;
	}
	counter++;
}

void Application::f_FixedUpdate() {
	


}
void Application::f_Initialize(HWND hWnd,HINSTANCE  hInst_temp ) {
	mHwnd = hWnd;
	hDC = GetDC ( mHwnd );
	g_hinst = hInst_temp;
	input::Initialize();
	Time::Initailize ( );
	
	//for (int i = 0; i < 5; i++) {
	////	enemys[i].Initialize(1);
	//}
	//for (int i = 5; i < 10; i++) {
	//	//enemys[i].Initialize(2);
	//}
	////SceneManager::Initialize();
	
}
void Application::f_Render() {
	GetClientRect(mHwnd, &rt);
	mDC = CreateCompatibleDC(hDC);
	hmemDC = CreateCompatibleDC ( mDC );
	mBackBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	SelectObject ( mDC , ( HBITMAP ) mBackBitmap );

	Rectangle ( mDC , 0 , 0 , rt.right , rt.bottom );
	
	//화면 전체 크기 1680, 1050 (Y축 윈도우 창 크기때문에 30빼고 계산)
	Rectangle(mDC, r_stage.left, r_stage.top, r_stage.right, r_stage.bottom);	//필드 스테이지 UI
	Rectangle(mDC, r_info.left, r_info.top, r_info.right, r_info.bottom);	//정보 UI
	Rectangle(mDC, r_car.left, r_car.top, r_car.right, r_car.bottom);	//포신 조종실 UI
	Rectangle(mDC, r_cannon.left, r_cannon.top, r_cannon.right, r_cannon.bottom);	//차체 조종실 UI
	SceneManager::Render(mDC);

	player1.Render(mDC);
	player2.Render(mDC);
	MonsterManager::render ( mDC );
	BulletManager::rander ( mDC );
	for (int i = 0; i < 10; i++) {
		//enemys[i].f_Render(mDC);
	}

	//enemyimg.Load ( L"Enemy_2_png.png" );
	//nWidth = enemyimg.GetWidth ( ); nHeight = enemyimg.GetHeight ( );
	//img.StretchBlt ( mDC , 0 , 0 , 100 , 100 , 0 , 0 , nWidth , nHeight , SRCCOPY );
	//enemyimg.AlphaBlend ( mDC , 0 , 0 , 100 , 100 , 0 , 0 , nWidth , nHeight , 255 , bBlendOp );
	
	Time::Render(mDC);
	
	BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);

	DeleteDC ( hmemDC );
	DeleteDC(mDC);
	DeleteObject(mBackBitmap);
	
}



void Application::f_Run() {
	f_Update();
	f_FixedUpdate();
	f_Render();

}

