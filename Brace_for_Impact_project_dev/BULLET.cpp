#include "BULLET.h"
#include "MATH.h"
#include <random>
#include"BLOCK.h"

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
		for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
			if ( rect2Cir ( ScanBlock.ReturnRect ( ) , x , y , SIZE ) ) {
				type = 0;
			}
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


