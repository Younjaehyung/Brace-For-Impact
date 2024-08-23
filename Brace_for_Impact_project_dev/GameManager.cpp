#include "GameManager.h"

void GameManager::Camera_UI_Ground ( const HDC& mDC )
{
	TransparentBlt ( mDC , 0 , 0 , 1024 , 768 ,
	Texture::getInstance ( ).Texture_GetDC ( "B_UI_Stage" ) , TankController::TankStage_frame ( ).frame * 1024 , 0 , 1024 , 768 , RGB ( 255 , 255 , 255 ) );

	if ( engineCount >= 0.1 ) {
		engineCount = 0;
		engineframe++;
		if ( engineframe >= 5 ) {
			engineframe = 0;
		}
	}

	engineCount += Time::DeltaTime ( );


	//상호작용 범위
	//이동 조작기
	//Rectangle ( mDC , 1024 + 16 * 8 , 16 * 9 , 1024 + 16 * 16 , 16 * 18 );
	//공격 조작기
	//Rectangle ( mDC , 1024 + 16 * 26 , 16 * 9 , 1024 + 16 * 34 , 16 * 18 );
	//플레이어 이동 불가구역(대포)
	//Rectangle ( mDC , 1024 + 16 * 16 , 16 * 9 , 1024 + 16 * 26 , 16 * 30 );
	//장전 가능 구역
	//Rectangle ( mDC , 1024 + 16 * 16 , 16 * 28 , 1024 + 16 * 26 , 16 * 35 );

	//연료 충전 구역
	//Rectangle ( mDC , 1024 + 16 * 16 , 16 * 46 , 1024 + 16 * 26 , 16 * 54 );

	//대쉬 가능 구역
	//Rectangle ( mDC , 1024 + 16 * 8 , 16 * 46 , 1024 + 16 * 16 , 16 * 54 );
	//증기 분출 가능 구역
	//Rectangle ( mDC , 1024 + 16 * 26 , 16 * 46 , 1024 + 16 * 34 , 16 * 54 );
	//연료 저장고
	//Rectangle ( mDC , 1024 + 16 * 8 , 16 * 34 , 1024 + 16 * 15 , 16 * 40 );
	//탄약 저장고
	//Rectangle ( mDC , 1024 + 16 * 26 , 16 * 34 , 1024 + 16 * 34 , 16 * 40 );

	//스테이지 UI는 tank.cpp로 이동됬음. 탱크 움직임에 맞춰서 변해야 하기 때문에.
	TransparentBlt ( mDC , 0 , 768 , 1024 , 225 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Info" ) , 0 , 0 , 1024 , 252 , RGB ( 255 , 255 , 255 ) );
	/*TransparentBlt ( mDC , 0 , 640 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Player" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 760 , 640 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Player" ) , 0 , 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );*/
	//==탱크 체력
	SelectObject ( mDC , redBrush );
	Rectangle ( mDC , 90 , 780 , 90 + TankController::TankHp ( ) , 780 + 64 );	//정보 UI
	TransparentBlt ( mDC , 0 , 780 , 500 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Status" ) , 0 , 0 , 575 , 64 , RGB ( 255 , 255 , 255 ) );

	SelectObject ( mDC , cyanBrush );
	Rectangle ( mDC , 90 , 880 , 90 + TankController::TankOil ( ) , 880 + 64 );	//정보 UI
	//==탱크 연료
	TransparentBlt ( mDC , 0 , 880 , 500 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Status" ) , 0 , 0 , 575 , 64 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 900 , 780 , 96 , 192 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Cooltime" ) , 96 * 2 , 0 , 96 , 192 , RGB ( 255 , 255 , 255 ) );

	//총알 개수 리로드
	TransparentBlt ( mDC , 500 , 780 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" )
			, 192 * 4 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 500 , 880 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" )
			, 192 * 4 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 700 , 780 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" )
			, 192 * 4 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 700 , 880 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" )
			, 192 * 4 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );
	switch ( TankController::TankBullet ( ) ) {
	case 4:
		TransparentBlt ( mDC , 700 , 880 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" )
			, 192 * 0 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );

	case 3:
		TransparentBlt ( mDC , 700 , 780 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" )
			, 192 * 0 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );

	case 2:
		TransparentBlt ( mDC , 500 , 880 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" )
			, 192 * 0 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );

	case 1:
		TransparentBlt ( mDC , 500 , 780 , 192 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Reloader" )
			, 192 * 0 , 0 , 192 , 64 , RGB ( 255 , 255 , 255 ) );
		break;
	}
	
}


void GameManager::Camera_UI_CT_1( const HDC& mDC )
{
	TransparentBlt ( mDC , 1024 + 120 , 0 + 80 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Move" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 400 , 0 + 80 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Attack" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );

	TransparentBlt ( mDC , 1024 + 200 , 0 - 30 , 240 , 512 ,
	Texture::getInstance ( ).Texture_GetDC ( "B_CT_Cannon" ) , TankController::TankCannon_frame ( ).frame * 240 , 0 , 240 , 512 , RGB ( 255 , 255 , 255 ) );
	
	TransparentBlt ( mDC , 1024 + 16 * 4 , 0 + 16 * 33 , 128 , 128 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_CT_Itembox" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 16 * 29 , 0 + 16 * 33 , 128 , 128 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_CT_Itembox" ) , 128 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );

}

void GameManager::Camera_UI_CT_2 ( const HDC& mDC )
{
	TransparentBlt ( mDC , 1024 + 16 * 18 , 0 + 16 * 45 , 96 , 160 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_CT_Engine" ) , engineframe * 96 , 0 , 96 , 160 , RGB ( 255 , 255 , 255 ) );
	//대쉬
	TransparentBlt ( mDC , 1024 + 16 * 6 , 0 + 16 * 46 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Steam_Dash" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	//스팀
	TransparentBlt ( mDC , 1024 + 16 * 27 , 0 + 16 * 46 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Steam_Dash" ) , 128 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );

}


void GameManager::Ground_Map ( const HDC& mDC )
{
	if ( SceneStatus == 1 || SceneStatus ==2 )
	{
		StretchBlt ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 0 , 0 , 1024 * 2 , 1024 * 2 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 , 0 , 1024 , 1024 , SRCCOPY );

	}
	else if ( SceneStatus == 3 || SceneStatus == 4 ) {
		StretchBlt ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 0 , 0 , 1024 * 2 , 1024 * 2 ,
	Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_1" ) , 0 , 0 , 1024 , 1024 , SRCCOPY );

		
	}
	else if( SceneStatus == 5 || SceneStatus==6 ){
		
		StretchBlt ( Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 0 , 0 , 1024 * 2 , 1024 * 2 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_3" ) , 0 , 0 , 1024 , 1024 , SRCCOPY );
	

	}
}

void GameManager::Camera_Cal ( const HDC& mDC ) {
	
	if ( PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).left + 512 >= 2048 ) {
		TankController::camera.left = 512 * 2;
	}
	else {
		TankController::camera.left = max ( 0 , PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).left - 512 );
	}
	
	if ( PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).top + 384 >= 2048 ) {
		TankController::camera.top = 2048 -(384*2);
	
	}
	else {
		TankController::camera.top = max ( 0 , PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( ).top - 384 );
	}
	TankController::camera.right = TankController::camera.left + 1024;
	TankController::camera.bottom = TankController::camera.top + 768;
	
}

void GameManager::Camera ( const HDC& mDC ) {
	BitBlt ( mDC , 0 , 0 , 1024 , 768 , Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , TankController::camera.left , TankController::camera.top , SRCCOPY );

}

void GameManager::Tank_Inside ( const HDC& mDC ) {

	BitBlt ( mDC , r_playground.left , r_playground.top , 656 , 1024 - 50 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Inside" ) , 0 , 0 , SRCCOPY );

}


void GameManager::TitleScene ( const HDC& mDC ) {	//0



	if ( count >= 0.4 ) {
		count = 0;
		frame++;
		if ( frame >= 5 ) {
			frame = 0;
		}
	}

	count += Time::DeltaTime ( );


	//TITLE 출력
	BitBlt ( mDC , 0 , 0 , 1024 , 1024 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_TITLE" ) , frame * 1024 , 0 , SRCCOPY );
	BitBlt ( mDC , 1024 - 50 , 0 , 1024 + 656 , 1024 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Select" ) , 0 , 0 , SRCCOPY );
	TransparentBlt ( mDC , 1024 + 8 + 16 * 1 , 32 * ( 9 + Cursor ) , 96 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Cursor" ) , 0 , 0 , 96 , 64 , RGB ( 255 , 255 , 255 ) );

	TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * ( 9 ) , 384 , 96 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 0 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * 13 , 384 , 96 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 384 * 1 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * 17 , 384 , 96 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 384 * 2 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 16 * 9 + 8 , 32 * ( 9 + Cursor ) + 16 , 64 , 64 ,
	Texture::getInstance ( ).Texture_GetDC ( "B_Item" ) , 0 , 64 * 3 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	MenuUpdate ( );

	

	if ( Rule ) {
		TransparentBlt ( mDC , 0 , -8 , 1024 , 1024 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Rule" ) , 0 , 0 , 1024 , 1024 , RGB ( 255 , 255 , 255 ) );

	}
}

void GameManager::EndScene ( const HDC& mDC ) {//2

	
	if ( endcount >= 0.1 ) {
		endcount = 0;
		endframe++;
		if ( endframe >= 6 ) {
			endframe = 0;
		}
	}	endcount += Time::DeltaTime ( );

	TransparentBlt ( mDC , 128 * 5 + 64 , 256 , 288 , 480 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Over" ) , 0 , 0 , 288 , 480 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 128 * 4 , 128 * 5 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_1" ) , endframe * 128 , 128 * 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 128 * 8 , 128 * 5 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_1" ) , endframe * 128 , 128 * 3 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 128 * 6 , 128 * 6 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Item" ) , 
		0 , 64 * 3 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	if ( input::GetKeyDown ( eKeyCode::F ) ) {
		Clear ( );
		Initialize ( );
	}

}

void GameManager::ClearScene ( const HDC& mDC ) {//2


	TransparentBlt ( mDC , 128 * 5 + 64 , 256 , 320 , 320 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Clear" ) , 0 , 0 ,320 , 320 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 128 * 8 , 128 * 5 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Player_2" ) , 0 , 64 * 2 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 128 * 4 , 128 * 5 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Player_1" ) , 0 , 64 * 7 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	if ( input::GetKeyDown ( eKeyCode::F ) ) {
		Clear ( );
		Initialize ( );
	}

}

void GameManager::Stage_Switch_Render ( const HDC& mDC, const HDC& orimDC ) {
	
	BitBlt ( orimDC , 0 , 0 , 1024 , 768 , Texture::getInstance ( ).Texture_GetDC ( "GAME_FIELD" ) , 4*Stage_Switch_x , 2*Stage_Switch_y , SRCCOPY );

	TransparentBlt ( orimDC , 0 , 758 - 2*Stage_Switch_y , 1024 , 384 ,
	Texture::getInstance ( ).Texture_GetDC ( "B_Start" ) , 1024 * BossSceneR , 384 * BossSceneC , 1024 , 384 , RGB ( 255 , 255 , 255 ) );

	
}