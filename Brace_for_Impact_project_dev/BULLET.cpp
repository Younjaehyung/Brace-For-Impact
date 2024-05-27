#include "BULLET.h"
#include "MATH.h"
#include <random>
std::list<bullet*> BulletManager::bullets;


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

	
}
void bullet::rander ( HDC dc ) {

	Ellipse ( dc , x - 5 , y - 5 , x + 5 , y + 5 );

}

void bullet::Update ( ) {
	move ( );

}



BulletManager::BulletManager ( ) {

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


void BulletManager::rander(HDC dc) {
	for ( auto iter : bullets ) {
		iter->rander (dc );
	}
}


