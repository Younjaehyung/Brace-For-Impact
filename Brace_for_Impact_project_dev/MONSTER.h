#pragma once
#include <windows.h>
#include <list>
#include "Texture.h"
#include "Time.h"
#include "Player.h"
#include "MATH.h"
#include <random>
#include "BULLET.h"
#include"BLOCK.h"

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
	float move_count;
	float attack_count;
	HBITMAP* hBitmap;
public:
	mop(int );
	
	void attack(Tank&);
	void move( Tank& );
	void Update( );
	void Render( const HDC& dc);
	RECTS ReturnRect ( );

	//OSW 몬스터 프레임과 방향. 근데 몹이 여러 종류라서 배열로 선언 필요할듯
	int frame , direct;		//direct 0 : 좌 1: 우

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
	std::list<mop*>& MopReturn();

};
