#pragma once
#include "Player1.h"
#include "Tank.h"



class PlayerManager {
private:
	PlayerManager ( ) {};

	Player1 player1;
	Player2 player2;
	Tank tank;

	
public:

	static PlayerManager& getInstance ( ) {
		static PlayerManager instance;
		return instance;
	}

	void Update ( ) {
		player1.Update ( );
		player2.Update ( );
		tank.Update ( );
		
	}
	void Render ( const HDC& mDC ,const HDC& orimDC ) {
		player1.Render ( orimDC );
		player2.Render ( orimDC );
		tank.Render ( mDC );

	}
	void Clear ( ) {
		tank.Clear ( );
		player1.Clear ( );
		player2.Clear ( );
	}

	void Initialize (int type ) {
		tank.Initialize ( type );
		player1.Initialize ( );
		player2.Initialize ( );
	}
	Player1& Player1_return ( ) {
		return player1;
	}
	Player2& Player2_return ( ) {
		return player2;
	}
	Tank& Tank_return ( ) {
		return tank;
	}
};