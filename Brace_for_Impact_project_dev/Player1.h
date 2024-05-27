#pragma once
#include <Windows.h>
#include "input.h"
#include "Time.h"
#include "MATH.h"


class Player1
{

private:
	RECTS rect;
	int count = 0;
	

public:
	Player1();
	void move ( );
	void Render(HDC mDC);
	void Update();
	void FixedUpdate();
	RECTS ReturnRect();
};

class Player2
{

private:
	RECTS rect;
	int count = 0;


public:
	Player2();
	void Render(HDC mDC);
	void Update();
	void FixedUpdate();
	RECTS ReturnRect();
};

