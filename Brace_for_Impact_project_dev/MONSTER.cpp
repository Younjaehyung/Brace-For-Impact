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


void mop::attack(Player1& p1) {

	
		if (mop_inform.type == 1) {

		}
		else if ( mop_inform.type == 2) {
			
			
			bulletmanager::CreateBullet (p1,2);
				
			
		}
	
}

void mop::move( Player1 &p1) {
	float speed = 600 * Time::DeltaTime();
	
		if ( mop_inform.type == 1) {

			if (p1.ReturnRect().left < p->x) {
				mop_inform.x -= speed;

			}

			if (p1.ReturnRect().top < p->y) {
				mop_inform.y -= speed;

			}

			if (p1.ReturnRect().left > p->x) {
				mop_inform.x += speed;
				
			}

			if (p1.ReturnRect().top > p->y) {
				mop_inform.y += speed;

			}


		}
		else if ( mop_inform.type == 2) {

			if (length(p1.ReturnRect().left+20, p1.ReturnRect().top+20, mop_inform.x , mop_inform.y) > MONSTERLEN) {

				if (p1.ReturnRect().left+20 < mop_inform.x) {
					mop_inform.x -= speed;

				}
				else {
					mop_inform.x += speed;
				}

				if (p1.ReturnRect().top+20 < mop_inform.y) {
					mop_inform.y -= speed;

				}
				else {
					mop_inform.y += speed;
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

void mop::Update( Player1& p1){
	move( p1);
	attack(  p1);
}

void mop::render(HDC dc) {

	
		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(RGB(255, 0, 0)); // ���ο� ��ü �����: �귯��
		oldBrush = (HBRUSH)SelectObject(dc, hBrush);
		Rectangle(dc, mop_inform.x - MOPSIZE, mop_inform.y - MOPSIZE, mop_inform.x + MOPSIZE, mop_inform.y + MOPSIZE);
		
		SelectObject(dc, oldBrush); // ������ �귯�÷� ���ư���
		DeleteObject(hBrush);
	
}



monster* monster_manager::spone ( int type ) {
	monster* newmop = new monster;
	newmop->x = sponsemop ( genmop );
	newmop->y = sponsemop ( genmop );
	newmop->hp = 100;
	newmop->type = type;
	newmop->cnt = 0;


	return newmop;
}


void monster_manager::Update ( Player1& p1 )
{
	for ( auto iter : mops ) {
		iter->Update ( p1 );
	}
}

void monster_manager::render ( HDC mDC)
{
	for ( auto iter : mops ) {
		iter->render(mDC);
	}
}
