#pragma once
#include "Tank.h"
#include "MONSTER.h"
#include "BULLET.h"
#include "Player.h"

class Game
{
private:
	BulletManager bulletManager;
	MonsterManager monsterManager;
	PlayerManager playerManager;

public:
	void Update ( ) {
		bulletManager.Update ( );
		monsterManager.Update ( );
		playerManager.Update ( );
	}
	void Render (HDC mDC ) {
		bulletManager.Render (mDC );
		monsterManager.Render ( mDC );
		playerManager.Render ( mDC );
	}

	void Initailize ( HINSTANCE g_hinst ) {
		bulletManager.Initailize ( g_hinst );
		playerManager.Initailize ( g_hinst );
		monsterManager.Initailize ( g_hinst );
	}

	void Interaction_player1$controller ( ) {

	}

	void Interaction_player2$controller ( ) {

	}

	void Interaction_tank$enemy ( ) {

	}

	void Interaction_enemy$bullet ( ) {

	}
};

