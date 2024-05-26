#include "BULLET.h"
#include "MATH.h"
#include <random>


bullet::bullet ( double dx, double dy, double dmx, double dmy, int dtype)
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
void bulletmanager::CreateBullet (Player1& p1,monster& m1,int type ) {
	if ( type == 1 ) {

	}
	else if ( type == 2 ) {
		
		
		double targetx = ( double ) ( p1.ReturnRect ( ).left + 20 );
		double targety = ( double ) ( p1.ReturnRect ( ).top + 20 );
		double ang = angle ( ( double ) ( m1.x ) , ( double ) ( m1.y ) , targetx , targety );
		bullet* newbullet = new bullet( m1.x , m1.y ,10, -cos ( ang ) , -sin ( ang ) );
		bullets.push_back ( newbullet );
	}
}

//void bulletmanager::DeleteBullet() {
//	
//		
//	for ( auto iter : bullets ) {
//		if ( iter->type == 0 ) {
//			
//			delete temp1;
//			temp1 = hd;
//			temp2 = hd;
//		}
//		else {
//			temp1 = temp1->next;
//			if ( temp1 == NULL ) {
//				break;
//			}
//			if ( temp1->type == 0 ) {
//				temp2->next = temp1->next;
//				delete temp1;
//				temp1 = temp2;
//			}
//			else {
//				temp2 = temp1;
//			}
//		}
//	}
//	
//
//}

void bulletmanager::Update() {
	for ( auto iter : bullets) {
		iter->Update ( );
	}
}


void bulletmanager::rander(HDC dc) {
	for ( auto iter : bullets ) {
		iter->rander ( );
	}
}


