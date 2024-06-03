#pragma once
#include "Time.h"

typedef struct Frame {
	int frame;
	float count;
}Frame;

class TankController
{
private:
	static int tankmove;
	static int tankaiming;

	//OSW 스테이지프레임, 대포 프레임, 대포 타이머
	static Frame Stage_frame , Cannon_frame , Inside_frame;

	static int tankhp;
	static int tankoil;
	static float tankoilcount;
public:
	static int& TankMoveStatus ( ) {
		return tankmove;
	}
	static int& TankAimingStatus ( ) {
		return tankaiming;
	}
	static Frame& TankStage_frame ( ) {
		return Stage_frame;
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
	static void Damage (int damage) {
		if (tankhp > 0 ) {
			tankhp -= damage;
		}
	}
	static void TankOilCount ( ) {
		if ( tankoilcount >= 1 ) {
			tankoil -= 1;
			tankoilcount = 0;
		}
		tankoilcount += 5 * Time::DeltaTime ( );
	}
};
