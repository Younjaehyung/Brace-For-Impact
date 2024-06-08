#include "BULLET.h"
#include "MATH.h"
#include <random>
#include"BLOCK.h"
#include "Player.h"
#include"MONSTER.h"

#define SIZE 20


bullet::bullet ( double dx, double dy, int dtype, double dmx, double dmy)
:x(dx),y(dy),mx(dmx),my(dmy),type(dtype){
	if ( dtype > 0 && dtype < 10 ) PlayerBullet = 1;
	// 0: 삭제   1~9: 플레이어용   10~:몬스터용 
	//10: 기본탄 1 데미지
	//11: 강력탄 10 데미지
	//12: 분열탄 맞을 시 8방향으로 나뉨
	//13: 회전탄 회전하면서 날아감
	//14: 충격파 제자리에서 점점 커짐
	//15: 
}



void bullet::move ( ) {
	
	if ( type != 14 ) {
		x += mx * 600 * Time::DeltaTime ( );
		y += my * 600 * Time::DeltaTime ( );
	}
	else {
		counter += 100 * Time::DeltaTime ( );
	}
		//OSW
		//총알 프레임
		if ( timer1 > 0.3 ) {
			frame++;
			if ( frame >= 3 ) frame = 0;
			timer1 = 0;
		}timer1 += Time::DeltaTime ( );
		// 
		//

		if ( x < 0 || y < 0 ) {
			type = 0;
		}
		if ( type > 0 ) {
			//벽에 탄 맞음
			for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
				if ( rect2Cir ( ScanBlock.ReturnRect ( ) , x , y , SIZE ) ) {
					if ( type == 12 ) {
						double angle1 = 45 * ( 3.141592 / 180 );
						for ( int i = 0; i < 8; i++ ) {
							bullet* newbullet = new bullet ( x , y , 10 , -cos ( i * angle1 ) , -sin ( i * angle1 ) );
							BulletManager::getInstance ( ).CreateBullet ( newbullet );
						}
					}
					type = 0;
				}
			}

			//몬스터가 탄 맞음
			if ( PlayerBullet ) {
				for ( auto& ScanMop : MonsterManager::getInstance ( ).MopReturn ( ) ) {
					if ( rect2Cir ( ScanMop->ReturnRect ( ) , x , y , SIZE ) && ScanMop->ReturnHP ( ) > 0 ) {

						type = 0;
						ScanMop->Damage ( 1 );
					}
				}
			}
			if ( !PlayerBullet ) {
				//플레이어(탱크)가 탄 맞음
				RECTS tankrect = PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( );
				if ( type == 14 ) {
					if ( counter >= 300 ) {
						if ( rect2Cir ( tankrect , x , y , SIZE + counter ) && TankController::TankHp ( ) > 0 ) {
							TankController::Damage ( 50 );
						}
						type = 0;
					}
				}
				else {
					if ( rect2Cir ( tankrect , x , y , SIZE ) && TankController::TankHp ( ) > 0 ) {
						if ( type == 10 ) {
							TankController::Damage ( 1 );
						}
						else if ( type == 11 ) {
							TankController::Damage ( 10 );
						}
						else if ( type == 12 ) {
							TankController::Damage ( 1 );
							double angle1 = 45 * ( 3.141592 / 180 );
							for ( int i = 0; i < 8; i++ ) {
								bullet* newbullet = new bullet ( x , y , 10 , -cos ( i * angle1 + angle1 / 2 ) , -sin ( i * angle1 + angle1 / 2 ) );
								BulletManager::getInstance ( ).CreateBullet ( newbullet );
							}
						}
						type = 0;
					}
				}
			}
		}
	
}
void bullet::Render ( const HDC& dc ) {
	if ( type != 0 ) {
		if ( PlayerBullet ) { //플레이어가 쏜 총알
			TransparentBlt ( dc , x - 4 * SIZE , y - 4 * SIZE , SIZE * 8 , SIZE * 8 ,
				Texture::getInstance ( ).Texture_GetDC ( "B_Bullet_2" ) , frame * 64 , 1 * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
			Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
		}
		else { // 몬스터가 쏜 총알
			if ( type == 14 ) { // 자폭이 폭발		
				Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
			}
			else { //그 외 다른애들 총알
				Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
			}
		}
	}
}

void bullet::Update ( ) {
	move ( );

}

void BulletManager::CreateBullet (bullet*& newbullet ) {

		bullets.push_back ( newbullet );
	
}

void BulletManager::DeleteBullet() {
	if ( bullets.size()  ) {
		 deletetime += Time::DeltaTime ( );
		if ( deletetime > 10.0 ) {
			

				for ( auto iter = bullets.begin ( ); iter != bullets.end ( );) {
					if ( ( *iter )->return_type ( ) == 0 ) {  // 반복자가 가리키는 객체에 접근하기 위해 *iter 사용
						bullet* del = *iter;  // 삭제할 노드의 포인터를 저장
						iter = bullets.erase ( iter );  // 삭제한 노드의 다음 노드의 반복자를 반환
					
						delete del;  // 삭제할 노드를 메모리에서 해제

						std::cout << "aa" << std::endl;
					}
					else {
						++iter;  // 다음 노드로 이동
					}
				}
				deletetime = 0;
		}
		

	}
	

}

void BulletManager::Update() {
	for ( auto& iter : bullets) {
		iter->Update ( );
	}
	DeleteBullet ( );
	
}


void BulletManager::Render( const HDC& dc) {
	for ( auto& iter : bullets ) {
		iter->Render (dc );
	}
}


