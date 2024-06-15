#include "Menu.h"


void TitleScene (HDC mDC) {	//0



	if ( gameStatus == 0 ) {
		//TITLE 출력
		BitBlt ( mDC , 0 , 0 , 1024 , 1024 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_TITLE" ) , TankController::ScreenTitle_frame ( ).frame * 1024 , 0 , SRCCOPY );
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

		if ( input::GetKeyDown ( eKeyCode::S ) ) {
			if ( Cursor < 11 )
				Cursor += 4;
		}
		else if ( input::GetKeyDown ( eKeyCode::W ) ) {
			if ( Cursor > 0 )
				Cursor -= 4;
		}

		//게임 시작 창일때
		if ( input::GetKeyDown ( eKeyCode::F ) && Cursor == 0 ) {
			gameStatus = 10;
		}
		else if ( input::GetKeyDown ( eKeyCode::F ) && Cursor == 4 ) {
			gameStatus = 1;
		}
		else if ( input::GetKeyDown ( eKeyCode::F ) && Cursor == 8 ) {
			gameStatus = 2;
		}
	}
}
void RuleScene ( HDC mDC ) {	//1

	BitBlt ( mDC , 0 , 0 , 1024 , 1024 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_TITLE" ) , TankController::ScreenTitle_frame ( ).frame * 1024 , 0 , SRCCOPY );
	BitBlt ( mDC , 1024 - 50 , 0 , 1024 + 656 , 1024 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Select" ) , 0 , 0 , SRCCOPY );
	TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * ( 9 ) , 384 , 96 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 0 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * 13 , 384 , 96 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 384 * 1 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 1024 + 8 + 16 * 8 , 32 * 17 , 384 , 96 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Selectframe" ) , 384 * 2 , 0 , 384 , 96 , RGB ( 255 , 255 , 255 ) );

	TransparentBlt ( mDC , 0 , 0 , 1024 , 768 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Rule" ) , 0 , 0 , 1024 , 768 , RGB ( 255 , 255 , 255 ) );
	if ( input::GetKeyDown ( eKeyCode::F ) ) {
		gameStatus = 0;
	}

}
void ENDScene ( HDC mDC ) {//2

	Rectangle ( mDC , 0 , 0 , rt.right , rt.bottom );
	TransparentBlt ( mDC , 128 * 5 , 256 , 320 , 320 ,
		Texture::getInstance ( ).Texture_GetDC ( "B_Clear" ) , 0 , 0 , 320 , 320 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 128 * 8 , 128 * 5 , PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_2" ) , 0 , 64 * 2 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	TransparentBlt ( mDC , 128 * 4 , 128 * 5 , PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_1" ) , 0 , 64 * 7 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	if ( input::GetKeyDown ( eKeyCode::F ) ) {
		gameStatus = 0;
	}

}