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
	blackBrush = CreateSolidBrush ( RGB ( 50 , 50 , 50 ) );

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

	SelectObject ( mDC , blackBrush );
	Rectangle ( mDC , r_info.left , r_info.top , r_info.right , r_info.bottom );	//정보 UI
	SceneManager::Render ( mDC );


	//OSW - hmemDC추가

	StretchBlt ( mDC , 0 , 0 , r_stage.right , r_stage.bottom , 
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 , 0 , 512 , 480 , SRCCOPY );

	//UI B_UI_info_up

	//UI 비트맵
	TransparentBlt ( mDC , r_playground.left , r_playground.top - 50 , 656 , 1024 , 
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Inside" ) , 0 , 0 , 656 , 1024 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 0 , 0 , 1024 , 768 , 
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Stage" ) , 0 , 0 , 1024 , 768 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 0 , 768 , 1024 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_info_up" ) , 0 , 0 , 1024 , 128 , RGB ( 255 , 255 , 255 ) );

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

