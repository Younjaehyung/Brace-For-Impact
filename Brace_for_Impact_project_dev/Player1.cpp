#include "Player1.h"

Player1::Player1() {
	rect = { 0,0,10,10 };
}

void Player1::f_Update() {
	if (count == 100) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			OffsetRect(&rect, 0, -5);
			count = 0;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			OffsetRect(&rect, -5, 0);
			count = 0;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			OffsetRect(&rect, 0, 5);
			count = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			OffsetRect(&rect, 5, 0);
			count = 0;
		}
		
	}
	if (count < 100) {
		count++;
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