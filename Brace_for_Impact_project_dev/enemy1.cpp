#include "enemy1.h"
#include <random>

std::random_device rd;
std::mt19937 gen;
std::uniform_int_distribution<int> sponse(0, 800);

enemy1::enemy1() {
	

}
void enemy1::f_init(){
	rect.left = sponse(gen);
	rect.top = sponse(gen);
	rect.right = rect.left + 40;
	rect.bottom = rect.top + 40;
}

void enemy1::f_attack() {

}

void enemy1::f_crash(enemy1& otherenemy) {
	RECT temp;
	
	if (IntersectRect(&temp, &rect, &otherenemy.rect)) {
		if (rect.left < otherenemy.rect.left) {
			OffsetRect(&rect, -5, 0);
		}
		if (rect.right > otherenemy.rect.right) {
			OffsetRect(&rect, 5, 0);
		}
		if (rect.top < otherenemy.rect.top) {
			OffsetRect(&rect, 0, -5);
		}
		if (rect.bottom > otherenemy.rect.bottom) {
			OffsetRect(&rect, 0, 5);
		}
	}
}

void enemy1::f_moving(Player1& player) {
	if (count == 5) {
		if (player.f_ReturnRect().left < rect.left) {
			OffsetRect(&rect, -1, 0);
			count = 0;
		}

		if (player.f_ReturnRect().top < rect.top) {
			OffsetRect(&rect, 0, -1);
			count = 0;
		}

		if (player.f_ReturnRect().left > rect.left) {
			OffsetRect(&rect, 1, 0);
			count = 0;
		}

		if (player.f_ReturnRect().top > rect.top) {
			OffsetRect(&rect, 0, 1);
			count = 0;
		}
		
	}

		count++;
	
}

void  enemy1::f_Update(Player1& player1) {

	f_moving(player1);
	
	f_attack();

}
void  enemy1::f_FixedUpdate() {
}
void  enemy1::f_Render(HDC mDC) {

	Rectangle(mDC, rect.left, rect.top, rect.right, rect.bottom);
}