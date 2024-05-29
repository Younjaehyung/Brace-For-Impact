#include "Application.h"

int counter = 0;

void Application::f_Update() {
	input::Update();
	Time::Update ( );
	player1.Update();
	player2.Update();
	tank_p.Update ( );
	
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
	
	//osw - mBitmap 추가
	mBitmap = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGE_2 ) ); //---1) 비트맵 로드하기
	B_Tank_car = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TANK_CAR ) ); //---1) 비트맵 로드하기
	B_Tank_head = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TANK_HEAD ) ); //---1) 비트맵 로드하기
	B_UI_info_up = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INFO_UP ) );
	B_UI_inside = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INSIDE ) );
	//

	//B_Tank_car = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BITMAP9 ) ); //---1) 비트맵 로드하기
	//B_Tank_head = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BITMAP10 ) ); //---1) 비트맵 로드하기
	tank_p.Init ( g_hinst );
	player1.Init ( g_hinst);
}
void Application::f_Render() {
	GetClientRect(mHwnd, &rt);
	mDC = CreateCompatibleDC(hDC);
	hmemDC = CreateCompatibleDC ( mDC );
	mBackBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	SelectObject ( mDC , ( HBITMAP ) mBackBitmap );

	Rectangle ( mDC , 0 , 0 , rt.right , rt.bottom );
	


	//화면 전체 크기 1680, 1050 (Y축 윈도우 창 크기때문에 30빼고 계산)
	Rectangle ( mDC , r_stage.left , r_stage.top , r_stage.right , r_stage.bottom );	//필드 스테이지 UI
	Rectangle ( mDC , r_info.left , r_info.top , r_info.right , r_info.bottom );	//정보 UI
	Rectangle ( mDC , r_car.left , r_car.top , r_car.right , r_car.bottom );	//포신 조종실 UI
	Rectangle ( mDC , r_cannon.left , r_cannon.top , r_cannon.right , r_cannon.bottom );	//차체 조종실 UI

	Rectangle ( mDC , r_playground.left , r_playground.top , r_playground.right , r_playground.bottom );	//차체 조종실 UI

	SceneManager::Render ( mDC );


	//OSW - hmemDC추가
	SelectObject ( hmemDC , ( HBITMAP ) mBitmap );
	StretchBlt ( mDC , 0 , 0 , r_stage.right , r_stage.bottom , hmemDC , 0 , 0 , 512 , 480 , SRCCOPY );

	//UI
	SelectObject ( hmemDC , ( HBITMAP ) B_UI_info_up );
	TransparentBlt ( mDC , 0 , 668 , 1024 , 128 , hmemDC , 0 , 0 , 1024 , 128 , RGB ( 255 , 255 , 255 ) );

	//UI 탱크 내부
	SelectObject ( hmemDC , ( HBITMAP ) B_UI_inside );
	TransparentBlt ( mDC , r_playground.left , r_playground.top - 50 , 656 , 1024 , hmemDC , 0 , 0 , 656 , 1024 , RGB ( 255 , 255 , 255 ) );

	//===


	player1.Render( hmemDC , mDC );
	player2.Render( hmemDC , mDC );
	MonsterManager::render ( mDC );
	BulletManager::rander ( mDC );
	tank_p.render (hmemDC,mDC);
	
	Time::Render ( mDC );
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

