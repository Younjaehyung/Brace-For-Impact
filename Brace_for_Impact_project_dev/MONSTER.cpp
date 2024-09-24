#include "MONSTER.h"
#define SIZE 256
#define BIGSIZE 768

//status // 0: 중립상태 , 1: 이동 , 2: 공격 , 3: 데미지 , 4: 사망
//std::list<mop*> MonsterManager::mops;
int MONSTERLEN = 300;
int MOPSIZE = 20;
int BLOCKCOUNT = 20;

std::random_device rd_mop;
std::mt19937 gen_mop ( rd_mop ( ) );
std::uniform_int_distribution<int> rand_atk ( 1 , 1000 );

std::random_device rdmop;
std::mt19937 genmop;
std::uniform_int_distribution<int> sponsemop(0, 800);
std::uniform_int_distribution<int> random_sound (0,10 );
mop::mop(int type) {
	if ( type == 1 ) {
		mop_inform.x = 28 * 64;
		mop_inform.y = 20 * 64;
	}
	else if ( type == 2 ) {
		mop_inform.x = 28 * 64;
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
		mop_inform.x = 11 * 64;
		mop_inform.y = 13 * 64;
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
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }
			if ( mop_inform.cnt == 0 ) {
				monster mop_inform = this->mop_inform;
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
				
				if (! IntersectRect_float ( ReturnRect ( ) , tankrect ) ) {//적과 플레이어 탱크 충돌

					this->mop_inform.x = mop_inform.x;
					this->mop_inform.y = mop_inform.y;
				}
				
			}
			RECTS moprect = { mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE ,mop_inform.x - MOPSIZE + SIZE  , mop_inform.y - MOPSIZE + SIZE };
			if ( rect2rect ( moprect , tankrect ) ) {
				if ( mop_inform.cnt == 0 ) {
					frame = 0;
					//status = 2;
					TankController::Damage ( 15 );
					mop_inform.cnt++;
					SoundManager::getInstance ( ).GetSoundID ( "stomp1" )->ReplaySound ( );
					attack_count = 0;
					
				}
				//attack_count = 0; 원래 위치
			}
		}
		if ( attack_count >= 1.1 ) {//원래3
			
			attack_count = 0;
			status = 0;
			mop_inform.cnt =0;
			direct = 0;
		}
		//충돌 수정
	}
	else if ( mop_inform.type == 2 ) { //빵빵이
		if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < MONSTERLEN ) {
			status = 2;
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }
		}
		if ( status == 2 ) {
			if ( attack_count >= 5 ) {
				bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 11 );
				attack_count = 0;
				status = 0;
				direct = 0;
			}
		}
	}
	else if ( mop_inform.type == 3 ) { //몬스터 소환술사
		if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < MONSTERLEN ) {
			status = 2;
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }

		}
		if ( attack_count >= 5 ) {
			if ( status == 2 ) {
				mop* newmop = new mop ( 10 );
				newmop->mop_inform.x = middleX ( ReturnRect ( ) );
				newmop->mop_inform.y = middleY ( ReturnRect ( ) );
				MonsterManager::getInstance ( ).MopReturn ( ).push_back ( newmop );
				SoundManager::getInstance ( ).GetSoundID ( "bip" )->ReplaySound ( );
				attack_count = 0;
				status = 0;
				direct = 0;
			}
			/*
			int ddakkariSpawn = 0;
			for ( auto& ddakkari : MonsterManager::getInstance ( ).MopReturn ( ) ) {
				if ( ddakkari->Returnmop_inform ( ).type == 10 ) {
					ddakkariSpawn += 1;
				}
			}
			if (  ddakkariSpawn <=8 ) {
				mop* newmop = new mop ( 10 );
				newmop->mop_inform.x = middleX ( ReturnRect ( ) );
				newmop->mop_inform.y = middleY ( ReturnRect ( ) );
				MonsterManager::getInstance ( ).MopReturn ( ).push_back ( newmop );
				
				attack_count = 0;
				status = 0;
				direct = 0;
			}
			*/
		}
	}
	else if ( mop_inform.type == 4 ) { //자폭이
		if ( rect2rect ( tankrect , moprect ) ) {
			if ( mop_inform.cnt == 0 ) {
				status = 2;
				if ( direct == 0 ) { direct = 1; }
				else if ( direct == 3 ) { direct = 4; }
				SoundManager::getInstance ( ).GetSoundID ( "ele" )->ReplaySound ( );
				bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 14 );
				mop_inform.cnt++;
			}
		}
		if ( attack_count > 12 ) {
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
		//공격상태로 변경
		if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < 3*MONSTERLEN && status != 2) {
			status = 2;
			if ( direct == 0 ) { direct = 1; }
			else if ( direct == 3 ) { direct = 4; }
			attack_count = 0;
			//사운드 랜덤 재생 함수
				SoundManager::getInstance ( ).GetSoundID ( "cine" )->ReplaySound ( );
				
			//atk_type = rand ( ) % 3;
		}
		/*
		if ( status == 2 ) {
			if ( attack_count <= 2 ) {
				//2초간 탄 발사
				if ( attack_count >= 0 ) {
					bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 10 );
				}
			}
			if ( attack_count >= 10 ) {
				//몹 소환
				if ( mop_inform.cnt == 0 ) {
					int boom_x , boom_y;
					for ( int i = 0; i < 5; i++ ) {
						boom_x = middleX ( ReturnRect ( ) ) + rand()%1000 - 500 ;
						boom_y = middleY ( ReturnRect ( ) ) + rand()%1000 - 500;
						bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , boom_x , boom_y , 15 );
					}
					mop_inform.cnt++;
				}
			}
			if ( attack_count >= 20 ) {
				//몹 소환2
				mop* newmop = new mop ( 11 );
				newmop->mop_inform.x = middleX ( ReturnRect ( ) );
				newmop->mop_inform.y = middleY ( ReturnRect ( ) );
				MonsterManager::getInstance ( ).MopReturn ( ).push_back ( newmop );
				//bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 15 );
				mop_inform.cnt = 0;

				attack_count = 0;
				status = 0;
				direct = 0;
			}
		}
		*/
		///*
		
		if ( status == 2 ) {
			if ( mop_inform.cnt == 0 ) {
				if ( length ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) ) < MONSTERLEN+100 ) {
					mop_inform.cnt = 1002;
				}
				else {
					mop_inform.cnt = rand_atk(rd_mop);
				}
			}

			if ( mop_inform.cnt>0 && mop_inform.cnt < 650 ) {
				int boom_x , boom_y;
				ATKStatus = 3; //미사일
				SoundManager::getInstance ( ).GetSoundID ( "missile2" )->ReplaySound ( );
				SoundManager::getInstance ( ).GetSoundID ( "missile1" )->ReplaySound ( );
				for ( int i = 0; i < 20; i++ ) {
					boom_x = middleX ( ReturnRect ( ) ) + rand ( ) % 2000 - 1000;
					boom_y = middleY ( ReturnRect ( ) ) + rand ( ) % 2000 - 1000;
					bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , boom_x , boom_y , 15 );
				}
				mop_inform.cnt = 1001;
			}
			else if ( mop_inform.cnt >= 650 &&mop_inform.cnt < 1000 ) {
				ATKStatus = 2; //레이저
				SoundManager::getInstance ( ).GetSoundID ( "Trim" )->ReplaySound ();
				if ( attack_count <= 2 ) {
					//2초간 탄 발사
					if ( attack_count >= 0 ) {
						bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 10 );
					}
				}
			}
			else if ( mop_inform.cnt == 1002 ) {
				ATKStatus = 1; //근접

				bulletshot ( middleX ( p1.ReturnRect ( ) ) , middleY ( p1.ReturnRect ( ) ) , middleX ( ReturnRect ( ) ) , middleY ( ReturnRect ( ) ) , 16 );
				mop_inform.cnt = 1001;
			}

			if ( attack_count >= 5 ) {
				attack_count = 0;
				mop_inform.cnt=0;
				status = 0;
				direct = 0;
			}

		}
	}
	else if ( mop_inform.type == 10 ) {// 소환몹
		if ( rect2rect ( moprect , tankrect ) ) {
			if ( random_sound ( genmop ) /5 ) {
				SoundManager::getInstance ( ).GetSoundID ( "cute" )->ReplaySound ( 0.15f );
			}
			if ( mop_inform.cnt == 0 ) {
				status = 2;
				TankController::Damage ( 30 );
				mop_inform.cnt++;
			}
		}
		if ( attack_count >= 2 ) {
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
				//attack_count = 0;
			}
			mop_inform.cnt++;
			
		}
		if ( attack_count >= 2 ) {
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
	RECTS cpyrect;	//길찾기
	
	RECTS tankRects = TankController::TankRects ( );

	
	
		
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
	monster mop_inform = this->mop_inform;

	float len = 0;
	BOOL ckBlock=0;
	if ( mop_inform.type == 6 ) {
		//여따 방향바꾸기 만드세연
		if ( p1.ReturnRect ( ).left < mop_inform.x ) {
			direct = 3;
		}
		else {
			if ( p1.ReturnRect ( ).left > mop_inform.x + 1 ) {
				direct = 0;
			}
		}
		//std::cout << "direct:" << direct << std::endl;
	}
	else if ( mop_inform.type == 1 || mop_inform.type == 4 || mop_inform.type == 10 || mop_inform.type == 11 ) {
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

	status = 0;
	/*
	if ( move_count >= 0.1 ) {
		frame++;
		if ( frame >= 6 ) frame = 0;
		move_count = 0;
	}
	move_count += Time::DeltaTime ( );
	*/

	
		
			
	

	
	if ( IntersectRect_float ( ReturnRect_T ( mop_inform ) , tankRects ) ) {//적과 플레이어 탱크 충돌

		return;

	}
	
	
	this->mop_inform.x = mop_inform.x;
	this->mop_inform.y = mop_inform.y;

}

//이동 업그레이드 버전 (개발중)
void mop::move2 ( Tank& p1 ) {
	//OSW: 속도 300 -> 100으로 수정함
	float speed = 100 * Time::DeltaTime ( );
	if ( mop_inform.type == 4 )speed *= 2;
	
	int map[ 32 ][ 32 ] = {0};
	int n = 1;
	for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
		for ( int i = ScanBlock.ReturnRect().left-n ; i < ScanBlock.ReturnRect ( ).right +n; i++ ) {
			for ( int j = ScanBlock.ReturnRect ( ).top -n; j < ScanBlock.ReturnRect ( ).bottom + n; j++ ) {
				if ( i >= 0 && i < 32 && j >= 0 && j < 32 ) {
					map[ i ][ j ] = -1;
				}
			}
		}
	}

	std::cout << "ttt" << std::endl;

	int px = (int) (middleX ( p1.ReturnRect ( ) )/64 );
	int py = (int) (middleY ( p1.ReturnRect ( ) )/64 );
	int mx = (int) (middleX ( ReturnRect ( ) )/64);
	int my = (int) (middleY ( ReturnRect ( ) )/64);

	map[ px ][ py ] = -2;
	map[ mx ][ my ] = -3;

	for ( int i = px - 1; i < px + 2; i++ ) {
		for ( int j = py - 1; j < py + 2; j++ ) {
			if ( map[ i ][ j ] == 0 ) {
				map[ i ][ j ] += 1;
			}
		}
	}

	int cnt = 2;

	//std::cout << "ttt" << std::endl;
	
	while ( 1 ) {
		for ( int i = px - cnt; i <= px + cnt; i++ ) {
			for ( int j = py - cnt; j <= py + cnt; j++ ) {
				if ( i >= 0 && i < 32 && j >= 0 && j < 32 ) {
					if ( map[ i ][ j ] == 0 ) {
						if ( ck8 ( map , i , j , cnt - 1 ) )
							map[ i ][ j ] = cnt;
					}
				}
			}
		}
		if ( ck8 ( map , mx , my , cnt ) ) {
			break;
		}
		cnt++;
	}

	//std::cout << "test:" << mx << "," << my << std::endl;


	if ( ck8_move ( map , mx , my , cnt ) ==1 ) {
		mop_inform.x += speed;
		mop_inform.y -= speed;
	}
	else if ( ck8_move ( map , mx , my , cnt ) == 2 ) {
		mop_inform.x += speed;
		mop_inform.y += speed;
	}
	else if ( ck8_move ( map , mx , my , cnt ) == 3 ) {
		mop_inform.x -= speed;
		mop_inform.y += speed;
	}
	else if ( ck8_move ( map , mx , my , cnt ) == 4 ) {
		mop_inform.x -= speed;
		mop_inform.y -= speed;
	}
	else if ( ck8_move ( map , mx , my , cnt ) == 5 ) {
		mop_inform.y -= speed;
	}
	else if ( ck8_move ( map , mx , my , cnt ) == 6 ) {
		mop_inform.x += speed;
	}
	else if ( ck8_move ( map , mx , my , cnt ) == 7 ) {
		mop_inform.y += speed;
	}
	else if ( ck8_move ( map , mx , my , cnt ) == 8 ) {
		mop_inform.x -= speed;
	}


	if ( frame >= 6 ) frame = 0;

	status = 0;

}

void mop::length_sound ( ) {
	RECTS tankrect =  TankController::TankRects ( );
	float lengthxy = length ( tankrect.right , tankrect.bottom , mop_inform.x , mop_inform.y );

	float soundM = ( 0.6f / 1599.0f ) * ( 1599.0f - lengthxy );

	
	SoundManager::getInstance ( ).GetSoundID ( "stomp3" )->ReplaySound ( soundM );
	std::cerr << soundM << std::endl;

}

void mop::Update( ){
	
	if ( status == 0 ) {
		
		status = 1;
		move ( PlayerManager::getInstance ( ).Tank_return ( ) );
		
	}
	if ( !( status == 3 || status == 4 || status == 5 ) ) {
	
		attack ( PlayerManager::getInstance ( ).Tank_return ( ) );
	}

	if ( !(status == 4 || status == 2||status==5) ) {
		if ( move_count >= 0.15 ) {

			if (( mop_inform.type == 1 || mop_inform.type == 2 || mop_inform.type == 5)&& (frame==2 || frame==5) ) {
				
				length_sound ( );
				
			}
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


		if ( sixCount >= 0.15 ) {
			sixframe++;
			if ( sixframe >= 6 ) {
				sixframe = 0;
			}
			sixCount = 0;
		}sixCount += Time::DeltaTime ( );
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
		RECTS CameraMopSize = {  mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , mop_inform.x - MOPSIZE + ( 2 * SIZE ),mop_inform.y - MOPSIZE + ( 2 * SIZE ) };
		//Rectangle ( dc , tankrect.left , tankrect.top , tankrect.right , tankrect.bottom ); //히트박스
		/*if ( TankController::camera.left>=mop_inform.x- MOPSIZE+SIZE ||
			TankController::camera.right<=mop_inform.y - MOPSIZE + SIZE ) {
			return;
		}*/

		//if (( mop_inform.x - MOPSIZE + SIZE < TankController::camera.left || mop_inform.x - MOPSIZE  > TankController::camera.right || mop_inform.y - MOPSIZE + SIZE  < TankController::camera.top || mop_inform.y - MOPSIZE > TankController::camera.bottom )) {
		//	//std::cout << "extrude" << std::endl;
		//	return;
		//}

		if ( !(IntersectRect_float(CameraMopSize, TankController::camera) ) ) {
			//std::cout << "extrude" << std::endl;
			return;
		}
		//OSW 적 가죽1
		if ( mop_inform.type == 1 ) { //기본
			//Rectangle ( dc , mop_inform.x + 30 , mop_inform.y + 20 , mop_inform.x + 190 , mop_inform.y + 220 );
			if ( status == 3 ) { //적 피격 시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_1" ) , 0, direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				SoundManager::getInstance ( ).GetSoundID ( "Hit" )->ReplaySound ( );
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
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_2" ) , 0 , 2 * 128/2 , 128/2 , 128/2 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_2" ) , die_frame * 128/2 , direct * 128/2 , 128/2 , 128/2 , RGB ( 255 , 255 , 255 ) );
				//Rectangle ( dc , 200 , 200 , 600 , 600 );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				TransparentBlt ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , SIZE , SIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_2" ) , frame * 128/2 , direct * 128/2 , 128/2 , 128/2 , RGB ( 255 , 255 , 255 ) );
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
				TransparentBlt ( dc , mop_inform.x - MOPSIZE*1 , mop_inform.y - MOPSIZE * 10 , BIGSIZE , BIGSIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_7" ) , 0 , 4 * 256 , 256 , 256 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( status == 4 ) {//적 사망시
				TransparentBlt ( dc , mop_inform.x - MOPSIZE * 1 , mop_inform.y - MOPSIZE * 10 , BIGSIZE , BIGSIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_7" ) , die_frame * 256 , 4 * 256 , 256 , 256 , RGB ( 255 , 255 , 255 ) );
				//Rectangle ( dc , 200 , 200 , 600 , 600 );
			}
			else if ( status == 5 ) {//적 사망시

			}
			else {
				if (ATKStatus != 0) { //공격모션
					TransparentBlt ( dc , mop_inform.x - MOPSIZE * 2 , mop_inform.y - MOPSIZE * 10 , BIGSIZE , BIGSIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_7" ) , sixframe * 256 , ATKStatus * 256 , 256 , 256 , RGB ( 255 , 255 , 255 ) );
				}
				else {
					TransparentBlt ( dc , mop_inform.x - MOPSIZE * 2 , mop_inform.y - MOPSIZE * 10 , BIGSIZE , BIGSIZE ,
			Texture::getInstance ( ).Texture_GetDC ( "B_Boss_7" ) , sixframe * 256 , 0 * 256 , 256 , 256 , RGB ( 255 , 255 , 255 ) );
				}
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
		
		if ( Debugging::ReturnMod ( ) )
		{
			int mopSize=0;
			HBRUSH oldBrush;
			HPEN hPen;
			HPEN oldPen;
			
			if ( mop_inform.type == 10 || mop_inform.type == 11 ) {
				mopSize = SIZE / 2;
			}
			else if ( mop_inform.type == 6 ) {
				mopSize = SIZE * 2;
			}
			else {
				mopSize = SIZE;
			}

			
			if ( status == 0 ) {
				hPen = Debugging::whitepen;
			}
			else if ( status == 1 ) {
				hPen = Debugging::yellowpen;
			}
			else if ( status == 2 ) {
				hPen = Debugging::redpen;
			}
			else if ( status == 3 ) {
				hPen = Debugging::blackpen;
			}
			else {
				hPen = Debugging::blackpen;
			}

			
			std::cerr << "적 status :" << status << std::endl;

			
			
			oldBrush=(HBRUSH)SelectObject ( dc , Debugging::NULLBRUSH );

			
			oldPen = ( HPEN ) SelectObject ( dc , hPen );

		
			Rectangle ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , mop_inform.x - MOPSIZE + mopSize , mop_inform.y - MOPSIZE + mopSize );
			
			wchar_t str[ 50 ] = L"";

			// wsprintf는 float을 처리할 수 없으므로 sprintf_s로 대체
			swprintf_s ( str , 50 , L"size %.2f %.2f %.2f %.2f" , ( float ) mop_inform.x - MOPSIZE , ( float ) mop_inform.y - MOPSIZE , ( float ) mop_inform.x - MOPSIZE + mopSize , ( float ) mop_inform.y - MOPSIZE + mopSize );

			// 문자열의 길이를 안전하게 계산하여 출력
			TextOut ( dc , mop_inform.x - MOPSIZE , mop_inform.y - MOPSIZE , str , wcsnlen_s ( str , 50 ) );
		
			swprintf_s ( str , 50 , L"mop_inform%.2f %.2f " , ( float ) mop_inform.x , ( float ) mop_inform.y  );

			TextOut ( dc , mop_inform.x , mop_inform.y , str , wcsnlen_s ( str , 50 ) );

			swprintf_s ( str , 50 , L"Returnrect %.2f %.2f %.2f %.2f " , ( float ) ReturnRect ( ).left , ( float ) ReturnRect ( ).top, ( float ) ReturnRect ( ).right, ( float ) ReturnRect ( ).bottom );

			TextOut ( dc , mop_inform.x , mop_inform.y , str , wcsnlen_s ( str , 50 ) );
			SelectObject ( dc , oldBrush );
			SelectObject ( dc , oldPen );
			
		}


}

RECTS& mop::ReturnRect ( ) {//피격범위
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

RECTS& mop::ReturnRect_T (monster mop_inform ) {//충돌
	RECTS r;
	if ( mop_inform.type == 1 ) {
		r = { mop_inform.x + 30 , mop_inform.y + 40 , mop_inform.x + 190 , mop_inform.y + 220 };
	}
	else if ( mop_inform.type == 2 ) {
		r = { mop_inform.x + 40  , mop_inform.y + 40  , mop_inform.x + 190 , mop_inform.y + 180 };	//수정1
	}
	else if ( mop_inform.type == 6 ) {
		r = { mop_inform.x , mop_inform.y + 70 , mop_inform.x + 490 , mop_inform.y + 350 };
	}
	else if ( mop_inform.type == 3 ) {
		r = { mop_inform.x , mop_inform.y + 30  , mop_inform.x + 210 , mop_inform.y + 180 };
	}
	else if ( mop_inform.type == 4 ) {
		r = { mop_inform.x + 50, mop_inform.y + 30 , mop_inform.x + 160 , mop_inform.y + 190 };
	}
	else if ( mop_inform.type == 5 ) {
		r = { mop_inform.x + 50 , mop_inform.y , mop_inform.x + 170 , mop_inform.y + 230 };
	}
	else if ( mop_inform.type == 10 || mop_inform.type == 11 ) {
		r = { mop_inform.x+10, mop_inform.y+10 , mop_inform.x + 90 , mop_inform.y + 90 };
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
