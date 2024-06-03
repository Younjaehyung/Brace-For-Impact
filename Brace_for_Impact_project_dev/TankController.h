#pragma once
class TankController
{
private:
	static int tankmove;
	static int tankaiming;



public:
	static int& TankMoveStatus ( ) {
		return tankmove;
	}
	static int& TankAimingStatus ( ) {
		return tankaiming;
	}

};
