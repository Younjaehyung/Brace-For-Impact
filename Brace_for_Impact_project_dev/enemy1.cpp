#include "enemy1.h"
#include "MATH.h"
#include <random>

int LEN = 200;

std::random_device rd;
std::mt19937 gen;
std::uniform_int_distribution<int> sponse(0, 800);

enemy1::enemy1() {
	

}
void enemy1::f_init(int tp){
	rect.left = sponse(gen);
	rect.top = sponse(gen);
	rect.right = rect.left + 40;
	rect.bottom = rect.top + 40;
	type = tp;
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
	if (type == 1) {
		if (count%5 == 0) {
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
	}
	else if (type == 2) {
		if (count%5 == 0) {

			if (length(player.f_ReturnRect().left, player.f_ReturnRect().top, rect.left, rect.top) > LEN) {
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

