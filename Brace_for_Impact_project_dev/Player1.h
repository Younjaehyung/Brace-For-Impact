#pragma once
#include <Windows.h>
#include "Texture.h"
#include "input.h"
#include "Time.h"
#include "MATH.h"
#include "Resource.h"
#include "TankController.h"
#define PLAYERSIZE 96

class Player1
{

private:
	RECTS rect;
	float count;
	int status;
	int frame , direct;		//direct 0 : 좌 1: 우
	bool tank_status;
	HBITMAP* B_Player_1;
	HDC hmemDC;

	RECTS p1Rect;

public:

	Player1 ( );
	
	void move ( );
	void SwitchStatus ( );
	void Tank_control ( );
	void Render ( const HDC& );
	void Update();
	void FixedUpdate();
	RECTS ReturnRect();
	
};

class Player2
{

private:
	RECTS rect;
	float count;
	int status;
	int frame , direct;		//direct 0 : 좌 1: 우
	bool tank_status;
	HBITMAP B_Player_2;
	HDC hmemDC;

	

public:
	Player2();
	void move ( );
	//void tank_control ( );
	void SwitchStatus ( );
	void Render ( const HDC& );
	void Update();
	void FixedUpdate();
	RECTS ReturnRect();
	void Init ( HINSTANCE g_hinst );
};

