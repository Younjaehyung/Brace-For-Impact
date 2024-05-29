#pragma once
#include "Player1.h"
#include "BULLET.h"
#include "MATH.h"
#include "Resource.h"
class Tank : public Player1
{

private:
	RECTS rect;
	HBITMAP B_Tank_car , B_Tank_head;
	int Tank_head_frame, Tank_car_frame;
	int Tank_car_direct, Tank_head_direct;		//0: 12시방향 1: 2시방향 2: 3시방향 3: 5시방향 4: 6시방향 6: 7시방향 7: 9시방향 8: 11시 방향
	int Tk_c_status;
	float Tank_car_count;
	float Tank_head_count;
	float angle;
	float frameInterval;
	BOOL isMove;			//탱크가 움직이고 있지 않으면 FRAME 0으로 만들 목적
	BOOL headMove;
	BOOL headArrow;
public:
	Tank ( );
	void move ( );
	void shooting ( );
	void moving_rander_cal ( );
	void aiming();
	void aiming_animation ( );
	void Init ( HINSTANCE g_hinst );
	void Update ( );
	void render ( HDC , HDC );

};

