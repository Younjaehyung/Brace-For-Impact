#pragma once
#include "Time.h"
#include "CommonInclude.h"
typedef struct Frame {
	int frame;
	float count;
}Frame;

class TankController
{
private:
	static bool tankmove;
	static bool tankaiming;
	static bool dash;
	//OSW 스테이지프레임, 대포 프레임, 대포 타이머
	static Frame Stage_frame , Cannon_frame , Inside_frame, Title_frame;
	static RECTS TankRect;
	static int tankhp;
	static int tankoil;
	static int tankbullet;
	static float tankoilcount;
public:
	static RECT camera;

	static bool& TankMoveStatus ( ) {
		return tankmove;
	}
	static bool& TankAimingStatus ( ) {
		return tankaiming;
	}
	static bool& Dash ( ) {
		return dash;
	}
	static Frame& TankStage_frame ( ) {
		return Stage_frame;
	}
	static Frame& ScreenTitle_frame ( ) {
		return Title_frame;
	}
	static Frame& TankCannon_frame ( ) {
		return Cannon_frame;
	}
	static int& TankHp ( ) {
		return tankhp;
	}
	static int& TankOil ( ) {
		return tankoil;
	}
	static int& TankBullet ( ) {
		return tankbullet;
	}
	static void Damage (int damage) {
		if (tankhp > 0 ) {
			tankhp -= damage;
			if ( tankhp < 0 ) {
				tankhp = 0;
			}
		}
	}
	static RECTS& TankRects ( ) {
		return TankRect;
	}
	static void TankOilCount ( ) {
		if ( tankoilcount >= 1 ) {
			tankoil -= 1;
			tankoilcount = 0;
		}
		if ( tankoil > 0 ) {
			tankoilcount += 5 * Time::DeltaTime ( );
		}
	}
};
