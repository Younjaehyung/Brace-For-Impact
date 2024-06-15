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
	HBRUSH cyanBrush;

public:
	Game ( ) :score(0) {
		
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
		BlockManager::getInstance ( ).Initialize(1);
		
	}

	void Clear ( ) {
		MonsterManager::getInstance ( ).Clear ( );
		PlayerManager::getInstance ( ).Clear ( );
		BlockManager::getInstance ( ).Clear ( );
	}


};

