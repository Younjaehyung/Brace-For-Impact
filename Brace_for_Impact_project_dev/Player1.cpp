#include "Player1.h"

void Player1::Init ( HINSTANCE g_hinst ) {
	B_Player_1 = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) );
}

Player1::Player1() {
	rect = { 0,0,40,40 };
}

void Player1::Update ( ) {
	
	move ( );

}

void Player1::move ( ) {
	float speed = 200 * Time::DeltaTime ( );

	if ( input::GetKey ( eKeyCode::W ) ) {
		rect.top -= speed;
		rect.bottom -= speed;
		frame += 32;
		if ( frame >= 128 ) frame = 0;
		
	}
	if ( input::GetKey ( eKeyCode::A ) ) {
		rect.left -= speed;
		rect.right -= speed;
		frame += 32;
		if ( frame >= 128 ) frame = 0;
		direct = 0;
	}
	if ( input::GetKey ( eKeyCode::S ) ) {
		rect.top += speed;
		rect.bottom += speed;
		frame += 32;
		if ( frame >= 128 ) frame = 0;
	}
	if ( input::GetKey ( eKeyCode::D ) ) {
		rect.left += speed;
		rect.right += speed;
		frame += 32;
		if ( frame >= 128 ) frame = 0;
		direct = 1;

	}
}

void Player1::FixedUpdate ( ) {
}
void Player1::Render (HDC hmemDC , HDC mDC ) {

	Rectangle ( mDC , rect.left, rect.top, rect.right , rect.bottom );
	//플레이어1
	SelectObject ( hmemDC , ( HBITMAP ) B_Player_1 );
	TransparentBlt ( mDC , rect.left, rect.top, 128 , 128 , hmemDC , frame , direct * 32 , 32 , 32 , RGB ( 255 , 255 , 255 ) );


}
RECTS Player1::ReturnRect ( ) {
	return rect;
}





Player2::Player2() {
	rect = { 40,40,80,80 };
}

void Player2::Init ( HINSTANCE g_hinst ) {
	B_Player_2 = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) );
}

void Player2::Update() {
	float speed = 200 * Time::DeltaTime ( );
	if ( input::GetKey ( eKeyCode::UP ) ) {
		rect.top -= speed;
		rect.bottom -= speed;
		frame += 32;
		if ( frame >= 128 ) frame = 0;

	}
	if ( input::GetKey ( eKeyCode::LEFT ) ) {
		rect.left -= speed;
		rect.right -= speed;
		frame += 32;
		if ( frame >= 128 ) frame = 0;
		direct = 0;
	}
	if ( input::GetKey ( eKeyCode::DOWN ) ) {
		rect.top += speed;
		rect.bottom += speed;
		frame += 32;
		if ( frame >= 128 ) frame = 0;
	}
	if ( input::GetKey ( eKeyCode::RIGHT ) ) {
		rect.left += speed;
		rect.right += speed;
		frame += 32;
		if ( frame >= 128 ) frame = 0;
		direct = 1;

	}
}


void Player2::FixedUpdate() {
}
void Player2::Render ( HDC hmemDC , HDC mDC ) {
	//플레이어2
	SelectObject ( hmemDC , ( HBITMAP ) B_Player_2 );
	TransparentBlt ( mDC , rect.left, rect.top, 128 , 128 , hmemDC , frame , 64 + direct * 32 , 32 , 32 , RGB ( 255 , 255 , 255 ) );

	Rectangle(mDC, rect.left, rect.top, rect.right, rect.bottom);
}
RECTS Player2::ReturnRect() {
	return rect;
}