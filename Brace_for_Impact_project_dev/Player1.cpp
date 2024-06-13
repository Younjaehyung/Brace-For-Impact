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
	
	//플레이어가 아이템을 들었을 때 출력 할 아이템 이미지
	TransparentBlt ( mDC , 1024 + rect.left + 32, 0 + rect.top - 32 , PLAYERSIZE /2 , PLAYERSIZE /2 , Texture::getInstance ( ).Texture_GetDC ( "B_Item" ) , frame * 64 , direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
}
RECTS Player1::ReturnRect ( ) {
	return rect;
}





Player2::Player2() {
	rect = { 0,0,40,40 };
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
	
	TransparentBlt ( mDC , 1024 + rect.left,  0 +rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_2" ) , frame * 64 , 64*4 + direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	//플레이어가 아이템을 들었을 때 출력 할 아이템 이미지
	TransparentBlt ( mDC , 1024 + rect.left + 32 , 0 + rect.top - 32 , PLAYERSIZE / 2 , PLAYERSIZE / 2 , Texture::getInstance ( ).Texture_GetDC ( "B_Item" ) , frame * 64 , direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

}
RECTS Player2::ReturnRect() {
	return rect;
}