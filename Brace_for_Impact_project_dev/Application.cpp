#include "Application.h"

void Application::f_Update() {
	input::Update();
	Time::Update ( );
	Debugging::InputMod ( );
	
	if ( Debugging::ReturnMod ( ) != 3 ) {	//Debugging pause
		GameManager::getInstance ( ).Update ( );
	}
	
}

void Application::f_FixedUpdate ( ) {
	


}




void Application::f_Initialize ( HWND hWnd , HINSTANCE  hInst_temp ) {
	mHwnd = hWnd;
	hDC = GetDC ( mHwnd );
	Stage_num = 0;

	g_hinst = hInst_temp;
	input::Initialize ( );
	Time::Initailize ( );
	SoundManager::getInstance().Init ( );
	
	HandleResize ( );
	Initrt.right = rt.right;
	Initrt.bottom = rt.bottom;
	GameManager::getInstance().Game_Initialize ( hDC , g_hinst );

	//임시 음악
	if ( GameManager::getInstance ( ).Return_SceneStatus () == 1) {

	}
	
	/*PlaySound ( MAKEINTRESOURCE ( IDR_WAVE1 ) , g_hinst , SND_RESOURCE | SND_ASYNC | SND_LOOP );
	PlaySound ( MAKEINTRESOURCE ( IDR_WAVE2 ) , g_hinst , SND_RESOURCE | SND_ASYNC | SND_LOOP );
	PlaySound ( MAKEINTRESOURCE ( IDR_WAVE3 ) , g_hinst , SND_RESOURCE | SND_ASYNC | SND_LOOP );
	PlaySound ( MAKEINTRESOURCE ( IDR_WAVE4 ) , g_hinst , SND_RESOURCE | SND_ASYNC | SND_LOOP );*/
	GameDC = CreateCompatibleDC ( hDC );
	mBitmap = CreateCompatibleBitmap ( hDC , 1024 * 2 , 1024 * 2 );
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



	GameManager::getInstance ( ).Render ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , mDC );
	

	Time::Render ( mDC );
	if ( Initrt.right == rt.right && rt.bottom== Initrt.bottom ) {
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		//std::cerr << rt.left << " " << rt.top << " " << rt.right << rt.bottom <<" 1" << std::endl;
	}
	else {
		StretchBlt ( hDC , 0 , 0 , rt.right , rt.bottom , mDC , 0 , 0 , 1680 , 1024 - 30 , SRCCOPY );
		//( 1024 * 2 ) - 390
		//std::cerr << rt.left << " " << rt.top << " " << rt.right << rt.bottom <<" 2" << std::endl;
	}
	
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
	
	mBackBitmap = CreateCompatibleBitmap ( hDC , 1680 , 1050 );	//rt.right rt.bottom

	
}

void Application::f_Run() {

	f_Update();
	f_FixedUpdate();
	f_Render();

}

