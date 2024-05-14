#include "Player1.h"


Player1::Player1() {
	rect = { 0,0,40,40 };
}

Player2::Player2() {
	rect = { 40,40,80,80 };
}

void Player2::f_Update() {

	if (input::GetKey(eKeyCode::UP)) {
		OffsetRect(&rect, 0, -1);
		count = 0;
	}
	if (input::GetKey(eKeyCode::LEFT)) {
		OffsetRect(&rect, -1, 0);
		count = 0;
	}
	if (input::GetKey(eKeyCode::DOWN)) {
		OffsetRect(&rect, 0, 1);
		count = 0;
	}
	if (input::GetKey(eKeyCode::RIGHT)) {
		OffsetRect(&rect, 1, 0);
		count = 0;
	}


}


void Player1::f_Update() {
	
		if (input::GetKey(eKeyCode::W)) {
			OffsetRect(&rect, 0, -1);
			count = 0;
		}
		if (input::GetKey(eKeyCode::A)) {
			OffsetRect(&rect, -1, 0);
			count = 0;
		}
		if (input::GetKey(eKeyCode::S)) {
			OffsetRect(&rect, 0, 1);
			count = 0;
		}
		if (input::GetKey(eKeyCode::D)) {
			OffsetRect(&rect, 1, 0);
			count = 0;
		}
		

}
void Player1::f_FixedUpdate() {
}
void Player1::f_Render(HDC mDC) {
	
	Rectangle(mDC, rect.left, rect.top, rect.right, rect.bottom);
}
RECT Player1::f_ReturnRect() {
	return rect;
}

void Player2::f_FixedUpdate() {
}
void Player2::f_Render(HDC mDC) {

	Rectangle(mDC, rect.left, rect.top, rect.right, rect.bottom);
}
RECT Player2::f_ReturnRect() {
	return rect;
}