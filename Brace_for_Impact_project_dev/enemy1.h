#pragma once
#include <windows.h>
#include "GameObject.h"
#include "Player1.h"
#include "MATH.h"
class enemy1:public GameObject
{
private:
	
	int count;
	int type;

public:
	enemy1();
	void f_moving(Player1& player);
	void f_attack();
	void Update(Player1& player1);
	void Render(HDC) override;
	void f_FixedUpdate();
	void Initialize(int tp) ;
	void f_crash(enemy1& otherenemy);
};



