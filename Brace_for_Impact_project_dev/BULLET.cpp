#include "BULLET.h"
#include "MATH.h"
#include <random>
std::list<bullet*> bulletmanager::bullets;


bullet::bullet ( double dx, double dy, int dtype, double dmx, double dmy)
:x(dx),y(dy),mx(dmx),my(dmy),type(dtype){
	// 0: 삭제   1~9: 플레이어용   10~:몬스터용 

}

void bullet::move ( ) {
	
		x += mx;
		y += my;

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



bulletmanager::bulletmanager ( ) {

}
void bulletmanager::CreateBullet (bullet*& newbullet ) {
	
		bullets.push_back ( newbullet );

}

void bulletmanager::DeleteBullet() {
	
	

	//map 나가면 status ==0 
	for ( auto iter : bullets ) {
		
	}
	

}

void bulletmanager::Update() {
	for ( auto iter : bullets) {
		iter->Update ( );
	}
}


void bulletmanager::rander(HDC dc) {
	for ( auto iter : bullets ) {
		iter->rander (dc );
	}
}


