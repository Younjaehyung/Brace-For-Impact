#pragma once
#include <windows.h>
#include "Player1.h"
class enemy1
{
private:
	RECT rect;
	int count;

public:
	enemy1();
	void f_moving(Player1& player);
	void f_attack();
	void f_Update(Player1& player1);
	void f_Render(HDC);
	void f_FixedUpdate();
	void f_init();
	void f_crash(enemy1& otherenemy);
};

