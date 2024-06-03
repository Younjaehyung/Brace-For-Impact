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

	
};
