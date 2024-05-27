#include "MONSTER.h"

std::list<mop*> monster_manager::mops;
int MONSTERLEN = 200;
int MOPSIZE = 20;

std::random_device rdmop;
std::mt19937 genmop;
std::uniform_int_distribution<int> sponsemop(0, 800);

mop::mop(int type) {
	mop_inform.x = sponsemop ( genmop );
	mop_inform.y = sponsemop ( genmop );
	mop_inform.hp = 100;
	mop_inform.type = type;
	mop_inform.cnt = 0;
}


void mop::attack(Player1& p1) {

	
		if (mop_inform.type == 1) {

		}
		else if ( mop_inform.type == 2) {
			

			double targetx = ( double ) ( p1.ReturnRect ( ).left + 20 );
			double targety = ( double ) ( p1.ReturnRect ( ).top + 20 );
			double ang = angle ( ( double ) ( mop_inform.x ) , ( double ) ( mop_inform.y ) , targetx , targety );
			bullet* newbullet = new bullet ( mop_inform.x , mop_inform.y , 10 , -cos ( ang ) , -sin ( ang ) );
			bulletmanager::CreateBullet ( newbullet );
		
		}
	
}

void mop::move( Player1 &p1) {
	float speed = 600 * Time::DeltaTime();
	
		if ( mop_inform.type == 1) {

			if (p1.ReturnRect().left < mop_inform.x) {
				mop_inform.x -= speed;

			}

			if (p1.ReturnRect().top < mop_inform.y) {
				mop_inform.y -= speed;

			}

			if (p1.ReturnRect().left > mop_inform.x) {
				mop_inform.x += speed;
				
			}

			if (p1.ReturnRect().top > mop_inform.y) {
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



void monster_manager::spone ( int type ) {
	mop* newmop = new mop(type);

	mops.push_back ( newmop );
	
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
