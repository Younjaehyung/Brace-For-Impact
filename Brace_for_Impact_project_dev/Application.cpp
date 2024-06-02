#include "Application.h"

int counter = 0;

void Application::f_Update() {
	input::Update();
	Time::Update ( );
	
	SceneManager::Update();

	gameobject.Update ( );
	
}

void Application::f_FixedUpdate() {
	


}
void Application::f_Initialize ( HWND hWnd , HINSTANCE  hInst_temp ) {
	mHwnd = hWnd;
	hDC = GetDC ( mHwnd );
	blackBrush = CreateSolidBrush ( RGB ( 20 , 20 , 20 ) );
	redBrush = CreateSolidBrush ( RGB ( 200 , 50 , 50 ) );

	g_hinst = hInst_temp;
	input::Initialize ( );
	Time::Initailize ( );
	HandleResize ( );
	gameobject.Initailize ( hDC,g_hinst );

	
	
};
void Application::f_Render() {
	HandleResize ( );
	SelectObject ( mDC , ( HBITMAP ) mBackBitmap );

	Rectangle ( mDC , 0 , 0 , rt.right , rt.bottom );
	
	

	//화면 전체 크기 1680, 1050 (Y축 윈도우 창 크기때문에 30빼고 계산)
	Rectangle ( mDC , r_stage.left , r_stage.top , r_stage.right , r_stage.bottom );	//필드 스테이지 UI
	Rectangle ( mDC , r_car.left , r_car.top , r_car.right , r_car.bottom );	//포신 조종실 UI
	Rectangle ( mDC , r_cannon.left , r_cannon.top , r_cannon.right , r_cannon.bottom );	//차체 조종실 UI
	Rectangle ( mDC , r_playground.left , r_playground.top , r_playground.right , r_playground.bottom );	//차체 조종실 UI

	
	SceneManager::Render ( mDC );


	//OSW - hmemDC추가

	StretchBlt ( mDC , 0 , 0 , r_stage.right , r_stage.bottom , 
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 , 0 , 512 , 480 , SRCCOPY );

	//UI B_UI_info_up

	//UI 비트맵
	TransparentBlt ( mDC , r_playground.left , r_playground.top , 656 , 1024  - 50, 
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Inside" ) , 0 , 0 , 656 , 1024 , RGB ( 255 , 255 , 255 ) );
	//스테이지 UI는 tank.cpp로 이동됬음. 탱크 움직임에 맞춰서 변해야 하기 때문에.
	TransparentBlt ( mDC , 0 , 768 , 1024 , 225 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Info" ) , 0 , 0 , 1024 , 252 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 0 , 640 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Player" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 760 , 640 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Player" ) , 0 , 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	//==탱크 체력
	SelectObject ( mDC , redBrush );
	Rectangle ( mDC , 100 , 780 , 300 , 780 + 64 );	//정보 UI
	TransparentBlt ( mDC , 0 , 780 , 500 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Status" ) , 0 , 0 , 575 , 64 , RGB ( 255 , 255 , 255 ) );
	
	SelectObject ( mDC , blackBrush );
	Rectangle ( mDC , 100 , 880 , 300 , 880 + 64 );	//정보 UI
	//==탱크 연료
	TransparentBlt ( mDC , 0 , 880 , 500 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Status" ) , 0 , 0 , 575 , 64 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 700 , 780 , 96 , 192 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Cooltime" ) , 96 * 0 , 0 , 96 , 192 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 800 , 780 , 96 , 192 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Cooltime" ) , 96 * 1 , 0 , 96 , 192 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 900 , 780 , 96 , 192 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Cooltime" ) , 96 * 2 , 0 , 96 , 192 , RGB ( 255 , 255 , 255 ) );

	TransparentBlt ( mDC , 500 , 780 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" ) , 0 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 500 , 880 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" ) , 0 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );


	TransparentBlt ( mDC , 1024 + 120 , 0 + 80 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Attack" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 400 , 0 + 80 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Move" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 200 , 0 -30 , 240 , 512 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Cannon" ) , 0 , 0 , 240 , 512 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 270 , 0+ 500 , 96 , 160 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Engine" ) , 0 , 0 , 96 , 160 , RGB ( 255 , 255 , 255 ) );
	
	/*TransparentBlt ( mDC , 0 , 768 , 1024 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Info_up" ) , 0 , 0 , 1024 , 128 , RGB ( 255 , 255 , 255 ) );*/
	

	//===
	gameobject.Render (mDC );



	Time::Render ( mDC );
	BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);

	DeleteDC(mDC);
	DeleteObject(mBackBitmap);
	
}

void Application::HandleResize ( ) {
	if ( mDC ) {
		DeleteDC ( mDC );
	}

	if ( mBackBitmap ) {
		DeleteObject ( mBackBitmap );
	}

	GetClientRect ( mHwnd , &rt );
	mDC = CreateCompatibleDC ( hDC );
	
	mBackBitmap = CreateCompatibleBitmap ( hDC , rt.right , rt.bottom );
}

void Application::f_Run() {
	f_Update();
	f_FixedUpdate();
	f_Render();
	
}

