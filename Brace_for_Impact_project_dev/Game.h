#pragma once
#include "MONSTER.h"
#include "BULLET.h"
#include "Player.h"
#include"BLOCK.h"

class Game
{
private:
	int score;
	HBRUSH blackBrush;
	HBRUSH redBrush;
	

public:
	Game ( ) :score(0) {
		blackBrush = CreateSolidBrush ( RGB ( 20 , 20 , 20 ) );
		redBrush = CreateSolidBrush ( RGB ( 200 , 50 , 50 ) );
	}

	void Update ( ) {

		BulletManager::getInstance ( ).Update ( );
		MonsterManager::getInstance ( ).Update ( );
		PlayerManager::getInstance ( ).Update ( );
	}
	void Render ( const HDC& mDC,const HDC& orimDC ) {
		BulletManager::getInstance ( ).Render ( mDC );
		MonsterManager::getInstance ( ).Render ( mDC );
		PlayerManager::getInstance ( ).Render ( mDC, orimDC );
		BlockManager::getInstance ( ).Render ( mDC );
	}

	void Initailize ( HDC mDC,HINSTANCE g_hinst ) {
		Texture::getInstance ( ).Texture_Loading ( mDC , g_hinst );
		BulletManager::getInstance ( );
		MonsterManager::getInstance ( );
		PlayerManager::getInstance ( );
		BlockManager::getInstance ( ).Initilize(3);
		
	}

	void Camera_UI ( const HDC& mDC );
	
	void Interaction_player1$controller ( ) {

	}

	void Interaction_player2$controller ( ) {

	}

	void Interaction_tank$enemy ( ) {

	}

	void Interaction_enemy$bullet ( ) {

	}
};

