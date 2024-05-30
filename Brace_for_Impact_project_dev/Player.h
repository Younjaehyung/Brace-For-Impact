#pragma once
#include "Player1.h"
#include "Tank.h"


class PlayerManager {
private:
	Player1 player1;
	Player2 player2;
	Tank tank;
public:
	void Update ( ) {
		player1.Update ( );
		player2.Update ( );
		tank.Update ( );
	}
	void Render (HDC mDC ) {
		player1.Render (mDC );
		player2.Render ( mDC );
		tank.Render ( mDC );
	}
	void Initailize (HINSTANCE ) {

	}
};