#pragma once
#include "Texture.h"
#include "Sound.h"
#include "TankController.h"
#include "Player1.h"
#include "BULLET.h"
#include "MATH.h"
#include "Resource.h"
#include "BLOCK.h"
#include "Windows.h"

class MonsterManager;

class Tank 
{

private:
	
	RECTS rect;
	int Tank_head_frame, Tank_car_frame;
	int Tank_car_direct, Tank_head_direct;		//0: 12시방향 1: 2시방향 2: 3시방향 3: 5시방향 4: 6시방향 6: 7시방향 7: 9시방향 8: 11시 방향
	int Tk_c_status;
	float angle;
	float dashcnt;
	int dashcnt2;
	
	float CannonInterval;
	//OSW
	float Tank_car_count;
	float Tank_head_count;
	float frameInterval;
	float shootingInterval;
	int fireInterval;
	
	BOOL isMove;			//탱크가 움직이고 있지 않으면 FRAME 0으로 만들 목적
	BOOL headMove;
	BOOL headArrow;
	

	BOOL UnDieing;
	BOOL OILMODE;
	//탱크 피격 이미지
	int Hitframe;
	float HitTimer;
	float HitCounter;
public:
	
	Tank ( );
	HBRUSH blackBrush;

	void move ( );
	void shooting ( );
	void moving_rander_cal ( );
	void aiming();
	void aiming_animation ( );
	void Clear ( );

	void Initialize (int);

	RECTS& ReturnRect ( ) {
	
		return rect;
		
	}
	BOOL& ReturnUndieing ( ) {
		return UnDieing;
	}

	BOOL& ReturnOILMode ( ) {
		return OILMODE;
	}

	BOOL& ReturnIsmove ( ) {
		return isMove;
	}

	void Damage ( int damage );

	void Update ( );
	void Render ( const HDC & );

	void sound ( );
};

