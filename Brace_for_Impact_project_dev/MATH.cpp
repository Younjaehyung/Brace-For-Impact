#include"MATH.h"

float abs_F ( float i ) {
	if ( i < 0 ) return -i;
	else return i;
}

float length(int x1, int y1, int x2, int y2) {
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double angle(double x1, double y1, double x2, double y2) {
	return atan2(y1-y2,x1-x2);
}

float a2bLine ( float x , float p1x , float p1y , float mopx , float mopy ) {
	if ( p1x != mopx ) {
		return ( p1y - mopy ) / ( p1x - mopx ) * ( x - mopx ) + mopy;
	}
	else {
		return p1x;
	}
}
float a2bLine2 ( float y , float p1x , float p1y , float mopx , float mopy ) {
	if ( p1y != mopy ) {
		return ( p1x - mopx ) / ( p1y - mopy ) * ( y - mopy ) + mopx;
	}
	else {
		return p1y;
	}
}

BOOL rect2Cir ( RECTS rect ,double& x ,double& y ,int sz ) {
	if ( rect.left - sz<x && rect.right + sz>x && rect.top - sz<y && rect.bottom>y ) {
		return 1;
	}
	else {
		return 0;
	}
}

BOOL rect2Line ( RECTS rect , float& p1x , float& p1y , float& mopx , float& mopy ) {
	if ( mopx <rect.left && p1x> rect.left ) {
		if ( rect.top < a2bLine ( rect.left , p1x , p1y , mopx , mopy ) && rect.bottom > a2bLine ( rect.left , p1x , p1y , mopx , mopy ) ) {
			return 1;
		}
	}
	if ( mopx > rect.right && p1x < rect.right ) {
		if ( rect.top < a2bLine ( rect.right , p1x , p1y , mopx , mopy ) && rect.bottom > a2bLine ( rect.right , p1x , p1y , mopx , mopy ) ) {
			return 1;
		}
	}
	if ( mopy <rect.top && p1y> rect.top ) {
		if ( rect.left < a2bLine2 ( rect.top , p1x , p1y , mopx , mopy ) && rect.right > a2bLine2 ( rect.top , p1x , p1y , mopx , mopy ) ) {
			return 1;
		}
	}
	if ( mopy >rect.bottom && p1y< rect.bottom ) {
		if ( rect.left < a2bLine2 ( rect.bottom , p1x , p1y , mopx , mopy ) && rect.right > a2bLine2 ( rect.bottom , p1x , p1y , mopx , mopy ) ) {
			return 1;
		}
	}
	else {
		return 0;
	}

	return 0;
}
BOOL rect2Line4 ( RECTS rect , RECTS p1 , RECTS mop ) {
	if ( rect2Line ( rect , p1.left , p1.top , mop.left , mop.top ) ) {
		return 1;
	}
	if ( rect2Line ( rect , p1.right , p1.top , mop.right , mop.top ) ) {
		return 1;
	}
	if ( rect2Line ( rect , p1.left , p1.bottom , mop.left , mop.bottom ) ) {
		return 1;
	}
	if ( rect2Line ( rect , p1.right , p1.bottom , mop.right , mop.bottom ) ) {
		return 1;
	}
	return 0;
}

BOOL rect2rect ( RECTS block , RECTS mop ) {
	if (block.left<mop.left && block.right >mop.left && block.top<mop.top&&block.bottom>mop.top ) {
		return 1;
	}
	if ( block.left<mop.right && block.right >mop.right && block.top<mop.top && block.bottom>mop.top ) {
		return 1;
	}
	if ( block.left<mop.left && block.right >mop.left && block.top<mop.bottom && block.bottom>mop.bottom ) {
		return 1;
	}
	if ( block.left<mop.right && block.right >mop.right && block.top<mop.bottom && block.bottom>mop.bottom ) {
		return 1;
	}

	if ( mop.left<block.left && mop.right > block.left && mop.top<block.top && mop.bottom>block.top ) {
		return 1;
	}
	if ( mop.left<block.right && mop.right > block.right && mop.top<block.top && mop.bottom>block.top ) {
		return 1;
	}
	if ( mop.left<block.left && mop.right > block.left && mop.top<block.bottom && mop.bottom>block.bottom ) {
		return 1;
	}
	if ( mop.left<block.right && mop.right > block.right && mop.top<block.bottom && mop.bottom>block.bottom ) {
		return 1;
	}
	
	return 0;
}

BOOL ckMopDown ( RECTS rect , RECTS mop ) {
	if ( rect.left<mop.right && rect.right>mop.left ) {
		if ( rect.bottom < mop.top ) {
			return 1;
		}
	}
	return 0;
}
BOOL ckMopUp ( RECTS rect , RECTS mop ) {
	if ( rect.left<mop.right && rect.right>mop.left ) {
		if ( rect.top > mop.bottom ) {
			return 1;
		}
	}
	return 0;
}
BOOL ckMopLeft ( RECTS rect , RECTS mop ) {
	if ( rect.top < mop.bottom && rect.bottom > mop.top ) {
		if ( rect.left > mop.right ) {
			return 1;
		}
	}
	return 0;
}
BOOL ckMopRight ( RECTS rect , RECTS mop ) {
	if ( rect.top < mop.bottom && rect.bottom > mop.top ) {
		if ( rect.right < mop.left ) {
			return 1;
		}
	}
	return 0;
}

void bulletshot ( float x1 , float y1 , float x2 , float y2 , int type) { // 1한테로 2가 발사
	double targetx = ( double ) ( x1 );
	double targety = ( double ) ( y1 );
	double ang = angle ( ( double ) ( x2 ) , ( double ) ( y2 ) , targetx , targety );
	bullet* newbullet = new bullet ( x2 , y2 , type , -cos ( ang ) , -sin ( ang ) );
	BulletManager::getInstance ( ).CreateBullet ( newbullet );
}

bool IntersectRect_float(RECTS& rect1, RECTS& rect2){
	// rect1이 rect2의 오른쪽에 있는지 확인
	if (rect1.right < rect2.left)
		return false;

	// rect1이 rect2의 왼쪽에 있는지 확인
	if (rect1.left > rect2.right)
		return false;

	// rect1이 rect2의 아래에 있는지 확인
	if (rect1.bottom < rect2.top)
		return false;

	// rect1이 rect2의 위에 있는지 확인
	if (rect1.top > rect2.bottom)
		return false;

	// 위의 모든 조건을 만족하지 않으면 두 사각형이 겹침
	return true;


}


bool PtinRect_float(const RECTS& rect, const POINT& point) {
	return (rect.left<point.x && rect.right>point.x && rect.bottom > point.y && rect.top < point.y);

}

RECTS float_return(const int& left, const int& top, const int& right, const int& bottom) {
	RECTS return_rects = { static_cast<float> (left), static_cast<float> (top), static_cast<float>(right), static_cast<float>(bottom) };
	return return_rects;
}

double Radian_return (float& angle ) {

	return angle * PI / 180.0;
}