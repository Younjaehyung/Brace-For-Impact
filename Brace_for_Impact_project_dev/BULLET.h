#pragma once
#include <windows.h>
#include "Player1.h"


struct bullet{
	double x;
	double y;
	double mx;
	double my;
	int type; // 0: 삭제   1~9: 플레이어용   10~:몬스터용
	BOOL PlayerBullet;
	bullet* next;
};

class bulletmanager {
public:
	bulletmanager();
	void move(bullet*& hd);
	void rander(HDC dc, bullet*&hd);
	void deleteBullet(bullet*& hd);
	void f_Updte(bullet*& hd);
};

