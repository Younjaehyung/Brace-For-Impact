#pragma once
#include <windows.h>
#include <list>
#include "Texture.h"
#include "Time.h"
#include "Player.h"
#include "MATH.h"
#include <random>
#include "BULLET.h"

typedef struct monster {
	float x;
	float y;
	int hp;
	int cnt;
	int type;
}monster;

class mop{
private:
	monster mop_inform;
	float attack_count;
	HBITMAP* hBitmap;
public:
	mop(int );
	
	void attack(Tank&);
	void move( Tank& );
	void Update( );
	void Render( const HDC& dc);

};

class MonsterManager {
private:

	MonsterManager ( ) {
		count = 0;
	};
	std::list<mop*> mops;
	float count;
public:
	static MonsterManager& getInstance ( ) {
		static MonsterManager instance;
		return instance;
	}

	void spawn ( int type );

	void Update ( );
	void Render ( const HDC& );
};
