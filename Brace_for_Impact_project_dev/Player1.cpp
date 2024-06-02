#include "Player1.h"
#define PLAYERSIZE 96


Player1::Player1() {
	rect = { 0,0,40,40 };
	count = 0;
}

void Player1::Update ( ) {
	
	move ( );

}

void Player1::move ( ) {
	float speed = 200 * Time::DeltaTime ( );

	if ( input::GetKey ( eKeyCode::W ) ) {
		rect.top -= speed;
		rect.bottom -= speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame += 32;
			if ( frame >= 128 ) frame = 0;
		}
		count+= Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::A ) ) {
		rect.left -= speed;
		rect.right -= speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame += 32;
			if ( frame >= 128 ) frame = 0;
			direct = 0;
		}
		count += Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::S ) ) {
		rect.top += speed;
		rect.bottom += speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame += 32;
			if ( frame >= 128 ) frame = 0;
		}
		count += Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::D ) ) {
		rect.left += speed;
		rect.right += speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame += 32;
			if ( frame >= 128 ) frame = 0;
			direct = 1;
		}
		count += Time::DeltaTime ( );

	}
}


void Player1::FixedUpdate ( ) {

}
void Player1::Render ( const HDC& mDC ) {

	
		//플레이어1

	TransparentBlt ( mDC , 1024 + rect.left,  300+ rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_1" ) , frame , direct * 32 , 32 , 32 , RGB ( 255 , 255 , 255 ) );


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
	float speed = 200 * Time::DeltaTime ( );
	if ( input::GetKey ( eKeyCode::UP ) ) {
		rect.top -= speed;
		rect.bottom -= speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame += 32;
			if ( frame >= 128 ) frame = 0;
		}
		count += Time::DeltaTime ( );

	}
	if ( input::GetKey ( eKeyCode::LEFT ) ) {
		rect.left -= speed;
		rect.right -= speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame += 32;
			if ( frame >= 128 ) frame = 0;
			direct = 0;
		}
		count += Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::DOWN ) ) {
		rect.top += speed;
		rect.bottom += speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame += 32;
			if ( frame >= 128 ) frame = 0;
		}
		count += Time::DeltaTime ( );
	}
	if ( input::GetKey ( eKeyCode::RIGHT ) ) {
		rect.left += speed;
		rect.right += speed;
		if ( count >= 0.1 ) {
			count = 0;
			frame += 32;
			if ( frame >= 128 ) frame = 0;
			direct = 1;
		}
		count += Time::DeltaTime ( );
	}
}



void Player2::FixedUpdate() {
}
void Player2::Render ( const HDC& mDC ) {
	//플레이어2
	
	TransparentBlt ( mDC , 1024 + rect.left,  200 +rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_2" ) , frame , 64 + direct * 32 , 32 , 32 , RGB ( 255 , 255 , 255 ) );

}
RECTS Player2::ReturnRect() {
	return rect;
}