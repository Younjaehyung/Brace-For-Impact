#include "MONSTER.h"
#define SIZE 256

//status // 0: 중립상태 , 1: 이동 , 2: 공격 , 3: 데미지 , 4: 사망
//std::list<mop*> MonsterManager::mops;
int MONSTERLEN = 300;
int MOPSIZE = 20;
int BLOCKCOUNT = 20;

std::random_device rdmop;
std::mt19937 genmop;
std::uniform_int_distribution<int> sponsemop(0, 800);

mop::mop(int type) {
	if ( type == 1 ) {
		mop_inform.x = 29 * 64;
		mop_inform.y = 20 * 64;
	}
	else if ( type == 2 ) {
		mop_inform.x = 29 * 64;
		mop_inform.y = 20 * 64;
	}
	else if ( type == 3 ) {
		mop_inform.x = 15 * 64;
		mop_inform.y = 6 * 64;
	}
	else if ( type == 4 ) {
		mop_inform.x = 15 * 64;
		mop_inform.y = 4 * 64;
	}
	else if ( type == 5) {
		mop_inform.x = 29  * 64;
		mop_inform.y = 12 * 64;
	}
	else if ( type == 6 ) {
		mop_inform.x = 25 * 64;
		mop_inform.y = 12 * 64;
	}


	if ( type == 1 ) {
		mop_inform.hp = 130; //꽁끼깅낑꽁깡꽁까강
	}
	else if ( type == 2 ) { //빵빵이
		mop_inform.hp = 130;
	}
	else if ( type == 3 ) { //오줌
		mop_inform.hp = 150;
	}
	else if ( type == 4 ) { //튼튼이
		mop_inform.hp = 120;
	}
	else if ( type == 5 ) { //자폭이
		mop_inform.hp = 100;
	}
	else if ( type == 6 ) { //춘식이
		mop_inform.hp = 100;
	}
	else if ( type == 10 ) { //튼튼이 소환몹
		mop_inform.hp = 10;
	}
	else if ( type == 11 ) { //오줌이 소환몹
		mop_inform.hp = 10;
	}

	mop_inform.type = type;
	mop_inform.cnt = 0;
	attack_count = 0;
	move_count = 0;

}

void mop::attack( Tank& p1) {
	RECTS moprect = ReturnRect();
	RECTS tankrect = p1.ReturnRect ( );
	float speed = 300 * Time::DeltaTime ( );
	if ( mop_inform.type == 1 ) { //꽁기깅깡
		if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < MONSTERLEN ) {
			status = 2;
			speed *= 1.5;
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }
			if ( mop_inform.cnt == 0 ) {
				if ( p1.ReturnRect ( ).left < mop_inform.x ) {
					mop_inform.x -= speed;
					direct = 3;
				}
				else {
					mop_inform.x += speed;
					if ( p1.ReturnRect ( ).left > mop_inform.x + 1 ) {
						direct = 0;
					}
				}
				if ( p1.ReturnRect ( ).top < mop_inform.y ) {
					mop_inform.y -= speed;
				}
				else {
					mop_inform.y += speed;
				}
			}
			if ( rect2rect ( moprect , tankrect ) ) {
				if ( mop_inform.cnt == 0 ) {
					frame = 0;
					//status = 2;
					TankController::Damage ( 50 );
					mop_inform.cnt++;
				}
				attack_count = 0;
			}
		}
		if ( attack_count >= 3 ) {
			attack_count = 0;
			status = 0;
			mop_inform.cnt =0;
			direct = 0;
		}
	}
	else if ( mop_inform.type == 2 ) { //빵빵이
		if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < MONSTERLEN ) {
			status = 2;
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }
		}
		if ( attack_count >= 5 ) {
			bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 11 );
			attack_count = 0;
			status = 0;
			direct = 0;
		}
	}
	else if ( mop_inform.type == 3 ) { //몬스터 소환술사
		if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < MONSTERLEN ) {
			status = 2;
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }

		}
		if ( attack_count >= 5 ) {
			if ( mop_inform.cnt < 10 ) {
				mop* newmop = new mop ( 10 );
				newmop->mop_inform.x = middleX ( ReturnRect ( ) );
				newmop->mop_inform.y = middleY ( ReturnRect ( ) );
				MonsterManager::getInstance ( ).MopReturn ( ).push_back ( newmop );
				mop_inform.cnt++;
				attack_count = 0;
				status = 0;
				direct = 0;
			}
		}
	}
	else if ( mop_inform.type == 4 ) { //자폭이
		if ( rect2rect ( tankrect , moprect ) ) {
			if ( mop_inform.cnt == 0 ) {
				status = 2;
				if ( direct == 0 ) { direct = 1; }
				else if ( direct == 3 ) { direct = 4; }
				bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 14 );
				mop_inform.cnt++;
			}
		}
		if ( attack_count > 5 ) {
			mop_inform.cnt = 0;
			direct = 0;
			attack_count = 0;
			status = 0;
		}
	}
	else if ( mop_inform.type == 5 ) { //춘식이 탄뿌리기
		if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < MONSTERLEN ) {
			status = 2;
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }
		}
		if ( mop_inform.cnt == 0 ) {
			double targetx = ( double ) ( middleX ( p1.ReturnRect ( ) ) );
			double targety = ( double ) ( middleY ( p1.ReturnRect ( ) ) );
			double ang = angle ( ( double ) ( middleX ( ReturnRect ( ) ) ) , ( double ) ( middleY ( ReturnRect ( ) ) ) , targetx , targety );
			double angle1 = 30 * ( 3.141592 / 180 );
			for ( int i = 0; i < 12; i++ ) {
				bullet* newbullet = new bullet ( middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 12 , -cos ( ang+i * angle1 ) , -sin ( ang+i * angle1 ) );
				BulletManager::getInstance ( ).CreateBullet ( newbullet );
			}
			mop_inform.cnt++;
		}
		else {
			if ( attack_count >= 2 ) {
				mop_inform.cnt = 0;
				attack_count = 0;
				status = 0;
				direct = 0;
			}
		}
	}
	else if ( mop_inform.type == 6 ) {
		if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < MONSTERLEN ) {
			status = 2;
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }
		}
		if ( attack_count <= 2 ) {
			if ( attack_count >= 0 ) {
				bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 10 );
			}
		}
		if ( attack_count >= 10 ) {
			if ( mop_inform.cnt == 0 ) {
				mop* newmop = new mop ( 11 );
				newmop->mop_inform.x = middleX ( ReturnRect ( ) );
				newmop->mop_inform.y = middleY ( ReturnRect ( ) );
				MonsterManager::getInstance ( ).MopReturn ( ).push_back ( newmop );
				mop_inform.cnt++;
			}
		}
		if ( attack_count >= 20 ) {
			mop* newmop = new mop ( 11 );
			newmop->mop_inform.x = middleX ( ReturnRect ( ) );
			newmop->mop_inform.y = middleY ( ReturnRect ( ) );
			MonsterManager::getInstance ( ).MopReturn ( ).push_back ( newmop );
			mop_inform.cnt = 0;

			attack_count = 0;
			status = 0;
			direct = 0;
		}


		}
	else if ( mop_inform.type == 10 ) {// 소환몹
		if ( rect2rect ( moprect , tankrect ) ) {
			if ( mop_inform.cnt == 0 ) {
				status = 2;
				TankController::Damage ( 10 );
			}
			mop_inform.cnt++;
			attack_count = 0;
		}
		if ( attack_count >= 5 ) {
			attack_count = 0;
			status = 0;
			mop_inform.cnt = 0;
		}
	}
	else if ( mop_inform.type == 11 ) {// 오줌싸개 소환몹
		if ( rect2rect ( moprect , tankrect ) ) {
			if ( mop_inform.cnt == 0 ) {
				status = 2;
				TankController::Damage ( 10 );
			}
			mop_inform.cnt++;
			attack_count = 0;
		}
		if ( attack_count >= 5 ) {
			attack_count = 0;
			status = 0;
			mop_inform.cnt = 0;
		}
	}

	if ( !( mop_inform.type == 11 || mop_inform.type == 10 ) ) {
		if ( rect2rect ( moprect , tankrect ) ) {
			//TankController::Damage ( 1 );  // 몬스터 틱뎀 원인
		}
	}

	attack_count += Time::DeltaTime ( );
	
}

void mop::move ( Tank& p1  ) {
	//OSW: 속도 300 -> 100으로 수정함
	float speed = 100 * Time::DeltaTime ( );
	if ( mop_inform.type == 4 )speed *= 2;
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
	if ( mop_inform.type == 1 || mop_inform.type == 4 || mop_inform.type == 10 || mop_inform.type == 11 ) {
		if ( frame >= 6 ) frame = 0;
		if ( blockmop ) {
			//몹 아래 장애물
			if ( cpyrect.top > moprect.bottom ) {
				mop_inform.x += speed;
				for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
					if ( ckMopRight ( ScanBlock.ReturnRect ( ) , moprect ) ) {
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
					if ( ckMopLeft ( ScanBlock.ReturnRect ( ) , moprect ) ) {
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
			if ( p1.ReturnRect ( ).left  < mop_inform.x ) {
				mop_inform.x -= speed;

				direct = 3;

			}
			else {
				mop_inform.x += speed;
				if ( p1.ReturnRect ( ).left > mop_inform.x +1) {
					direct = 0;
				}
			}
			if ( p1.ReturnRect ( ).top  < mop_inform.y ) {
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
					if ( ckMopRight ( ScanBlock.ReturnRect ( ) , moprect ) ) {
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
					if ( ckMopLeft ( ScanBlock.ReturnRect ( ) , moprect ) ) {
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
			if ( length ( middleX( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect() ) , middleY ( ReturnRect ( ) ) ) > MONSTERLEN ) {

				if ( p1.ReturnRect ( ).left  < mop_inform.x ) {
					mop_inform.x -= speed;
					direct = 3;
				}
				else {
					mop_inform.x += speed;
					if ( p1.ReturnRect ( ).left > mop_inform.x + 1 ) {
						direct = 0;
					}
				}
				if ( p1.ReturnRect ( ).top  < mop_inform.y ) {
					mop_inform.y -= speed;
				}
				else {
					mop_inform.y += speed;
				}
			}
		}
	}
	/*
	if ( move_count >= 0.1 ) {
		frame++;
		if ( frame >= 6 ) frame = 0;
		move_count = 0;
	}
	move_count += Time::DeltaTime ( );
	*/

}

void mop::Update( ){
	
	if ( status == 0 || status == 1 ) {
		status = 1;
		move ( PlayerManager::getInstance ( ).Tank_return ( ) );
	}
	if ( !( status == 3 || status == 4 || status == 5 ) ) {
		attack ( PlayerManager::getInstance ( ).Tank_return ( ) );
	}

	if ( !(status == 4 || status == 2||status==5) ) {
		if ( move_count >= 0.15 ) {
			frame++;
			move_count = 0;
			if ( frame >= 6 ) {
				frame = 0;
				if ( status == 3 ) 
				{ status = 0; }
			}
			
		}
		move_count += Time::DeltaTime ( );
	}
	else if ( status == 2 ) {
		if ( move_count >=0.15 ) {
			frame++;
			if ( frame >= 6 ) {
				frame = 5;

				//if ( status == 3 ) status = 0;
			}
			move_count = 0;
		}

		move_count += Time::DeltaTime ( );
	}
	else if( status == 4 ){
		if ( die_timer >= 0.25 ) {
			
			if ( die_frame > 6 ) {
				die_frame = 5;
				status = 5;
			}
			else {
				
				die_frame++;
				
			}
			die_timer = 0;
		}

		die_timer += Time::DeltaTime ( );
	
	}
}

void mop::Render( const HDC& dc) {

	
		HBRUSH hBrush, oldBrush;
	
		//Rectangle ( dc , tankrect.left , tankrect.top , tankrect.right , tankrect.bottom ); //히트박스
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
			//Rectangle ( dc , mop_inform.x + 30 , mop_inform.y + 20 , mop_inform.x + 190 , mop_inform.y + 220 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_1" ) , 0, direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_1" ) , die_frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				//Rectangle ( dc , 200 , 200 , 600 , 600 );
			}
			else if ( status == 5 ) {//적 사망시
				
			}
			else { // 기본 움직임 상태
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_1" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
		
		}
		else if ( mop_inform.type == 2 ) { // 한발
			//Rectangle ( dc , mop_inform.x +40  , mop_inform.y+20  , mop_inform.x +190 , mop_inform.y +180 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_2" ) , 0 , 2 * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_2" ) , die_frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				//Rectangle ( dc , 200 , 200 , 600 , 600 );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_2" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
		}
		else if ( mop_inform.type == 3 ) { // 
			//Rectangle ( dc , mop_inform.x , mop_inform.y+30  , mop_inform.x + 210 , mop_inform.y + 180 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_3" ) , 0 , 2 * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_3" ) , die_frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				//Rectangle ( dc , 200 , 200 , 600 , 600 );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_3" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
		}
		else if ( mop_inform.type == 4 ) { // 자폭병
			//Rectangle ( dc , mop_inform.x+40, mop_inform.y+20 , mop_inform.x + 170 , mop_inform.y + 200 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_4" ) , 0 , 2 * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_4" ) , die_frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				//Rectangle ( dc , 200 , 200 , 600 , 600 );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_4" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
		}
		else if ( mop_inform.type == 5 ) { // 춘식이
			//Rectangle ( dc , mop_inform.x+50 , mop_inform.y , mop_inform.x + 170 , mop_inform.y + 230 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_5" ) , 0 , 2 * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_5" ) , die_frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				//Rectangle ( dc , 200 , 200 , 600 , 600 );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_5" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
		}
		else if ( mop_inform.type == 6 ) { //오줌
			//Rectangle ( dc , mop_inform.x , mop_inform.y + 70 , mop_inform.x + 490 , mop_inform.y + 350 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_6" ) , 0 , 2 * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_6" ) , die_frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				//Rectangle ( dc , 200 , 200 , 600 , 600 );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_6" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
		}
		else if ( mop_inform.type == 10 ) { // 쪼꼬미 4가 소환함
			//Rectangle ( dc , mop_inform.x , mop_inform.y , mop_inform.x + 100 , mop_inform.y + 100 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE / 2 , SIZE / 2 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_1" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE / 2 , SIZE / 2 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_1" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE / 2 , SIZE / 2 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_1" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
		}
		else if ( mop_inform.type == 11 ) { // 쪼꼬미 오줌이가 소환함
			//Rectangle ( dc , mop_inform.x , mop_inform.y , mop_inform.x + 100 , mop_inform.y + 100 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE / 2 , SIZE / 2 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_4" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE / 2 , SIZE / 2 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_4" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE / 2 , SIZE / 2 ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Enemy_4" ) , frame * 128 , direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
			}
		}
}

RECTS& mop::ReturnRect ( ) {
	RECTS r;
	if ( mop_inform.type == 1 ) {
		r = { mop_inform.x + 30 , mop_inform.y + 20 , mop_inform.x + 190 , mop_inform.y + 220 };
	}
	else if ( mop_inform.type == 2 ) {
		r = { mop_inform.x + 40  , mop_inform.y + 20  , mop_inform.x + 190 , mop_inform.y + 180 };
	}
	else if ( mop_inform.type == 6 ) {
		r = { mop_inform.x , mop_inform.y + 70 , mop_inform.x + 490 , mop_inform.y + 350 };
	}
	else if ( mop_inform.type == 3 ) {
		r = { mop_inform.x , mop_inform.y + 30  , mop_inform.x + 210 , mop_inform.y + 180 };
	}
	else if ( mop_inform.type == 4 ) {
		r = { mop_inform.x + 40, mop_inform.y + 20 , mop_inform.x + 170 , mop_inform.y + 200 };
	}
	else if ( mop_inform.type == 5 ) {
		r = { mop_inform.x + 50 , mop_inform.y , mop_inform.x + 170 , mop_inform.y + 230 };
	}
	else if( mop_inform.type == 10 || mop_inform.type ==11){
		r = { mop_inform.x, mop_inform.y , mop_inform.x + 100 , mop_inform.y + 100 };
	}
	else {
		r = { mop_inform.x, mop_inform.y , mop_inform.x + 200 , mop_inform.y + 200 };
	}


	//RECTS r = { mop_inform.x,mop_inform.y, mop_inform.x+200 , mop_inform.y+200 };  //256 * 256

	return r;
}

int mop::ReturnHP ( ) {
	return mop_inform.hp;
}

void mop::Damage ( int damage ) {
	if ( mop_inform.hp > 0 ) {
		mop_inform.hp -= damage;
	}
	else if ( mop_inform.hp < 0 ) {
		mop_inform.hp = 0;
	}

	if ( mop_inform.hp <= 0 ) {
		//사망시
		status = 4;

		//보고 있는 방향에 따라 죽는 모션 차이
		if ( direct == 0 || direct == 1 ) {
			direct = 2;
		}
		else if ( direct == 3 || direct == 4 ) {
			direct = 5;
		}

	}
	else {//피격시
		status = 3;
		
		if ( direct == 0 ) {
			direct = 2;
		}
		else if ( direct == 3 ) {
			direct = 5;
		}
		
		//attacked_timer += Time::DeltaTime ( );
	}

}



void MonsterManager::spawn ( int type ) {

	mop* newmop = new mop(type);
	mops.push_back ( newmop );
	
}

//void MonsterManager::SpawnMonster (int type  ) {
//
//
//
//	if ( count >= 10000.0 ) {
//		count = 0;
//		spawn ( 1 );
//		spawn ( 2 );
//	
//	}
//	count += Time::DeltaTime ( );
//
//}

void MonsterManager::Clear ( ) {
	count = 0;
	deletetime = 0;
	mops.clear ( );
}

void MonsterManager::DeleteMonster () {

	if ( mops.size ( ) ) {
		deletetime += Time::DeltaTime ( );
		if ( deletetime > 7.0 ) {


			for ( auto iter = mops.begin ( ); iter != mops.end ( );) {
				if ( ( *iter )->status == 5) {  // 반복자가 가리키는 객체에 접근하기 위해 *iter 사용
					mop* del = *iter;  // 삭제할 노드의 포인터를 저장
					iter = mops.erase ( iter );  // 삭제한 노드의 다음 노드의 반복자를 반환

					delete del;  // 삭제할 노드를 메모리에서 해제

				}
				else {
					++iter;  // 다음 노드로 이동
				}
			}
			deletetime = 0;
		}


	}

}


void MonsterManager::Update (  )
{

	for ( auto iter : mops ) {
		//if ( iter->ReturnHP ( ) >= 0 ) {
			iter->Update ( );
		//}
	}

	DeleteMonster ( );


}

void MonsterManager::Render ( const HDC& mDC)
{
	
	for ( auto iter : mops ) {
		//if ( IntersectRect_float ( iter->ReturnRect ( ) , TankController::camera ) ) {
			iter->Render ( mDC );
		//}
		
	}
}

std::list<mop*>& MonsterManager::MopReturn ( ) {
	return mops;
}
