#pragma once
#include <Windows.h>
#include "Texture.h"
#include "input.h"
#include "Time.h"
#include "MATH.h"
#include "Resource.h"
#include "TankController.h"
#include "Tank.h"
//#include "Player.h"
#define PLAYERSIZE 96

class Player1
{

private:
	RECTS rect;
	float count;
	int status;
	int frame , direct;		//direct 0 : 좌 1: 우

	RECTS p1Rect;

public:

	Player1 ( );
	void Clear ( );
	void move ( );
	void SwitchStatus ( );
	void Initialize (  );
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

	

public:
	Player2();
	void Clear ( );
	void move ( );
	void SwitchStatus ( );
	void Initialize (  );
	void Render ( const HDC& );
	void Update();
	void FixedUpdate();
	RECTS ReturnRect();
};

