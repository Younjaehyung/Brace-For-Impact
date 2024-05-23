#include "MONSTER.h"
#include "MATH.h"
#include <random>
#include "enemy1.h"

int MONSTERLEN = 200;
int MOPSIZE = 20;

std::random_device rdmop;
std::mt19937 genmop;
std::uniform_int_distribution<int> sponsemop(0, 800);

mop::mop() {

}

void mop::spone(monster*& hd, int type){
	monster* newmop = new monster;
	newmop->x = sponsemop(genmop);
	newmop->y = sponsemop(genmop);
	newmop->hp = 100;
	newmop->type = type;
	newmop->cnt = 0;
	newmop->next = hd;
	hd = newmop;
}

void mop::attack(monster*& mophd, bullet*& bullethd, Player1& p1) {

	for (monster* p = mophd; p != NULL; p = p->next) {
		if (p->type == 1) {

		}
		else if (p->type == 2) {
			p->cnt++;
			if (p->cnt > 100) {
				p->cnt = 0;
				bullet* newbullet = new bullet;
				newbullet->x = p->x;
				newbullet->y = p->y;
				newbullet->type = 10;
				double targetx = (double)(p1.f_ReturnRect().left + 20);
				double targety = (double)(p1.f_ReturnRect().top + 20);
				double ang = angle((double)(p->x), (double)(p->y) , targetx,targety );
				newbullet->mx = -cos(ang);
				newbullet->my = -sin(ang);

				newbullet->next = bullethd;
				bullethd = newbullet;
			}
		}
	}
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

			if (length(p1.f_ReturnRect().left+20, p1.f_ReturnRect().top+20, p->x ,p->y) > MONSTERLEN) {

				if (p1.f_ReturnRect().left+20 < p->x) {
					p->x -= speed;

				}
				else {
					p->x += speed;
				}

				if (p1.f_ReturnRect().top+20 < p->y) {
					p->y -= speed;

				}
				else {
					p->y += speed;
				}
				/*
				if (p1.f_ReturnRect().left > p->x) {
					p->x += speed;

				}

				if (p1.f_ReturnRect().top > p->y) {
					p->y += speed;

				}
				*/
			}

		}
	}
}

void mop::f_Update(monster*& mophd, bullet*& bullethd, Player1& p1){
	move(mophd, p1);
	attack(mophd, bullethd, p1);
}

void mop::rander(HDC dc, monster*& hd) {

	for (monster* p = hd; p != NULL; p = p->next) {
		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(RGB(255, 0, 0)); // ���ο� ��ü �����: �귯��
		oldBrush = (HBRUSH)SelectObject(dc, hBrush);
		Rectangle(dc, p->x - MOPSIZE, p->y - MOPSIZE, p->x + MOPSIZE, p->y + MOPSIZE);
		SelectObject(dc, oldBrush); // ������ �귯�÷� ���ư���
		DeleteObject(hBrush);
	}
}
