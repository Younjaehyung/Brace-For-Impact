#include "MONSTER.h"
#include "MATH.h"
#include <random>

int LEN = 200;
int MOPSIZE = 20;

std::random_device rd;
std::mt19937 gen;
std::uniform_int_distribution<int> sponse(0, 800);

mop::mop() {

}

void mop::spone(monster*& hd, int type){
	monster* newmop = new monster;
	newmop->x = sponse(gen);
	newmop->y = sponse(gen);
	newmop->hp = 100;
	newmop->type = type;
	newmop->cnt = 0;
	newmop->next = hd;
	hd = newmop;
}

void mop::move(monster*& hd , Player1 &p1) {
	float speed = 600 * Time::DeltaTime();
	for (monster* p = hd; p != NULL; p = p->next) {
		if (p->type == 1) {

			if (p1.f_ReturnRect().left < p->x) {
				p->x -= speed;

			}

			if (p1.f_ReturnRect().top < p->y) {
				p->y -= speed;

			}

			if (p1.f_ReturnRect().left > p->x) {
				p->x += speed;
				
			}

			if (p1.f_ReturnRect().top > p->y) {
				p->y += speed;

			}


		}
		else if (p->type == 2) {


			if (length(p1.f_ReturnRect().left, p1.f_ReturnRect().top, p->x ,p->y) > LEN) {

				if (p1.f_ReturnRect().left < p->x) {
					p->x -= speed;

				}

				if (p1.f_ReturnRect().top < p->y) {
					p->y -= speed;

				}

				if (p1.f_ReturnRect().left > p->x) {
					p->x += speed;

				}

				if (p1.f_ReturnRect().top > p->y) {
					p->y += speed;

				}
			}

		}
	}
}

void mop::rander(HDC dc, monster*& hd) {

	for (monster* p = hd; p != NULL; p = p->next) {
		Rectangle(dc, p->x - MOPSIZE, p->y - MOPSIZE, p->x + MOPSIZE, p->y + MOPSIZE);
	}
}
