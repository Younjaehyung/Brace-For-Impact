#include "Game.h"

void Game::Camera_UI (const HDC& mDC )
{
	TransparentBlt ( mDC , 0 , 0 , 1024 , 768 ,
	Texture::getInstance ( ).Texture_GetDC ( "B_UI_Stage" ) , TankController::TankStage_frame ( ).frame * 1024 , 0 , 1024 , 768 , RGB ( 255 , 255 , 255 ) );


	//스테이지 UI는 tank.cpp로 이동됬음. 탱크 움직임에 맞춰서 변해야 하기 때문에.
	TransparentBlt ( mDC , 0 , 768 , 1024 , 225 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Info" ) , 0 , 0 , 1024 , 252 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 0 , 640 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Player" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 760 , 640 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Player" ) , 0 , 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	//==탱크 체력
	SelectObject ( mDC , redBrush );
	Rectangle ( mDC , 90 , 780 , 90 +TankController::TankHp() , 780 + 64 );	//정보 UI
	TransparentBlt ( mDC , 0 , 780 , 500 , 64 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_UI_Status" ) , 0 , 0 , 575 , 64 , RGB ( 255 , 255 , 255 ) );

	SelectObject ( mDC , blackBrush );
	Rectangle ( mDC , 90 , 880 , 90 +TankController::TankOil() , 880 + 64 );	//정보 UI
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

	TransparentBlt ( mDC , 1024 + 270 , 0 + 500 , 96 , 160 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Engine" ) , 0 , 0 , 96 , 160 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 100 , 0 + 730 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Steam" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 450 , 0 + 730 , 128 , 128 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_CT_Dash" ) , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 200 , 0 - 30 , 240 , 512 ,
	Texture::getInstance ( ).Texture_GetDC ( "B_CT_Cannon" ) , TankController::TankCannon_frame().frame * 240 , 0 , 240 , 512 , RGB ( 255 , 255 , 255 ) );
}
