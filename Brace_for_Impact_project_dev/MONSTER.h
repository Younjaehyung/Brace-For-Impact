#pragma once
#include <windows.h>
#include "Player1.h"
#include "BULLET.h"

struct monster {
	float x;
	float y;
	int hp;
	int cnt;
	int type;
	monster* next;
};

class mop{
public:
	mop();
	void spone(monster*& hd, int type);
	void attack(monster*& mophd, bullet*& bullethd , Player1 &p1);
	void move(monster*& hd , Player1 &p1);
	void f_Update(monster*& mophd, bullet*& bullethd, Player1& p1);
	void rander(HDC dc, monster*& hd);

};
