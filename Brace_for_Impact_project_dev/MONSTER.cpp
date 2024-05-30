#include "MONSTER.h"

//std::list<mop*> MonsterManager::mops;
int MONSTERLEN = 200;
int MOPSIZE = 20;
int BLOCKCOUNT = 20;

std::random_device rdmop;
std::mt19937 genmop;
std::uniform_int_distribution<int> sponsemop(0, 800);

mop::mop(int type) {
	mop_inform.x = sponsemop ( genmop );
	mop_inform.y = sponsemop ( genmop );
	mop_inform.hp = 100;
	mop_inform.type = type;
	mop_inform.cnt = 0;
	attack_count = 0;
}


void mop::attack( Tank& p1) {

	if ( attack_count >= 5 ) {
		if ( mop_inform.type == 1 ) {

		}
		else if ( mop_inform.type == 2 ) {

			double targetx = ( double ) ( p1.return_rect ( ).left + 20 );
			double targety = ( double ) ( p1.return_rect ( ).top + 20 );
			double ang = angle ( ( double ) ( mop_inform.x ) , ( double ) ( mop_inform.y ) , targetx , targety );
			bullet* newbullet = new bullet ( mop_inform.x , mop_inform.y , 10 , -cos ( ang ) , -sin ( ang ) );
			BulletManager::getInstance().CreateBullet ( newbullet );

		}
		attack_count = 0;
	}
	attack_count += Time::DeltaTime ( );
}

<<<<<<< .merge_file_5eRAzh
void mop::move( Tank& p1) {
=======
void mop::move( Player1 &p1 , Block blocks[] ) {
>>>>>>> .merge_file_40bg4J
	float speed = 600 * Time::DeltaTime();
	BOOL blockmop = 0;
	for ( int i = 0; i < BLOCKCOUNT; i++ ) {
		if ( rect2Line ( blocks[ i ].ReturnRect ( ) , p1.ReturnRect ( ).left + 20 , p1.ReturnRect ( ).top + 20 , mop_inform.x , mop_inform.y ) ) {
			blockmop = 1;
		}
	}

		if ( mop_inform.type == 1) {

			if ( p1.return_rect ( ).left < mop_inform.x) {
				mop_inform.x -= speed;

			}

			if ( p1.return_rect ( ).top < mop_inform.y) {
				mop_inform.y -= speed;

			}

			if ( p1.return_rect ( ).left > mop_inform.x) {
				mop_inform.x += speed;
				
			}

			if ( p1.return_rect ( ).top > mop_inform.y) {
				mop_inform.y += speed;

			}


		}
		else if ( mop_inform.type == 2) {
			if ( blockmop ) {

				mop_inform.x += speed;

<<<<<<< .merge_file_5eRAzh
			if (length( p1.return_rect ( ).left+20, p1.return_rect ( ).top+20, mop_inform.x , mop_inform.y) > MONSTERLEN) {

				if ( p1.return_rect ( ).left+20 < mop_inform.x) {
					mop_inform.x -= speed;
=======
			}
			else {
				if ( length ( p1.ReturnRect ( ).left + 20 , p1.ReturnRect ( ).top + 20 , mop_inform.x , mop_inform.y ) > MONSTERLEN ) {

					if ( p1.ReturnRect ( ).left + 20 < mop_inform.x ) {
						mop_inform.x -= speed;
>>>>>>> .merge_file_40bg4J

					}
					else {
						mop_inform.x += speed;
					}

<<<<<<< .merge_file_5eRAzh
				if ( p1.return_rect ( ).top+20 < mop_inform.y) {
					mop_inform.y -= speed;
=======
					if ( p1.ReturnRect ( ).top + 20 < mop_inform.y ) {
						mop_inform.y -= speed;
>>>>>>> .merge_file_40bg4J

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
	
}

<<<<<<< .merge_file_5eRAzh
void mop::Update( ){
	move(PlayerManager::getInstance().Tank_return());
	attack( PlayerManager::getInstance ( ).Tank_return ( ) );
=======
void mop::Update( Player1& p1 , Block blocks[] ){
	move( p1, blocks);
	attack(  p1);
>>>>>>> .merge_file_40bg4J
}

void mop::Render( const HDC& dc) {

	
		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(RGB(255, 0, 0)); // ���ο� ��ü �����: �귯��
		oldBrush = (HBRUSH)SelectObject(dc, hBrush);
		Rectangle(dc, mop_inform.x - MOPSIZE, mop_inform.y - MOPSIZE, mop_inform.x + MOPSIZE, mop_inform.y + MOPSIZE);
		
		SelectObject(dc, oldBrush); // ������ �귯�÷� ���ư���
		DeleteObject(hBrush);
	
}



void MonsterManager::spone ( int type ) {

	mop* newmop = new mop(type);
	mops.push_back ( newmop );
	
}


<<<<<<< .merge_file_5eRAzh
void MonsterManager::Update (  )
{
	for ( auto iter : mops ) {
		iter->Update (  );
=======
void MonsterManager::Update ( Player1& p1 , Block blocks[] )
{
	for ( auto iter : mops ) {
		iter->Update ( p1 , blocks);
>>>>>>> .merge_file_40bg4J
	}
}

void MonsterManager::Render ( const HDC& mDC)
{
	for ( auto iter : mops ) {
		iter->Render(mDC);
	}
}
