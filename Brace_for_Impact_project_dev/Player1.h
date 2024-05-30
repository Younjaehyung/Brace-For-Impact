#pragma once
#include <Windows.h>
#include "Texture.h"
#include "input.h"
#include "Time.h"
#include "MATH.h"
#include "Resource.h"

class Player1
{

private:
	RECTS rect;
	double count;
	int frame , direct;		//direct 0 : 좌 1: 우
	bool tank_status;
	HBITMAP* B_Player_1;
	HDC hmemDC;
public:
	Player1();
	
	void move ( );
	//void tank_control ( );
	void Render ( HDC );
	void Update();
	void FixedUpdate();
	RECTS ReturnRect();
	void Init ( HINSTANCE g_hinst );
};

class Player2
{

private:
	RECTS rect;
	double count;
	int frame , direct;		//direct 0 : 좌 1: 우
	bool tank_status;
	HBITMAP B_Player_2;
	HDC hmemDC;
public:
	Player2();
	
	//void tank_control ( );
	void Render ( HDC );
	void Update();
	void FixedUpdate();
	RECTS ReturnRect();
	void Init ( HINSTANCE g_hinst );
};

