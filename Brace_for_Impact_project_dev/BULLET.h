#pragma once
#include <windows.h>
#include "Player1.h"


struct bullet{
	double x;
	double y;
	double mx;
	double my;
	int type;
	BOOL PlayerBullet;
	bullet* next;
};

class bulletmanager {
public:
	bulletmanager();
	void move(bullet*& hd);
	void rander(HDC dc, bullet*&hd);
};

