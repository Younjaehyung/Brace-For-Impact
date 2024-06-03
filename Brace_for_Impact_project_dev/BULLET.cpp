#include "BULLET.h"
#include "MATH.h"
#include <random>
#include"BLOCK.h"
#include "Player.h"
#include"MONSTER.h"

#define SIZE 20


bullet::bullet ( double dx, double dy, int dtype, double dmx, double dmy)
:x(dx),y(dy),mx(dmx),my(dmy),type(dtype){
	// 0: 삭제   1~9: 플레이어용   10~:몬스터용 

}



void bullet::move ( ) {
	
		x += mx *600 * Time::DeltaTime ( );
		y += my * 600 * Time::DeltaTime ( );

		if ( x < 0 || y < 0 ) {
			type = 0;
		}
		//벽에 탄 맞음
		for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
			if ( rect2Cir ( ScanBlock.ReturnRect ( ) , x , y , SIZE ) ) {
				type = 0;
			}
		}
		//몬스터가 탄 맞음
		if ( type < 10 ) {
			for ( auto& ScanMop : MonsterManager::getInstance ( ).MopReturn ( ) ) {
				if ( rect2Cir ( ScanMop->ReturnRect ( ) , x , y , SIZE ) ) {
					type = 0;
				}
			}
		}
		//플레이어(탱크)가 탄 맞음
		RECTS tankrect = PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( );
		tankrect.bottom = tankrect.top + 192;
		tankrect.right = tankrect.left + 192;
		if ( rect2Cir ( tankrect , x , y , SIZE ) ) {
			type = 0;
		}
	
}
void bullet::Render ( const HDC& dc ) {
	if ( type != 0 ) {
		Ellipse ( dc , x - SIZE , y - SIZE , x + SIZE , y + SIZE );
	}
}

void bullet::Update ( ) {
	move ( );

}

void BulletManager::CreateBullet (bullet*& newbullet ) {
	
		bullets.push_back ( newbullet );

}

void BulletManager::DeleteBullet() {
	

	for ( auto iter : bullets ) {
		if ( iter->return_type ( ) == 0 ) {

		}
	}
	

}

void BulletManager::Update() {
	for ( auto iter : bullets) {
		iter->Update ( );
	}

}


void BulletManager::Render( const HDC& dc) {
	for ( auto iter : bullets ) {
		iter->Render (dc );
	}
}


