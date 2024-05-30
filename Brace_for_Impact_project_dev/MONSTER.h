#pragma once
#include <windows.h>
#include <list>
#include "Time.h"
#include "Player1.h"
#include "MATH.h"
#include <random>
#include "BULLET.h"
#include "BLOCK.h"

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
public:
	mop(int );
	
	void attack( Player1 &p1);
	void move(Player1 &p1 , Block blocks[] );
	void Update(  Player1& p1 , Block blocks[] );
	void render(HDC dc);

};

class MonsterManager {
private:
	static std::list<mop*> mops;
	
public:
	static void spone ( int type );
	static void Update ( Player1& p1 , Block blocks[] );
	static void render (HDC);
};
