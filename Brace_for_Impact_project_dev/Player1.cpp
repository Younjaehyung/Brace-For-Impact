#include "Player1.h"
#define PLAYERSIZE 96


Player1::Player1() {
	rect = { 0,0,40,40 };
	count = 0;
}

void Player1::Update ( ) {
	SwitchStatus ( );
	move ( );

}

void Player1::move ( ) {
	if ( TankController::TankMoveStatus ( ) ) {
		return;
	}

	float speed = 200 * Time::DeltaTime ( );

	if ( input::GetKey ( eKeyCode::W ) && rect.top > 0) { //  rect.top > 0
		rect.top -= speed;
		rect.bottom -= speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame ++;
			if ( frame >= 5 ) frame = 0;
		}
		count+= Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::A ) && rect.left > 0) { // rect.left > 0
		rect.left -= speed;
		rect.right -= speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame ++;
			if ( frame >= 5 ) frame = 0;
			direct = 0;
		}
		count += Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::S ) && rect.bottom <900) { // rect.bottom < 900
		rect.top += speed;
		rect.bottom += speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame ++;
			if ( frame >= 5 ) frame = 0;
		}
		count += Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::D ) && rect.right <600) { // rect.right <600
		rect.left += speed;
		rect.right += speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame ++;
			if ( frame >= 5 ) frame = 0;
			direct = 1;
		}
		count += Time::DeltaTime ( );

	}
	//플레이어1 충돌 범위

	if ( input::GetKeyUp ( eKeyCode::W ) || input::GetKeyUp ( eKeyCode::A ) || input::GetKeyUp ( eKeyCode::S ) || input::GetKeyUp ( eKeyCode::D ) ) {
		frame = 0;
	}

}

void Player1::SwitchStatus ( ) {
	if ( input::GetKeyUp ( eKeyCode::p1_a ) ) {
		TankController::TankMoveStatus ( )= !TankController::TankMoveStatus ( );
		direct = 2;
	}
}

void Player1 :: Tank_control ( ) {

}

void Player1::FixedUpdate ( ) {
	p1Rect = { 1024 + rect.left , 0 + rect.top , 1024 + rect.left + PLAYERSIZE , 0 + rect.top + PLAYERSIZE };
}
void Player1::Render ( const HDC& mDC ) {

	
	//플레이어1
	
	TransparentBlt ( mDC , 1024 + rect.left,  0+ rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_1" ) , frame * 64, direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	//Rectangle ( mDC , p1Rect.left , p1Rect.top , p1Rect.right, p1Rect.bottom );
	//좌표 알아보기 용
	wchar_t str1[ 50 ] = L"";
	wchar_t str2[ 50 ] = L"";
	wsprintf ( str1 , L"X : %d" , (int)rect.left );
	wsprintf ( str2, L"Y : %d" , ( int ) rect.top );
	int len1 = wcsnlen_s ( str1 , 50 );
	int len2 = wcsnlen_s ( str2 , 50 );
	TextOut ( mDC , 100 , 200 , str1 , len1 );
	TextOut ( mDC , 100 , 300 , str2 , len2 );
}
RECTS Player1::ReturnRect ( ) {
	return rect;
}





Player2::Player2() {
	rect = { 40,40,80,80 };
	count = 0;
}

void Player2::Init ( HINSTANCE g_hinst ) {
	//B_Player_2 = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) );	//youn
}

void Player2::Update() {
	SwitchStatus ( );
	move ( );

}
void Player2::move ( ) {

	if ( TankController::TankAimingStatus ( ) ) {
		return;
	}
	float speed = 200 * Time::DeltaTime ( );
	if ( input::GetKey ( eKeyCode::UP ) && rect.top>-200 ) { //rect.top > -200
		rect.top -= speed;
		rect.bottom -= speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame ++;
			if ( frame >= 5 ) frame = 0;
		}
		count += Time::DeltaTime ( );

	}
	if ( input::GetKey ( eKeyCode::LEFT ) && rect.left>0 ) { // rect.left > 0
		rect.left -= speed;
		rect.right -= speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame ++;
			if ( frame >= 5 ) frame = 0;
			direct = 0;
		}
		count += Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::DOWN ) && rect.bottom<700 ) { // rect.bottom < 700
		rect.top += speed;
		rect.bottom += speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame ++;
			if ( frame >= 5 ) frame = 0;
		}
		count += Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::RIGHT ) && rect.right < 600) { // rect.right < 600
		rect.left += speed;
		rect.right += speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame ++;
			if ( frame >= 5 ) frame = 0;
			direct = 1;
		}
		count += Time::DeltaTime ( );
	}

	if ( input::GetKeyUp ( eKeyCode::UP ) || input::GetKeyUp ( eKeyCode::RIGHT ) || input::GetKeyUp ( eKeyCode::LEFT ) || input::GetKeyUp ( eKeyCode::DOWN ) ) {
		frame = 0;
	}
}
void Player2::SwitchStatus ( ) {
	if ( input::GetKeyUp ( eKeyCode::p2_a ) ) {
		TankController::TankAimingStatus ( ) = !TankController::TankAimingStatus ( );
		direct = 2;
	}
}

void Player2::FixedUpdate() {
}
void Player2::Render ( const HDC& mDC ) {
	//플레이어2
	
	TransparentBlt ( mDC , 1024 + rect.left,  200 +rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_2" ) , frame * 64 , 64*4 + direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

}
RECTS Player2::ReturnRect() {
	return rect;
}