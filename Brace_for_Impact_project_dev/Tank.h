#pragma once
#include "Texture.h"
#include "Player1.h"
#include "BULLET.h"
#include "MATH.h"
#include "Resource.h"
class Tank 
{

private:
	
	RECTS rect;
	HBITMAP* bitmap;
	int Tank_head_frame, Tank_car_frame;
	int Tank_car_direct, Tank_head_direct;		//0: 12시방향 1: 2시방향 2: 3시방향 3: 5시방향 4: 6시방향 6: 7시방향 7: 9시방향 8: 11시 방향
	int Tk_c_status;
	float angle;
	//OSW 스테이지프레임, 대포 프레임, 대포 타이머
	int Stage_frame, Cannon_frame, Inside_frame;
	float CannonInterval;
	//OSW
	float Tank_car_count;
	float Tank_head_count;
	float frameInterval;
	float shootingInterval;
	int HP;
	int OIL;
	float OILcount = 0;
	
	BOOL isMove;			//탱크가 움직이고 있지 않으면 FRAME 0으로 만들 목적
	BOOL headMove;
	BOOL headArrow;
 
public:
	
	Tank ( );
	HBRUSH blackBrush;

	void move ( );
	void shooting ( );
	void moving_rander_cal ( );
	void aiming();
	void aiming_animation ( );
	
	RECTS& ReturnRect ( ) {
		return rect;
	}
	int ReturnHP ( );
	void Damage ( int damage );
	int ReturnOIL ( );
	void OILDown();

	void Update ( );
	void Render ( const HDC& );

};

