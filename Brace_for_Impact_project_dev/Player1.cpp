#include "Player1.h"


Player1::Player1() {
	rect = { 0,0,40,40 };
}

void Player1::f_Update ( ) {
	float speed = 1200 * Time::DeltaTime ( );
	if ( input::GetKey ( eKeyCode::W ) ) {
		rect.top -= speed;
		rect.bottom -= speed;
		count = 0;
	}
	if ( input::GetKey ( eKeyCode::A ) ) {
		rect.left -= speed;
		rect.right -= speed;
		count = 0;
	}
	if ( input::GetKey ( eKeyCode::S ) ) {
		rect.top += speed;
		rect.bottom += speed;
		count = 0;
	}
	if ( input::GetKey ( eKeyCode::D ) ) {
		rect.left += speed;
		rect.right += speed;
		count = 0;
	}


}


void Player1::f_FixedUpdate ( ) {
}
void Player1::f_Render ( HDC mDC ) {

	Rectangle ( mDC , rect.left , rect.top , rect.right , rect.bottom );
}
RECTS Player1::f_ReturnRect ( ) {
	return rect;
}




Player2::Player2() {
	rect = { 40,40,80,80 };
}

void Player2::f_Update() {
	float speed = 1200 * Time::DeltaTime ( );
	if (input::GetKey(eKeyCode::UP)) {
		rect.top -= speed;
		rect.bottom -= speed;
	
	}
	if (input::GetKey(eKeyCode::LEFT)) {
		rect.left -= speed;
		rect.right -= speed;
	
	}
	if (input::GetKey(eKeyCode::DOWN)) {
		rect.top += speed;
		rect.bottom += speed;
		
	}
	if (input::GetKey(eKeyCode::RIGHT)) {
		rect.left += speed;
		rect.right += speed;
		
	}


}


void Player2::f_FixedUpdate() {
}
void Player2::f_Render(HDC mDC) {

	Rectangle(mDC, rect.left, rect.top, rect.right, rect.bottom);
}
RECTS Player2::f_ReturnRect() {
	return rect;
}