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
	

	g_hinst = hInst_temp;
	input::Initialize ( );
	Time::Initailize ( );
	HandleResize ( );
	gameobject.Initailize ( hDC,g_hinst );

	
	GameDC = CreateCompatibleDC ( hDC );
	mBitmap = CreateCompatibleBitmap ( hDC , 1024 * 2 , 960 * 2 );
	SelectObject ( GameDC , ( HBITMAP ) mBitmap );
};
void Application::f_Render() {
	HandleResize ( );
	SelectObject ( mDC , ( HBITMAP ) mBackBitmap );
	
	//Rectangle ( mDC , 0 , 0 , rt.right , rt.bottom );
	
	

	////화면 전체 크기 1680, 1050 (Y축 윈도우 창 크기때문에 30빼고 계산)
	//Rectangle ( mDC , r_stage.left , r_stage.top , r_stage.right , r_stage.bottom );	//필드 스테이지 UI
	//Rectangle ( mDC , r_car.left , r_car.top , r_car.right , r_car.bottom );	//포신 조종실 UI
	//Rectangle ( mDC , r_cannon.left , r_cannon.top , r_cannon.right , r_cannon.bottom );	//차체 조종실 UI
	//Rectangle ( mDC , r_playground.left , r_playground.top , r_playground.right , r_playground.bottom );	//차체 조종실 UI

	//SceneManager::Render ( mDC );

	switch ( Stage_num ) {
	case 0:

		break;
	case 1:
		break;
	}

	if ( input::GetKey ( eKeyCode::P ) ) {
		Stage_num = 1;
	}
	else if ( input::GetKey ( eKeyCode::O ) ) {
		Stage_num = 0;
	}

	//OSW - hmemDC추가

	//StretchBlt ( mDC , 0 , 0 , r_stage.right , r_stage.bottom , 
	//	Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 , 0 , 512 , 480 , SRCCOPY );
	/*StretchBlt ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 0 , 0 , 1024*2 , 960*2 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 , 0 , 1024 , 960 , SRCCOPY );*/

	
	
	if ( PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).left + 512 >= 2048 ) {
		TankController::camera.left = 512 * 2;
	}
	else {
		TankController::camera.left = max ( 0 , PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).left - 512 );
	}
	
	if ( PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).top + 480 >= 1920 ) {
		TankController::camera.top = 480 * 2;
	}
	else {
		TankController::camera.top = max ( 0 , PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).top - 480 );
	}
	
	gameobject.Render ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ),mDC );
	

	//StretchBlt ( mDC , 0 , 0 , 1024 , 780, Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , left , top , 1024 , 960 , SRCCOPY );
	BitBlt ( mDC , 0 , 0 , 1024 , 780 , Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , TankController::camera.left , TankController::camera.top , SRCCOPY );

	TransparentBlt ( mDC , r_playground.left , r_playground.top , 656 , 1024 - 50 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Inside" ) , 0 , 0 , 656 , 1024 , RGB ( 255 , 255 , 255 ) );

	
	gameobject.Camera_UI ( mDC );
	//Rectangle ( mDC , 0 , 0 , 1024 , 780 );
	//UI 비트맵
	

	//플레이어 활동 가능 구역
	//Rectangle ( mDC , 1024 + 100 , 0 + 150 , 1024 + 550 , 0 + 100 + 750 );
	//===OSW===
	

	

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

