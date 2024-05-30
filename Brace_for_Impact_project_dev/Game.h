#pragma once
#include "MONSTER.h"
#include "BULLET.h"
#include "Player.h"

class Game
{
private:
	HDC hmemDC;

public:
	Game::Game (HDC DC) {
		
	}

	void Update ( ) {
		BulletManager::Update ( );
		MonsterManager::Update ( );
		PlayerManager::Update ( );
	}
	void Render (HDC mDC ) {
		BulletManager::Render (mDC );
		MonsterManager::Render ( mDC );
		PlayerManager::Render ( mDC );
	}

	void Initailize ( HINSTANCE g_hinst ) {
		BulletManager::Initailize ( g_hinst );
		MonsterManager::Initailize ( g_hinst );
		PlayerManager::Initailize ( g_hinst );
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

