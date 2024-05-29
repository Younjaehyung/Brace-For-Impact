#pragma once
#include <Windows.h>
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

public:
	Player1();
	HBITMAP B_Player_1;
	void move ( );
	void Render ( HDC , HDC );
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

public:
	Player2();
	HBITMAP B_Player_2;
	void Render ( HDC , HDC );
	void Update();
	void FixedUpdate();
	RECTS ReturnRect();
	void Init ( HINSTANCE g_hinst );
};

