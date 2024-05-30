#pragma once
#include <windows.h>
#include <list>
#include "Time.h"
#include "Player1.h"
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
public:
	mop(int );
	
	void attack( Player1 &p1);
	void move(Player1 &p1);
	void Update(  Player1& p1);
	void render(HDC dc);

};

class MonsterManager {
private:
	std::list<mop*> mops;
	HBITMAP Monster1 , Monster2 , Monster3,Monster4;


public:

	void spone ( int type );
	void Initailize (HINSTANCE );
	void Update ( Player1& p1 );
	void Render (HDC);
};
