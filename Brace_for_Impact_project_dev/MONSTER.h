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
#include "Tank.h"
#include "Debugging.h"
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

	float attacked_timer;
	float die_timer;
	int die_frame;

public:
	mop(int );
	
	void attack(Tank&);
	void move( Tank& );
	void move2( Tank& );
	void Update( );
	void Render( const HDC& dc);
	void length_sound ( );
	RECTS& ReturnRect ( );	//공격 범위
	RECTS& ReturnRect_T ( monster mop_inform );	//충돌방지범위
	monster& Returnmop_inform(){
		return mop_inform;
	}
	int ReturnHP ( );
	void Damage (int D);

	int status = 0; // 0: 중립상태 , 1: 이동 , 2: 공격 , 3: 데미지 , 4: 사망
	int ATKStatus = 0; //0: 1:근접 2: 레이저 3: 미사일


	//OSW 몬스터 프레임과 방향. 근데 몹이 여러 종류라서 배열로 선언 필요할듯
	int frame , direct;		//direct 0 : 좌 1: 우
	float sixCount;
	int sixframe;

	float fourCount;
	int fourframe;

};

class MonsterManager {
private:

	MonsterManager ( ) {
		count = 0;
		deletetime = 0;
	};
	std::list<mop*> mops;
	float count;
	float deletetime;
public:
	static MonsterManager& getInstance ( ) {
		static MonsterManager instance;
		return instance;
	}

	void Clear ( );
	void spawn ( int type );
	/*void SpawnMonster ( );*/
	void Initialize ( int type ) {
		spawn ( type );
	}
	void DeleteMonster ( );
	void Update ( );
	void Render ( const HDC& );
	std::list<mop*>& MopReturn();

};
