#pragma once
#include <windows.h>
#include <list>
#include "Texture.h"
#include "Time.h"
#include "Player.h"
#include "Tank.h"
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
	
	void attack(Tank*);
	void move( Tank* );
	void Update( );
	void render(HDC dc);

};

class MonsterManager {
private:
	static std::list<mop*> mops;
	

public:

	static void spone ( int type );
	static void Initailize (HINSTANCE ,HDC);
	static void Update ( );
	static void Render (HDC);
};
