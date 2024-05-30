#pragma once
#include "MONSTER.h"
#include "BULLET.h"
#include "Player.h"

class Game
{
private:
	int score;
public:
	Game ( ) :score(0) {
		
	}

	void Update ( ) {

		BulletManager::getInstance ( ).Update ( );
		MonsterManager::getInstance ( ).Update ( );
		PlayerManager::getInstance ( ).Update ( );
	}
	void Render ( const HDC& mDC ) {
		BulletManager::getInstance ( ).Render ( mDC );
		MonsterManager::getInstance ( ).Render ( mDC );
		PlayerManager::getInstance ( ).Render ( mDC );
	}

	void Initailize ( HDC mDC,HINSTANCE g_hinst ) {
		Texture::getInstance ( ).Texture_Loading ( mDC , g_hinst );
		BulletManager::getInstance ( );
		MonsterManager::getInstance ( );
		PlayerManager::getInstance ( );
		
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

