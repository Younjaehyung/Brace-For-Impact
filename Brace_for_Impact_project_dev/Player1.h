#pragma once
#include <Windows.h>
#include "Texture.h"
#include "input.h"
#include "Time.h"
#include "MATH.h"
#include "Resource.h"
#include "TankController.h"
#include "Tank.h"

#define PLAYERSIZE 96

class Player1
{

private:
	RECTS rect;
	float count;
	int status;
	int frame , direct;		//direct 0 : 좌 1: 우

	RECTS object1 = { 248, 200 , 400 , 400 };
	bool Ismove , IsAiming;
	int itemtype;

	RECTS p1Rect;
	BOOL isHold; //아이템을 뭐라도 들고 있을 때
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
	int Controller;
	RECTS object1 = { 248, 200 , 400 , 400 };
	bool Ismove , IsAiming;
	int itemtype;
	BOOL isHold; //아이템을 뭐라도 들고 있을 때

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

