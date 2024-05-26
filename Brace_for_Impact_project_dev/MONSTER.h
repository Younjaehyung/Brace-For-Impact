#pragma once
#include <windows.h>

#include "Player1.h"

struct monster {
	float x;
	float y;
	int hp;
	int cnt;
	int type;
	monster* next;
};

class mop{
private:
	monster mop_inform;
	
public:
	mop();
	
	void attack( Player1 &p1);
	void move(Player1 &p1);
	void Update(  Player1& p1);
	void render(HDC dc);

};

class monster_manager {
private:
	std::list<mop*> mops;
public:
	static monster* spone ( int type );
	void Update ( Player1& p1 );
	void render (HDC );
};
