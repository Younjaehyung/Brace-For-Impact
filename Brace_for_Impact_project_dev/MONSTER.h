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
public:
	mop();
	void spone(monster*& hd, int type);
	void move(monster*& hd , Player1 &p1);
	void rander(HDC dc, monster*& hd);

};
