#pragma once
#include "Player1.h"
#include "Tank.h"


class PlayerManager {
private:
	static Player1 player1;
	static Player2 player2;
	static Tank tank;
public:
	static void Update ( ) {
		player1.Update ( );
		player2.Update ( );
		tank.Update ( );
	}
	static void Render (HDC mDC ) {
		player1.Render (mDC );
		player2.Render ( mDC );
		tank.Render ( mDC );
	}
	static void Initailize (HINSTANCE ) {

	}
	static Player1* Player1_return ( ) {
		return &player1;
	}
	static Player2* Player2_return ( ) {
		return &player2;
	}
	static Tank* Tank_return ( ) {
		return &tank;
	}
};