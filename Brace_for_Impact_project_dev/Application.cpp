#include "Application.h"


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
	Stage_num = 0;

	g_hinst = hInst_temp;
	input::Initialize ( );
	Time::Initailize ( );
	HandleResize ( );
	gameobject.Initailize ( hDC,g_hinst );
	//임시 음악
	//PlaySound ( MAKEINTRESOURCE ( IDR_WAVE1 ) , g_hinst , SND_RESOURCE | SND_ASYNC | SND_LOOP );
	
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

	switch ( Stage_num ) {
	case 0:
		StretchBlt ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 0 , 0 , 1024 * 2 , 1024 * 2 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 , 0 , 1024 , 1024 , SRCCOPY );
		break;
	case 1:
		StretchBlt ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 0 , 0 , 1024 * 2 , 1024 * 2 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_3" ) , 0 , 0 , 1024 , 1024 , SRCCOPY );
		break;
	case 2:
		StretchBlt ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 0 , 0 , 1024 * 2 , 1024 * 2 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_1" ) , 0 , 0 , 1024 , 1024 , SRCCOPY );
		break;
	case 3:
		
		break;

	}


	if ( input::GetKey ( eKeyCode::I ) ) {
		Stage_num = 0;
	}
	else if ( input::GetKey ( eKeyCode::O ) ) {
		Stage_num = 1;
	}
	else if ( input::GetKey ( eKeyCode::P ) ) {
		Stage_num = 2;
	}
	else if ( input::GetKey ( eKeyCode::U ) ) {
		Stage_num = 3;
	}
	else if ( input::GetKeyUp ( eKeyCode::Z ) ) {
		gameStart = !gameStart;
	}
	BitBlt ( mDC , r_playground.left , r_playground.top , 656 , 1024 - 50 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Inside" ) , 0 , 0 , SRCCOPY );

	//OSW - hmemDC추가

	
	if ( PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).left + 512 >= 2048 ) {
		TankController::camera.left = 512 * 2;
	}
	else {
		TankController::camera.left = max ( 0 , PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).left - 512 );
	}
	
	if ( PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).top + 384 >= 2048 ) {
		TankController::camera.top = PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).top-384;
	
	}
	else {
		TankController::camera.top = max ( 0 , PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).top - 384 );
	}
	TankController::camera.right = TankController::camera.left + 1024;
	TankController::camera.bottom = TankController::camera.top + 768;
	gameobject.Render ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ),mDC );
	

	//StretchBlt ( mDC , 0 , 0 , 1024 , 780, Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , left , top , 1024 , 960 , SRCCOPY );
	BitBlt ( mDC , 0 , 0 , 1024 , 768 , Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , TankController::camera.left , TankController::camera.top , SRCCOPY );



	/*TransparentBlt ( mDC , r_playground.left , r_playground.top , 656 , 1024-50 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Inside" ) , 0 , 0 , 656 , 1024 , RGB ( 255 , 255 , 255 ) );
	*/
	
gameobject.Camera_UI ( mDC );

	if ( gameStatus == 0) {
		//TITLE 출력
		BitBlt ( mDC , 0 , 0 , 1024 , 1024 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_TITLE" ) , TankController::ScreenTitle_frame ( ).frame * 1024 , 0 , SRCCOPY );
		BitBlt ( mDC , 1024 - 50 , 0 , 1024 + 656 , 1024 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Select" ) , 0 , 0 , SRCCOPY );
		TransparentBlt ( mDC , 1024 + 8 + 16*1 , 32 * (9 + Cursor) ,96 , 64 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Cursor" ) ,0 , 0 , 96 , 64 , RGB ( 255 , 255 , 255 ) );
		TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * ( 9) , 384 , 96 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 0 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
		TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * 13 , 384 , 96 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 384 * 1 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
		TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * 17 , 384 , 96 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 384*2 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
		
		if ( input::GetKeyDown ( eKeyCode::S ) ) {
			if(Cursor < 11 )
			Cursor +=4;
		}
		else if ( input::GetKeyDown ( eKeyCode::W ) ) {
			if(Cursor > 0 )
			Cursor -=4;
		}

		//게임 시작 창일때
		if ( input::GetKeyDown ( eKeyCode::F ) && Cursor == 0) {
			gameStatus = 10;
		}else if (input::GetKeyDown ( eKeyCode::F ) && Cursor == 4) {
			gameStatus = 1;
		} else if (input::GetKeyDown ( eKeyCode::F ) && Cursor == 8) {
			gameStatus = 2;
		}
	}
	else if ( gameStatus == 1 ) {
		BitBlt ( mDC , 0 , 0 , 1024 , 1024 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_TITLE" ) , TankController::ScreenTitle_frame ( ).frame * 1024 , 0 , SRCCOPY );
		BitBlt ( mDC , 1024 - 50 , 0 , 1024 + 656 , 1024 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Select" ) , 0 , 0 , SRCCOPY );
		TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * ( 9) , 384 , 96 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 0 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
		TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * 13 , 384 , 96 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 384 * 1 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
		TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * 17 , 384 , 96 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 384*2 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
		
		TransparentBlt ( mDC , 0, 0 , 1024 , 768 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Rule" ), 0,0,1024 , 768 ,RGB(255,255,255) );
		if ( input::GetKeyDown ( eKeyCode::F )) {
			gameStatus = 0;
		}
	}

	else if ( gameStatus == 2 ) {

		Rectangle ( mDC , 0 , 0 , rt.right , rt.bottom );
		TransparentBlt ( mDC , 128*5 , 256 , 320 , 320 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Clear" ) , 0 , 0 , 320 , 320 , RGB ( 255 , 255 , 255 ) );
		TransparentBlt ( mDC , 128 * 8 , 128*5 , PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_2" ) , 0 ,64 * 2 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
		TransparentBlt ( mDC , 128 * 4 , 128*5 , PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_1" ) , 0 , 64 * 7 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
		if ( input::GetKeyDown ( eKeyCode::F ) ) {
			gameStatus = 0;
		}
	}

	
	//플레이어 활동 가능 구역
	//Rectangle ( mDC , 1024 + 16*6 , 0 + 16*9 , 1024 + 16*35 , 0 + 100 + 16*50 );

	// 
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

