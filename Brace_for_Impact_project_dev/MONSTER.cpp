#include "MONSTER.h"
#define SIZE 256


//std::list<mop*> MonsterManager::mops;
int MONSTERLEN = 500;
int MOPSIZE = 20;
int BLOCKCOUNT = 20;

std::random_device rdmop;
std::mt19937 genmop;
std::uniform_int_distribution<int> sponsemop(0, 800);

mop::mop(int type) {
	mop_inform.x = sponsemop ( genmop );
	mop_inform.y = sponsemop ( genmop );
	if ( type == 1 ) {
		mop_inform.hp = 2;
	}
	else if ( type != 1 ) {
		mop_inform.hp = 1;
	}

	mop_inform.type = type;
	mop_inform.cnt = 0;
	attack_count = 0;
	move_count = 0;
	switch( mop_inform.type ){
	case 1:

		break;
	}
}

void mop::attack( Tank& p1) {
	RECTS moprect = { mop_inform.x   , mop_inform.y   , mop_inform.x + 100  , mop_inform.y + 100 };
	RECTS tankrect = { p1.ReturnRect ( ).left+30   , p1.ReturnRect ( ).top+40  , p1.ReturnRect ( ).right+165  , p1.ReturnRect ( ).bottom+175 };

	if ( attack_count >= 5 ) {
		if ( mop_inform.type == 1 ) {

		}
		else if ( mop_inform.type == 2 ) {

			bulletshot ( p1.ReturnRect ( ).left + 60 , p1.ReturnRect ( ).top + 60 , mop_inform.x + 40 , mop_inform.y + 40 , 11 );

		}
		else if ( mop_inform.type == 4 ) {

			bulletshot ( p1.ReturnRect ( ).left + 60 , p1.ReturnRect ( ).top + 60 , mop_inform.x + 40 , mop_inform.y + 40 , 12 );

		}
		attack_count = 0;
	}
	if ( attack_count <= 1 ) {
		if ( attack_count >= 0.1 ) {
			if ( mop_inform.type == 3 ) {

				//double targetx = ( double ) ( p1.ReturnRect ( ).left + 60 );
				//double targety = ( double ) ( p1.ReturnRect ( ).top + 60 );
				//double ang = angle ( ( double ) ( mop_inform.x ) , ( double ) ( mop_inform.y ) , targetx , targety );
				//bullet* newbullet = new bullet ( mop_inform.x+30 , mop_inform.y+30 , 10 , -cos ( ang ) , -sin ( ang ) );
				//BulletManager::getInstance ( ).CreateBullet ( newbullet );
				bulletshot ( p1.ReturnRect ( ).left + 60 , p1.ReturnRect ( ).top + 60 , mop_inform.x + 40 , mop_inform.y + 40 , 10 );
				//attack_count = 0;
			}
		}
	}
	else {
		if ( attack_count >= 10 ) {
			attack_count = 0;
		}
	}
	if ( mop_inform.type == 5 ) {
		if ( rect2rect ( tankrect , moprect ) ) {
			mop_inform.hp = 0;
			TankController::Damage ( 50 );
		}
		//bulletshot ( p1.ReturnRect ( ).left + 60 , p1.ReturnRect ( ).top + 60 , mop_inform.x + 40 , mop_inform.y + 40 ,13);
	}
	attack_count += Time::DeltaTime ( );
}

void mop::move ( Tank& p1  ) {
	//OSW: 속도 300 -> 100으로 수정함
	float speed = 100 * Time::DeltaTime ( );
	BOOL blockmop = 0;
	RECTS moprect = ReturnRect ( );
	RECTS cpyrect;
	for ( auto& ScanBlock : BlockManager::getInstance().BlockReturn()) {
		//벽과 몹 충돌
		if ( rect2rect ( ScanBlock.ReturnRect ( ) , moprect ) ) {
			if ( ScanBlock.ReturnRect ( ).top >= moprect.top ) {
				mop_inform.y -= 2*speed;
			}
			if ( ScanBlock.ReturnRect ( ).bottom <= moprect.bottom ) {
				mop_inform.y += 2*speed;
			}
			if ( ScanBlock.ReturnRect ( ).right <= moprect.right ) {
				mop_inform.x += 2*speed;
			}
			if ( ScanBlock.ReturnRect ( ).left >= moprect.left ) {
				mop_inform.x -= 2*speed;
			}
		}
		if ( rect2Line4 ( ScanBlock.ReturnRect ( ) , p1.ReturnRect ( ) , moprect ) ) {
			blockmop = 1;
			cpyrect = ScanBlock.ReturnRect ( );
		}
	}
	float len = 0;
	BOOL ckBlock=0;
	if ( mop_inform.type == 1 || mop_inform.type == 5 ) {
		if ( frame >= 6 ) frame = 0;
		if ( blockmop ) {
			//몹 아래 장애물
			if ( cpyrect.top > moprect.bottom ) {
				mop_inform.x += speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopLeft ( ScanBlock.ReturnRect ( ) , moprect ) ) {
						len = abs_F ( ScanBlock.ReturnRect ( ).left - moprect.right);
						ckBlock = 1;
					}
				}
				if ( ckBlock && len<10) {
					mop_inform.y -= speed;
				}
				ckBlock = 0;
			}
			if ( cpyrect.bottom < moprect.top ) {
				mop_inform.x -= speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopRight ( ScanBlock.ReturnRect ( ) , moprect ) ) {
						len = abs_F(ScanBlock.ReturnRect ( ).right - moprect.left);
						ckBlock = 1;
					}
				}
				if ( ckBlock && len < 10 ) {
					mop_inform.y += speed;
				}
				ckBlock = 0;
			}
			if ( cpyrect.right < moprect.left ) {
				mop_inform.y += speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopUp ( ScanBlock.ReturnRect ( ) , moprect ) ) {
						len = abs_F ( ScanBlock.ReturnRect ( ).top - moprect.bottom );
						ckBlock = 1;
					}
				}
				if ( ckBlock && len < 10 ) {
					mop_inform.x += speed;
				}
				ckBlock = 0;
			}
			if ( cpyrect.left > moprect.right ) {
				mop_inform.y -= speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopDown ( ScanBlock.ReturnRect ( ) , moprect ) ) {
						len = abs_F ( ScanBlock.ReturnRect ( ).bottom - moprect.top );
						ckBlock = 1;
					}
				}
				if ( ckBlock && len < 10 ) {
					mop_inform.x -= speed;
				}
				ckBlock = 0;
			}
		}
		else {
			if ( p1.ReturnRect ( ).left+50  < mop_inform.x ) {
				mop_inform.x -= speed;
				direct = 3;
			}
			else {
				mop_inform.x += speed;
				direct = 0;
			}
			if ( p1.ReturnRect ( ).top+50  < mop_inform.y ) {
				mop_inform.y -= speed;
			}
			else {
				mop_inform.y += speed;
			}
		}
	}
	else {
		if ( frame >= 6 ) frame = 0;
		if ( blockmop ) {
			//몹 아래 장애물
			if ( cpyrect.top > moprect.bottom ) {
				mop_inform.x += speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopLeft ( ScanBlock.ReturnRect ( ) , moprect ) ) {
						len = abs_F ( ScanBlock.ReturnRect ( ).left - moprect.right );
						ckBlock = 1;
					}
				}
				if ( ckBlock && len < 10 ) {
					mop_inform.y -= speed;
				}
				ckBlock = 0;
			}
			if ( cpyrect.bottom < moprect.top ) {
				mop_inform.x -= speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopRight ( ScanBlock.ReturnRect ( ) , moprect ) ) {
						len = abs_F ( ScanBlock.ReturnRect ( ).right - moprect.left );
						ckBlock = 1;
					}
				}
				if ( ckBlock && len < 10 ) {
					mop_inform.y += speed;
				}
				ckBlock = 0;
			}
			if ( cpyrect.right < moprect.left ) {
				mop_inform.y += speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopUp ( ScanBlock.ReturnRect ( ) , moprect ) ) {
						len = abs_F ( ScanBlock.ReturnRect ( ).top - moprect.bottom );
						ckBlock = 1;
					}
				}
				if ( ckBlock && len < 10 ) {
					mop_inform.x += speed;
				}
				ckBlock = 0;
			}
			if ( cpyrect.left > moprect.right ) {
				mop_inform.y -= speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopDown ( ScanBlock.ReturnRect ( ) , moprect ) ) {
						len = abs_F ( ScanBlock.ReturnRect ( ).bottom - moprect.top );
						ckBlock = 1;
					}
				}
				if ( ckBlock && len < 10 ) {
					mop_inform.x -= speed;
				}
				ckBlock = 0;
			}
		}
		else {
			if ( length ( p1.ReturnRect ( ).left + 60 , p1.ReturnRect ( ).top + 60 , mop_inform.x , mop_inform.y ) > MONSTERLEN ) {

				if ( p1.ReturnRect ( ).left  < mop_inform.x ) {
					mop_inform.x -= speed;
					direct = 3;
				}
				else {
					mop_inform.x += speed;
					direct = 0;
				}
				if ( p1.ReturnRect ( ).top  < mop_inform.y ) {
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

	if ( move_count >= 0.1 ) {
		frame++;
		if ( frame >= 6 ) frame = 0;
		move_count = 0;
	}
	move_count += Time::DeltaTime ( );


}

void mop::Update( ){
	
	move ( PlayerManager::getInstance ( ).Tank_return ( ) );

	attack ( PlayerManager::getInstance ( ).Tank_return ( ) );
	
}

void mop::Render( const HDC& dc) {

	
		HBRUSH hBrush, oldBrush;
		RECTS tankrect = PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( );
		//Rectangle ( dc , tankrect.left +30 , tankrect.top +40 , tankrect.right+165 , tankrect.bottom+175 ); //히트박스
		/*if ( TankController::camera.left>=mop_inform.x- MOPSIZE+SIZE ||
			TankController::camera.right<=mop_inform.y - MOPSIZE + SIZE ) {
			return;
		}*/
		if (( mop_inform.x - MOPSIZE + SIZE < TankController::camera.left || mop_inform.x - MOPSIZE  > TankController::camera.right || mop_inform.y - MOPSIZE + SIZE  < TankController::camera.top || mop_inform.y - MOPSIZE > TankController::camera.bottom )) {
			//std::cout << "extrude" << std::endl;
			return;
		}
		//OSW 적 가죽1
		if ( mop_inform.type == 1 ) { //기본
			Rectangle ( dc , mop_inform.x + 30 , mop_inform.y + 20 , mop_inform.x + 190 , mop_inform.y + 220 );
			TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_1" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
		}
		else if ( mop_inform.type == 2 ) { // 한발
			Rectangle ( dc , mop_inform.x +40  , mop_inform.y+20  , mop_inform.x +190 , mop_inform.y +180 );
			TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_2" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
		}
		else if ( mop_inform.type == 3 ) { //오줌
			Rectangle ( dc , mop_inform.x , mop_inform.y + 70 , mop_inform.x + 490 , mop_inform.y + 350 );
			TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE * 2 , SIZE * 2 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_2" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
		}
		else if ( mop_inform.type == 4 ) { // 탄폭파
			Rectangle ( dc , mop_inform.x , mop_inform.y+30  , mop_inform.x + 210 , mop_inform.y + 180 );
			//hBrush = CreateSolidBrush ( RGB ( 0 , 255 , 255 ) ); // ���ο� ��ü �����: �귯��
			//oldBrush = ( HBRUSH ) SelectObject ( dc , hBrush );
			TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_3" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			//SelectObject ( dc , oldBrush ); // ������ �귯�÷� ���ư���
			//DeleteObject ( hBrush );
			
			
		}
		else if ( mop_inform.type == 5 ) { // 자폭병
			
			Rectangle ( dc , mop_inform.x+40, mop_inform.y+20 , mop_inform.x + 170 , mop_inform.y + 200 );
			TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_4" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			
			
		}
		//

		
		
	
}

RECTS mop::ReturnRect ( ) {
	RECTS r;
	if ( mop_inform.type == 1 ) {
		r = { mop_inform.x + 30 , mop_inform.y + 20 , mop_inform.x + 190 , mop_inform.y + 220 };
	}
	else if ( mop_inform.type == 2 ) {
		r = { mop_inform.x + 40  , mop_inform.y + 20  , mop_inform.x + 190 , mop_inform.y + 180 };
	}
	else if ( mop_inform.type == 3 ) {
		r = { mop_inform.x , mop_inform.y + 70 , mop_inform.x + 490 , mop_inform.y + 350 };
	}
	else if ( mop_inform.type == 4 ) {
		r = { mop_inform.x , mop_inform.y + 30  , mop_inform.x + 210 , mop_inform.y + 180 };
	}
	else if ( mop_inform.type == 5 ) {
		r = { mop_inform.x + 40, mop_inform.y + 20 , mop_inform.x + 170 , mop_inform.y + 200 };
	}


	//RECTS r = { mop_inform.x,mop_inform.y, mop_inform.x+200 , mop_inform.y+200 };  //256 * 256

	return r;
}

int mop::ReturnHP ( ) {
	return mop_inform.hp;
}

void mop::Damage ( int damage ) {
	mop_inform.hp -= damage;
}



void MonsterManager::spawn ( int type ) {

	mop* newmop = new mop(type);
	mops.push_back ( newmop );
	
}



void MonsterManager::Update (  )
{

	for ( auto iter : mops ) {
		if ( iter->ReturnHP ( ) > 0 ) {
			iter->Update ( );
		}
	}

	if ( count >= 10 ) {
		count = 0;
		//spawn ( 1 );
		//spawn ( 2 );
		//spawn ( 3 );
		spawn ( 4 );
		spawn ( 5 );
		
	}
	count += Time::DeltaTime ( );

}

void MonsterManager::Render ( const HDC& mDC)
{
	for ( auto iter : mops ) {
		if ( iter->ReturnHP ( ) > 0 ) {
			iter->Render ( mDC );
		}
	}
}

std::list<mop*>& MonsterManager::MopReturn ( ) {
	return mops;
}
